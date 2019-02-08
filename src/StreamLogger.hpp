/******************************************************************************
 * StreamLogger.hpp
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
#ifndef SRC_STREAMLOGGER_HPP_
#define SRC_STREAMLOGGER_HPP_

#include "Logger.hpp"

#include <memory>

namespace Log {

class StreamLogger : public Logger {
	public:
		StreamLogger(std::shared_ptr<std::ostream> os);
		void writeToStream(const Metadata& meta, const std::string& text);
		void write(const Metadata& meta, const std::string& text) override;

	protected:
		std::shared_ptr<std::ostream> stream;
};

} /* namespace Log */




#endif /* SRC_STREAMLOGGER_HPP_ */
