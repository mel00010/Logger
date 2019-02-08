/******************************************************************************
 * Level.cpp
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

#include "Level.hpp"

namespace Log {

std::ostream& operator<<(std::ostream &os, const Level &rhs) {
	switch (rhs) {
		case Level::VERBOSE:
			os << "|verbose|";
			break;
		case Level::DEBUG:
			os << "|debug  |";
			break;
		case Level::INFO:
			os << "|info   |";
			break;
		case Level::WARNING:
			os << "|warning|";
			break;
		case Level::ERROR:
			os << "|error  |";
			break;
		case Level::FATAL:
			os << "|fatal  |";
			break;
	}
	return os;
}

} /* namespace Log */

