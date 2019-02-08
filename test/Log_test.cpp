/******************************************************************************
 * Log_test.cpp
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Log.hpp>

#include <sstream>

namespace Log {
TEST(Log_Log, Log) {

	manager()->clearLoggers();
	{
		std::shared_ptr<std::stringstream> ss = std::make_shared<std::stringstream>();
		LoggerRef logger = manager()->makeLogger<StreamLogger>(ss);

		LOG_V("Verbose test");
		EXPECT_EQ(ss->str(), "|verbose| virtual void Log::Log_Log_Log_Test::TestBody()[36] Verbose test\n");
		manager()->removeLogger(logger);
	}
	{
		std::shared_ptr<std::stringstream> ss = std::make_shared<std::stringstream>();
		LoggerRef logger = manager()->makeLogger<StreamLogger>(ss);

		LOG_D("Debug test");
		EXPECT_EQ(ss->str(), "|debug  | virtual void Log::Log_Log_Log_Test::TestBody()[44] Debug test\n");
		manager()->removeLogger(logger);
	}
	{
		std::shared_ptr<std::stringstream> ss = std::make_shared<std::stringstream>();
		LoggerRef logger = manager()->makeLogger<StreamLogger>(ss);

		LOG_I("Info test");
		EXPECT_EQ(ss->str(), "|info   | virtual void Log::Log_Log_Log_Test::TestBody()[52] Info test\n");
		manager()->removeLogger(logger);
	}
	{
		std::shared_ptr<std::stringstream> ss = std::make_shared<std::stringstream>();
		LoggerRef logger = manager()->makeLogger<StreamLogger>(ss);

		LOG_W("Warn test");
		EXPECT_EQ(ss->str(), "|warning| virtual void Log::Log_Log_Log_Test::TestBody()[60] Warn test\n");
		manager()->removeLogger(logger);
	}
	{
		std::shared_ptr<std::stringstream> ss = std::make_shared<std::stringstream>();
		LoggerRef logger = manager()->makeLogger<StreamLogger>(ss);

		LOG_E("Error test");
		EXPECT_EQ(ss->str(), "|error  | virtual void Log::Log_Log_Log_Test::TestBody()[68] Error test\n");
		manager()->removeLogger(logger);
	}
	{
		std::shared_ptr<std::stringstream> ss = std::make_shared<std::stringstream>();
		LoggerRef logger = manager()->makeLogger<StreamLogger>(ss);

		LOG_F("Fatal test");
		EXPECT_EQ(ss->str(), "|fatal  | virtual void Log::Log_Log_Log_Test::TestBody()[76] Fatal test\n");
		manager()->removeLogger(logger);
	}
	manager()->makeLogger<ConsoleLogger>();
	LOG_V("Test");
	LOG_D("Test");
	LOG_I("Test");
	LOG_W("Test");
	LOG_E("Test");
	LOG_F("Test");
}
} /* namespace Log */
