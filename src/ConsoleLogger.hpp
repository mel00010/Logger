/******************************************************************************
 * ConsoleLogger.hpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of CIS_441.
 *
 * CIS_441 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CIS_441 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CIS_441.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef SRC_UTIL_LOG_CONSOLELOGGER_HPP_
#define SRC_UTIL_LOG_CONSOLELOGGER_HPP_

#include "StreamLogger.hpp"
#include "Metadata.hpp"

#include <string>

namespace Log {

class ConsoleLogger : public StreamLogger {
	public:
		ConsoleLogger();
		void write(const Metadata& meta, const std::string& text) override;
};

} /* namespace Log */

#endif /* SRC_UTIL_LOG_CONSOLELOGGER_HPP_ */
