/******************************************************************************
 * SysLogger.hpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of CIS_441.
 *
 * CIS_441 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CIS_441 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CIS_441.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef SRC_UTIL_LOG_SYSLOGGER_HPP_
#define SRC_UTIL_LOG_SYSLOGGER_HPP_

#include "Logger.hpp"

namespace Log {

class SysLogger : public Logger {
	public:
		SysLogger();
		virtual ~SysLogger();

		void write(const Metadata& meta, const std::string& text) override;
		//! Sets the minimum logging level that will trigger a system log.
		//! \note Setting \p minLevel below CI_MIN_LOG_LEVEL is pointless; minLevel will act like CI_MIN_LOG_LEVEL.
		void setLoggingLevel(Level _min_level) {
			min_level = _min_level;
		}

	protected:
		Level min_level;
#if defined( __APPLE__ ) || defined( __linux__ ) || defined( __unix__ ) || defined(_POSIX_VERSION)
		class ImplSysLog;
		std::unique_ptr<ImplSysLog> mImpl;
#elif defined( _WIN32 )
		class ImplEventLog;
		std::unique_ptr<ImplEventLog> mImpl;
#elif defined( __ANDROID__ )
		class ImplLogCat;
		std::unique_ptr<ImplLogCat> mImpl;
#endif
};


} /* namespace Log */


#endif /* SRC_UTIL_LOG_SYSLOGGER_HPP_ */
