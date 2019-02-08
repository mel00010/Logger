/******************************************************************************
 * Logger.hpp
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
#ifndef SRC_UTIL_LOG_LOGGER_HPP_
#define SRC_UTIL_LOG_LOGGER_HPP_

#include "Metadata.hpp"

#include <memory>
#include <ostream>

namespace Log {

class Noncopyable {
	protected:
		Noncopyable() = default;
		~Noncopyable() = default;

		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator=(const Noncopyable&) = delete;
};

class Logger: protected Noncopyable {
	public:
		virtual ~Logger() = default;

	public:
		virtual void write(const Metadata& meta, const std::string& text) = 0;

		void setTimestampEnabled(bool enable  = true);
		bool isTimestampEnabled() const;
		void setColorsEnabled(bool enable  = true);
		bool areColorsEnabled() const;

	protected:
		Logger();

		void writeDefault(std::ostream& stream, const Metadata& meta, const std::string& text);

	protected:
		bool time_stamp_enabled;
		bool colors_enabled;
};

using LoggerRef = std::shared_ptr<Logger>;

} /* namespace Log */

#endif /* SRC_UTIL_LOG_LOGGER_HPP_ */
