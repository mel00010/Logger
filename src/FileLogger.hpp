/******************************************************************************
 * FileLogger.hpp
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
#ifndef SRC_UTIL_LOG_FILELOGGER_HPP_
#define SRC_UTIL_LOG_FILELOGGER_HPP_

#include "Logger.hpp"

#include <fstream>
#include <string>

namespace Log {

class FileLogger : public Logger {
	public:
		//! LoggerFile writes to a single log file.  File appending is configurable.
		//! If \p filePath is empty, uses the default ('%cinder.log' next to app binary)
		FileLogger( const std::string& filePath, bool appendToExisting = true );

		virtual ~FileLogger();

		void write(const Metadata &meta, const std::string &text) override;

		//! Returns the file path targeted by this logger.
		const std::string& getFilePath() const {
			return file_path;
		}

	protected:
		std::string getDefaultLogFilePath() const;
		void ensureDirectoryExists();

		std::string file_path;
		bool append;
		std::ofstream stream;
};

} /* namespace Log */



#endif /* SRC_UTIL_LOG_FILELOGGER_HPP_ */
