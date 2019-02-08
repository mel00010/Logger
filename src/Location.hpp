/******************************************************************************
 * Location.hpp
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
#ifndef SRC_LOCATION_HPP_
#define SRC_LOCATION_HPP_

#include <ostream>
#include <string>

namespace Log {

class Location {
	public:
		Location() = default;
		Location(const std::string& _function_name, const std::string& _file_name, const size_t& _line_number);

	public:
		const std::string& getFileName() const;
		const std::string& getFunctionName() const;
		size_t getLineNumber() const;

	private:
		std::string function_name, file_name;
		size_t line_number;
};

std::ostream& operator<<(std::ostream& os, const Location& rhs);

} /* namespace Log */

#endif /* SRC_LOCATION_HPP_ */
