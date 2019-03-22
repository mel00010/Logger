/******************************************************************************
 * Log.hpp
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
#ifndef SRC_LOG_HPP_
#define SRC_LOG_HPP_

#include "BreakpointLogger.hpp"
#include "ConsoleLogger.hpp"
#include "Entry.hpp"
#include "FileLogger.hpp"
#include "Level.hpp"
#include "Location.hpp"
#include "Logger.hpp"
#include "LoggerManager.hpp"
#include "StreamLogger.hpp"
#include "SysLogger.hpp"

#include <iomanip>
#include <memory>
#include <string>
#include <sstream>

#if __has_include(<glm/gtx/io.hpp>)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>
#endif /* __has_include(<glm/gtx/io.hpp>) */


template<typename Integer> inline std::string hex(Integer data, size_t space = 8) {
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(sizeof(Integer)*2) << std::uppercase << std::hex << data;

	std::string s = "0x";
	size_t j = 1;

	for(auto& i : ss.str()) {
		if(j % (space + 1) == 0) {
			s.push_back(' ');
			j++;
		}
		s.push_back(i);
		j++;
	}
	return s;
}

/* Macro Code */

#ifndef MIN_LOG_LEVEL
	#ifdef NDEBUG
		#define MIN_LOG_LEVEL 3
	#else /* NDEBUG */
		#define MIN_LOG_LEVEL 0
	#endif /* NDEBUG */
#endif /* MIN_LOG_LEVEL */

#if defined( __clang__ ) || defined( __ANDROID__ ) || defined(__GNUG__)
	#define CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined( _MSC_VER )
	#define CURRENT_FUNCTION __FUNCTION__
#else
	#define CURRENT_FUNCTION "(unknown function)"
#endif


#define LOG_STREAM(log_level, stream) ::Log::Entry(log_level, ::Log::Location(CURRENT_FUNCTION, __FILE__, __LINE__)) << stream

#if MIN_LOG_LEVEL <= 0
	#define LOG_V(stream) LOG_STREAM(::Log::Level::VERBOSE, stream)
#else /* MIN_LOG_LEVEL <= 0 */
	#define LOG_V(stream) (void(0))
#endif /* MIN_LOG_LEVEL <= 0 */
#define LOG_VERBOSE(stream) LOG_V(stream)

#if MIN_LOG_LEVEL <= 1
	#define LOG_D(stream) LOG_STREAM(::Log::Level::DEBUG, stream)
#else /* MIN_LOG_LEVEL <= 1 */
	#define LOG_D(stream) (void(0))
#endif /* MIN_LOG_LEVEL <= 1 */
#define LOG_DEBUG(stream) LOG_D(stream)

#if MIN_LOG_LEVEL <= 2
	#define LOG_I(stream) LOG_STREAM(::Log::Level::INFO, stream)
#else /* MIN_LOG_LEVEL <= 2 */
	#define LOG_I(stream) (void(0))
#endif /* MIN_LOG_LEVEL <= 2 */
#define LOG_INFO(stream) LOG_I(stream)

#if MIN_LOG_LEVEL <= 3
	#define LOG_W(stream) LOG_STREAM(::Log::Level::WARNING, stream)
#else /* MIN_LOG_LEVEL <= 3 */
	#define LOG_W(stream) (void(0))
#endif /* MIN_LOG_LEVEL <= 3 */
#define LOG_WARN(stream) LOG_W(stream)

#if MIN_LOG_LEVEL <= 4
	#define LOG_E(stream) LOG_STREAM(::Log::Level::ERROR, stream)
#else /* MIN_LOG_LEVEL <= 4 */
	#define LOG_E(stream) (void(0))
#endif /* MIN_LOG_LEVEL <= 4 */
#define LOG_ERROR(stream) LOG_E(stream)

#if MIN_LOG_LEVEL <= 5
	#define LOG_F(stream) LOG_STREAM(::Log::Level::FATAL, stream)
#else /* MIN_LOG_LEVEL <= 5 */
	#define LOG_F(stream) (void(0))
#endif /* MIN_LOG_LEVEL <= 5 */
#define LOG_FATAL(stream) LOG_F(stream)

#endif /* SRC_LOG_HPP_ */
