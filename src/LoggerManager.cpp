/******************************************************************************
 * LoggerManager.cpp
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

#include "LoggerManager.hpp"

#include "ConsoleLogger.hpp"
#include "SysLogger.hpp"

#include <algorithm>

namespace Log {

LoggerManager* LoggerManager::instance() {
	return _instance;
}
void LoggerManager::destroyInstance() {
	delete _instance;
}

std::mutex& LoggerManager::getMutex() const {
	return mutex;
}

LoggerManager* manager() {
	return LoggerManager::instance();
}

LoggerManager::LoggerManager() {
	restoreToDefault();
}

void LoggerManager::clearLoggers() {
	std::lock_guard<std::mutex> lock(mutex);
	loggers.clear();
}

void LoggerManager::resetLogger(const LoggerRef& logger) {
	std::lock_guard<std::mutex> lock(mutex);
	loggers.clear();
	loggers.push_back(logger);
}

void LoggerManager::addLogger(const LoggerRef& logger) {
	std::lock_guard<std::mutex> lock(mutex);
	loggers.push_back(logger);
}

void LoggerManager::removeLogger(const LoggerRef& logger) {
	std::lock_guard<std::mutex> lock(mutex);
	loggers.erase(
		remove_if(loggers.begin(), loggers.end(),
			[logger]( const LoggerRef &o ) {
				return o == logger;
			}
		),
		loggers.end()
	);
}

std::vector<LoggerRef> LoggerManager::getAllLoggers() {
	std::lock_guard<std::mutex> lock(mutex);
	return loggers;
}

void LoggerManager::restoreToDefault() {
	clearLoggers();
	makeLogger<ConsoleLogger>();
}

void LoggerManager::write(const Metadata& meta, const std::string& text) {
	// TODO move this to a shared_lock_timed with c++14 support
	std::lock_guard<std::mutex> lock(mutex);

	for (auto& logger : loggers) {
		logger->write(meta, text);
	}
}

} /* namespace Log */

