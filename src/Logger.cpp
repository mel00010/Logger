/******************************************************************************
 * Logger.cpp
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

#include "Logger.hpp"

namespace Log {

void Logger::setTimestampEnabled(bool enable) {
	time_stamp_enabled = enable;
}
bool Logger::isTimestampEnabled() const {
	return time_stamp_enabled;
}
void Logger::setColorsEnabled(bool enable) {
	colors_enabled = enable;
}
bool Logger::areColorsEnabled() const {
	return colors_enabled;
}

Logger::Logger() : time_stamp_enabled(false), colors_enabled(false) {

}

const std::string getCurrentDateTimeString() {
	time_t timeSinceEpoch = time( NULL );
	struct tm *now = localtime( &timeSinceEpoch );

	char result[100];
	strftime( result, sizeof( result ), "%Y-%m-%d.%X", now );

	return result;
}

const std::string bold()		{	return "\x1B[1m";	}
const std::string underline()	{	return "\x1B[4m";	}
const std::string white()		{	return "\x1B[37m";	}
const std::string green()		{	return "\x1B[32m";	}
const std::string cyan()		{	return "\x1B[36m";	}
const std::string blue()		{	return "\x1B[34m";	}
const std::string magenta()		{	return "\x1B[35m";	}
const std::string yellow()		{	return "\x1B[33m";	}
const std::string red() 		{	return "\x1B[31m";	}
const std::string reset()		{	return "\x1B[0m";	}

void Logger::writeDefault( std::ostream &stream, const Metadata &meta, const std::string &text) {
	if(colors_enabled) {
		switch (meta.level) {
			case Level::VERBOSE:	stream << bold() << white();	break;
			case Level::DEBUG:		stream << bold() << green();	break;
			case Level::INFO:		stream << bold() << cyan();		break;
			case Level::WARNING:	stream << bold() << blue();		break;
			case Level::ERROR:		stream << bold() << magenta();	break;
			case Level::FATAL:		stream << bold() << red();		break;
		}
	}
	stream << meta.level;
	if(colors_enabled) {
		stream << reset();
	}
	stream << " ";

	if( isTimestampEnabled() ) {
		if(colors_enabled) {
			stream << green();
		}

		stream << getCurrentDateTimeString();
		if(colors_enabled) {
			stream << reset();
		}
		stream << " ";
	}
	if(colors_enabled) {
		stream << yellow();
	}
	stream << meta.location;
	if(colors_enabled) {
		stream << reset();
	}
	stream << " " << text << std::endl;
}


} /* namespace Log */


