/******************************************************************************
 * Location.cpp
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

#include "Location.hpp"

namespace Log {

Location::Location(const std::string& _function_name, const std::string& _file_name, const size_t& _line_number) :
		function_name(_function_name), file_name(_file_name), line_number(_line_number) {
}

const std::string& Location::getFileName() const {
	return file_name;
}

const std::string& Location::getFunctionName() const {
	return function_name;
}

size_t Location::getLineNumber() const {
	return line_number;
}

std::ostream& operator<<(std::ostream& os, const Location& rhs) {
	return os << rhs.getFunctionName() << "[" << rhs.getLineNumber() << "]";
}


} /* namespace Log */

