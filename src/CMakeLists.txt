add_library(Logger STATIC "")
add_library(Logger::Logger ALIAS Logger)

target_sources(Logger
	PRIVATE
		BreakpointLogger.cpp
		ConsoleLogger.cpp
		Entry.cpp
		FileLogger.cpp
		Indent.cpp
		Level.cpp
		Location.cpp
		Log.cpp
		Logger.cpp
		LoggerManager.cpp
		Metadata.cpp
		StreamLogger.cpp
		SysLogger.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/BreakpointLogger.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/ConsoleLogger.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Entry.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/FileLogger.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Indent.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Level.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Location.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Log.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Logger.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/LoggerManager.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Metadata.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/StreamLogger.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/SysLogger.hpp
)
target_include_directories(Logger
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Logger
)