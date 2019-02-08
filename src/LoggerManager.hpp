/******************************************************************************
 * LoggerManager.hpp
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
#ifndef SRC_UTIL_LOG_LOGGERMANAGER_HPP_
#define SRC_UTIL_LOG_LOGGERMANAGER_HPP_

#include "Logger.hpp"

#include <memory>
#include <mutex>
#include <vector>

namespace Log {

class LoggerManager {
	public:
		static LoggerManager* instance();
		static void destroyInstance();
		void restoreToDefault();

		void clearLoggers();
		void resetLogger(const LoggerRef& logger);
		void addLogger(const LoggerRef& logger);
		void removeLogger(const LoggerRef& logger);
		template<typename LoggerT> std::vector<std::shared_ptr<LoggerT>> getLoggers();
		std::vector<LoggerRef> getAllLoggers();
		std::mutex& getMutex() const;
		void write(const Metadata &meta, const std::string &text);
		template<typename LoggerT, typename ... Args> std::shared_ptr<LoggerT> makeLogger(Args&&... args);
		template<typename LoggerT, typename ... Args> std::shared_ptr<LoggerT> makeOrGetLogger(Args&&... args);

	protected:
		LoggerManager();
		std::vector<LoggerRef> loggers;

		mutable std::mutex mutex;

		static LoggerManager *_instance;
};

LoggerManager* manager();


template<typename LoggerT, typename... Args>
std::shared_ptr<LoggerT> LoggerManager::makeLogger( Args&&... args ) {
	static_assert( std::is_base_of<Logger, LoggerT>::value, "LoggerT must inherit from log::Logger" );

	std::shared_ptr<LoggerT> result = std::make_shared<LoggerT>( std::forward<Args>( args )... );
	addLogger( result );
	return result;
}

template<typename LoggerT, typename... Args>
std::shared_ptr<LoggerT> LoggerManager::makeOrGetLogger( Args&&... args ) {
	static_assert( std::is_base_of<Logger, LoggerT>::value, "LoggerT must inherit from log::Logger" );

	auto vector = getLoggers<LoggerT>();
	if( ! vector.empty() ) {
		return vector.front();
	}

	std::shared_ptr<LoggerT> result = std::make_shared<LoggerT>( std::forward<Args>( args )... );
	addLogger( result );
	return result;
}

template<typename LoggerT>
std::vector<std::shared_ptr<LoggerT>> LoggerManager::getLoggers() {
	std::vector<std::shared_ptr<LoggerT>> result;

	std::lock_guard<std::mutex> lock( manager()->getMutex() );
	for( const auto &logger : loggers ) {
		auto loggerCasted = std::dynamic_pointer_cast<LoggerT>( logger );
		if( loggerCasted ) {
			result.push_back( loggerCasted );
		}
	}

	return result;
}


} /* namespace Log */

#endif /* SRC_UTIL_LOG_LOGGERMANAGER_HPP_ */
