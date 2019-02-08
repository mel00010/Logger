/******************************************************************************
 * Entry.hpp
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
#ifndef SRC_ENTRY_HPP_
#define SRC_ENTRY_HPP_

#include "Level.hpp"
#include "Location.hpp"
#include "Metadata.hpp"

#include <sstream>

namespace Log {

class Entry {
	public:
		Entry(Level level, const Location& location);
		~Entry();

		template<typename T> Entry& operator<<(const T& rhs) {
			has_content = true;
			stream << rhs;
			return *this;
		}

		void writeToLog();
		const Metadata& getMetaData() const {
			return metadata;
		}

	private:
		Metadata metadata;
		bool has_content;
		std::stringstream stream;
};

} /* namespace Log */

#endif /* SRC_ENTRY_HPP_ */
