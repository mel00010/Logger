/******************************************************************************
 * Indent.cpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of GameEngine.
 *
 * GameEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include "Indent.hpp"

#include <iostream>

namespace Log {

int Indent::indent = 0;

} /* namespace Log */

std::ios_base& push_indent(std::ios_base& os) {
	::Log::Indent::indent++;
	return os;
}
std::ios_base& pop_indent(std::ios_base& os) {
	if(::Log::Indent::indent == 0) {
		return os;
	}
	::Log::Indent::indent--;
	return os;
}




