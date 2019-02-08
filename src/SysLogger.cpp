/******************************************************************************
 * SysLogger.cpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of Logger.
 *
 * Logger is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Logger is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Logger.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include "SysLogger.hpp"

#include "Level.hpp"

#include "Log.hpp"

#if defined( __APPLE__ )
	#include "cinder/app/cocoa/PlatformCocoa.h"
	#import <Foundation/Foundation.h>
	#include <syslog.h>
#elif defined( _WIN32 )
	#include <Windows.h>
	#include <codecvt>
#elif defined( __ANDROID__ )
	#include <android/log.h>
 	#define TAG "cinder"
#elif defined( __linux__ ) || defined( __unix__ ) || defined(_POSIX_VERSION)
	#include <syslog.h>
	#include <limits.h>
	#include <unistd.h>
	#include <libgen.h>
#endif

#include <cstring>
#include <mutex>

namespace Log {

#if defined( __APPLE__ ) || defined( __linux__ ) || defined( __unix__ ) || defined(_POSIX_VERSION)

	class SysLogger::ImplSysLog : public Logger {
		public:
			ImplSysLog() {
				#if defined( __APPLE__ )
						// determine app name from it's NSBundle. https://developer.apple.com/library/mac/qa/qa1544/_index.html
						NSBundle* bundle = app::PlatformCocoa::get()->getBundle();
						NSString* bundlePath = [bundle bundlePath];
						NSString* appName = [[NSFileManager defaultManager] displayNameAtPath: bundlePath];
						const char* cAppName = [appName UTF8String];
				#elif defined( __linux__ ) || defined( __unix__ ) || defined(_POSIX_VERSION)
					std::vector<char> buf( PATH_MAX);
					std::memset(&(buf[0]), 0, buf.size());
					ssize_t len = ::readlink("/proc/self/exe", &(buf[0]), buf.size() - 1);
					if ((-1 != len) && (len < static_cast<ssize_t>(buf.size()))) {
						buf[len] = '\0';
					}

					std::string exeName = basename((char *) (&buf[0]));
					const char* app_name = exeName.c_str();
				#endif
				openlog( app_name, ( LOG_CONS | LOG_PID ), LOG_USER );
			}

			virtual ~ImplSysLog() {
				closelog();
			}

			void write( const Metadata &meta, const std::string &text ) override {
				int sysLevel = logLevelToSysLogLevel( meta.level );
				syslog( sysLevel , "%s %s", meta.toString().c_str(), text.c_str() );
			};

	protected:
		int logLevelToSysLogLevel( Level log_level ) {
			switch( log_level ) {
				case Level::FATAL:		return LOG_CRIT;
				case Level::ERROR:		return LOG_ERR;
				case Level::WARNING:	return LOG_WARNING;
					// We never return lower than LOG_NOTICE for OS X SysLog to ensure the message arrives
					// http://apple.stackexchange.com/questions/13484/messages-issued-by-syslog-not-showing-up-in-system-logs
				case Level::INFO:		return LOG_NOTICE;
				case Level::DEBUG:		return LOG_NOTICE;
				case Level::VERBOSE:	return LOG_NOTICE;
			}
			return LOG_CRIT;
		}
	};

#elif defined( _WIN32 )
	class LoggerSystem::ImplEventLog : public Logger {
	public:
		ImplEventLog()
		{
			char filename[MAX_PATH];
			wchar_t wFilename[MAX_PATH];
			string stem;

			DWORD size = ::GetModuleFileNameA( NULL, filename, MAX_PATH );
			if( size ) {
				fs::path exePath( filename );
				stem = exePath.stem().string();
			} else {
				app::Platform::get()->console() << CINDER_CURRENT_FUNCTION << "[" << __LINE__
				<< "] could not determine application name, defaulting to 'CinderApp'" << endl;
				stem = "CinderApp";
			}

			::mbstowcs( wFilename, stem.c_str(), stem.size() + 1 );
			mHLog = ::RegisterEventSourceW( 0, wFilename );

			if( ! mHLog ) {
				app::Platform::get()->console() << CINDER_CURRENT_FUNCTION << "[" << __LINE__
				<< "] RegisterEventSourceW() failed with " << GetLastError() << endl;
			}
		}

		virtual ~ImplEventLog()
		{
			if( mHLog ) {
				::CloseEventLog( mHLog );
			}
		}

		void write( const Metadata& meta, const std::string& text ) override
		{
			int eventLevel = cinderLogLevelToEventLogLevel( meta.mLevel );

			std::wstring wMeta = mConverter.from_bytes( meta.toString() );
			std::wstring wText = mConverter.from_bytes( text );

			LPCTSTR wStrings[2];
			wStrings[0] = wMeta.c_str();
			wStrings[1] = wText.c_str();

			// Windows manifests do not allow 0 based event IDs.
			DWORD eventID = meta.mLevel + 100;

			::ReportEventW( mHLog, eventLevel, 0, eventID, 0, 2, 0, wStrings, 0 );
		}

	protected:
		int cinderLogLevelToEventLogLevel( Level cinderLogLevel )
		{
			switch( cinderLogLevel ) {
					// MSDN Event Types don't seem particularly granular, hence the repeats
				case LEVEL_FATAL:	return EVENTLOG_ERROR_TYPE;
				case LEVEL_ERROR:	return EVENTLOG_ERROR_TYPE;
				case LEVEL_WARNING:	return EVENTLOG_WARNING_TYPE;
				case LEVEL_INFO:	return EVENTLOG_INFORMATION_TYPE;
				case LEVEL_DEBUG:	return EVENTLOG_INFORMATION_TYPE;
				case LEVEL_VERBOSE:	return EVENTLOG_INFORMATION_TYPE;
				default:
					CI_ASSERT_NOT_REACHABLE();
					return 0;
			}
		}

		HANDLE			mHLog;
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> mConverter;
	};

#endif

#if defined( __ANDROID__ )
	class LoggerSystem::ImplLogCat : public Logger {
	public:
		ImplLogCat()
		{
		}

		virtual ~ImplLogCat()
		{
		}

		void write( const Metadata &meta, const std::string &text ) override
		{
			std::stringstream ss;
			writeDefault( ss, meta, text );

			android_LogPriority prio = ANDROID_LOG_DEFAULT;
			switch( meta.mLevel ) {
				case LEVEL_VERBOSE:	prio = ANDROID_LOG_VERBOSE; break;
				case LEVEL_INFO:	prio = ANDROID_LOG_INFO; 	break;
				case LEVEL_DEBUG:	prio = ANDROID_LOG_DEBUG; 	break;
				case LEVEL_WARNING:	prio = ANDROID_LOG_WARN; 	break;
				case LEVEL_ERROR:	prio = ANDROID_LOG_ERROR; 	break;
				case LEVEL_FATAL:	prio = ANDROID_LOG_FATAL; 	break;
			}

			__android_log_print( prio, TAG, ss.str().c_str() );
		}
	};

#endif /* defined ( __ANDROID__ ) */

SysLogger::SysLogger() {
	min_level = static_cast<Level>(MIN_LOG_LEVEL);
#if defined( CINDER_COCOA ) || defined( CINDER_LINUX )
	LoggerSystem::mImpl = std::unique_ptr<ImplSysLog>( new ImplSysLog() );
#elif defined( CINDER_MSW_DESKTOP )
	LoggerSystem::mImpl = std::unique_ptr<ImplEventLog>( new ImplEventLog() );
#elif defined( CINDER_ANDROID )
	LoggerSystem::mImpl = std::unique_ptr<ImplLogCat>( new ImplLogCat() );
#endif
}

SysLogger::~SysLogger() {
}

void SysLogger::write(const Metadata& meta, const std::string& text) {
#if ! defined( CINDER_UWP ) // Currently no system logging support on WinRT
	if (meta.level >= min_level) {
		mImpl->write(meta, text);
	}
#endif
}

} /* namespace Log */

