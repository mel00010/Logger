/******************************************************************************
 * Indent.hpp
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
#ifndef BUILD_RELEASE__DEPS_LOGGER_SRC_SRC_INDENT_HPP_
#define BUILD_RELEASE__DEPS_LOGGER_SRC_SRC_INDENT_HPP_

#include <iostream>
#include <ostream>
#include <streambuf>

namespace Log {

class Indent : public std::streambuf {
	public:
		explicit Indent(std::ostream& os) : dest(os) {}

	protected:
		virtual int overflow( int ch ) {
			if ( atStartOfLine && (ch != '\n') ) {
				for(int i = 0; i < indent; i++) {
					dest.rdbuf()->sputn("    ", 4);
				}
			}
			atStartOfLine = (ch == '\n');
			return dest.rdbuf()->sputc( ch );
		}
	public:
		static int indent;
		std::ostream& dest;
	protected:
		bool atStartOfLine = true;

};

} /* namespace Log */


std::ios_base& push_indent(std::ios_base& os);
std::ios_base& pop_indent(std::ios_base& os);





#endif /* BUILD_RELEASE__DEPS_LOGGER_SRC_SRC_INDENT_HPP_ */
