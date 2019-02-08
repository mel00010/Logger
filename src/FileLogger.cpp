/******************************************************************************
 * FileLogger.cpp
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

#include "FileLogger.hpp"

#include <fstream>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
	#include <direct.h>
	#define GetCurrentDir _getcwd
	#define SEPARATOR "\\"
	#define MkDir(file) _mkdir(file)
#else /* WINDOWS */
	#include <unistd.h>
	#define GetCurrentDir getcwd
	#define SEPARATOR "/"
	#include <sys/types.h>
	#include <sys/stat.h>
	#define MkDir(file) mkdir(file, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)

#endif /* WINDOWS */

#include <algorithm>
#include <errno.h>
#include <vector>
#include <iostream>

namespace Log {

std::string get_current_dir() {
	char current_path[FILENAME_MAX];

	if (!GetCurrentDir(current_path, sizeof(current_path))) {
		return std::string("");
	}

	return std::string(current_path);
}

bool path_exists(std::string path) {
	struct stat info;

	if(stat( path.c_str(), &info ) != 0) {
		return false;
	} else if(info.st_mode & S_IFDIR) {
		return true;
	}
	return false;
}

std::string get_parent_dir(std::string path) {
	size_t sep_location = path.find_last_of(SEPARATOR);
	if(sep_location == std::string::npos) {
		return path;
	}
	return path.substr(0, sep_location);
}

bool create_path(std::string file_path) {
	if(path_exists(file_path)) {
		return true;
	}
	std::string path = file_path;
	std::vector<std::string> paths;
	do {
		paths.push_back(path);
		path = get_parent_dir(path);
	} while(path.find_last_of(SEPARATOR) != std::string::npos);

	std::reverse(paths.begin(), paths.end());
	for(auto& i : paths) {
		if (MkDir(i.c_str()) == -1) {
			if(errno == EEXIST) {
				continue;
			}
			return false;
		}
	}
	return true;
}

FileLogger::FileLogger(const std::string& _file_path, bool append_to_existing) :
		file_path(_file_path), append(append_to_existing) {
	if (file_path.empty()) {
		file_path = getDefaultLogFilePath();
	}

	setTimestampEnabled();
}

FileLogger::~FileLogger() {
	if (stream.is_open())
		stream.close();
}

void FileLogger::write(const Metadata &meta, const std::string &text) {
	if (!stream.is_open()) {
		ensureDirectoryExists();
		append ? stream.open(file_path, std::ofstream::app) : stream.open(file_path);
	}
	writeDefault(stream, meta, text);
}

std::string FileLogger::getDefaultLogFilePath() const {
	return get_current_dir() + SEPARATOR + "cinder.log";
}

void FileLogger::ensureDirectoryExists() {
	std::string dir = file_path;
	if (dir.empty()) {
		// make single file path names explicitly next to executable
		dir = get_current_dir() + SEPARATOR + file_path;
	}
	else if (!path_exists(dir)) {
		bool success = create_path(dir);
		if (!success) {
			// not using CI_LOG_E since it could lead to recursion
			std::cerr << "Log::LoggerFile error: Unable to create folder \"" << dir << "\"" << std::endl;
		}
	}
}

} /* namespace Log */

