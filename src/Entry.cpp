/******************************************************************************
 * Entry.cpp
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

#include "Entry.hpp"

#include "LoggerManager.hpp"


namespace Log {

Entry::Entry(Level level, const Location& location) :
		metadata { level, location }, has_content(false) {
}

Entry::~Entry()
{
	if (has_content) {
		writeToLog();
	}
}

void Entry::writeToLog()
{
	manager()->write(metadata, stream.str());
}

}
/* namespace Log */

