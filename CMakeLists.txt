#####################################################################################
# This CMakeLists.txt file was generated using Skylar Cupit's json_to_cmake tool.   #
# Github: https://github.com/scupit/json_to_cmake                                   #
#####################################################################################

cmake_minimum_required( VERSION 3.12 )
project( json_parser_improved )

set( JPARSER_SOURCES
	${PROJECT_SOURCE_DIR}/src/JsonValue.cpp
	${PROJECT_SOURCE_DIR}/src/JsonParser.cpp
	${PROJECT_SOURCE_DIR}/include/JsonValue.hpp
	${PROJECT_SOURCE_DIR}/include/JsonParser.hpp
)

add_library( jparser STATIC ${JPARSER_SOURCES} )

set( jparser_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include/
)

target_include_directories( jparser PRIVATE ${jparser_INCLUDE_DIRS} )

set_target_properties( jparser
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}
)

set( JPARSER_SHARED_SOURCES
	${PROJECT_SOURCE_DIR}/src/JsonValue.cpp
	${PROJECT_SOURCE_DIR}/src/JsonParser.cpp
	${PROJECT_SOURCE_DIR}/include/JsonValue.hpp
	${PROJECT_SOURCE_DIR}/include/JsonParser.hpp
)

add_library( jparser_shared SHARED ${JPARSER_SHARED_SOURCES} )

set( jparser_shared_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include/
)

target_include_directories( jparser_shared PRIVATE ${jparser_shared_INCLUDE_DIRS} )

set_target_properties( jparser_shared
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}
)

set( TEST_SOURCES
	${PROJECT_SOURCE_DIR}/testing/test.cpp
	${PROJECT_SOURCE_DIR}/testing/src/TestPrinterFunctions.cpp
	${PROJECT_SOURCE_DIR}/testing/src/OperatorTestFunctions.cpp
	${PROJECT_SOURCE_DIR}/testing/src/ArithmeticTestFunctions.cpp
	${PROJECT_SOURCE_DIR}/testing/src/JsonValueTestFunctions.cpp
	${PROJECT_SOURCE_DIR}/testing/include/ArithmeticTestFunctions.hpp
	${PROJECT_SOURCE_DIR}/testing/include/JsonValueTestFunctions.hpp
	${PROJECT_SOURCE_DIR}/testing/include/OperatorTestFunctions.hpp
	${PROJECT_SOURCE_DIR}/testing/include/TestPrinterFunctions.hpp
	${jparser_HEADER_FILES}
)

add_executable( test ${TEST_SOURCES} )

target_include_directories( test PRIVATE
	${PROJECT_SOURCE_DIR}/testing/include/
	${jparser_INCLUDE_DIRS}
)

set_target_properties( test
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}
)

set( JSON_PARSER_SOURCES
	${PROJECT_SOURCE_DIR}/main.cpp
	${jparser_HEADER_FILES}
)

add_executable( json_parser ${JSON_PARSER_SOURCES} )

target_include_directories( json_parser PRIVATE
	${jparser_INCLUDE_DIRS}
)

set_target_properties( json_parser
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}
)

target_link_libraries( test
	jparser
)

target_link_libraries( json_parser
	jparser
)

set( C_COMPILER_STANDARD "11" CACHE STRING "C compiler standard year")
set_property( CACHE C_COMPILER_STANDARD PROPERTY STRINGS "11" )
message( "Using C compiler standard -std=c${C_COMPILER_STANDARD}" )

set( CXX_COMPILER_STANDARD "14" CACHE STRING "C++ compiler standard year")
set_property( CACHE CXX_COMPILER_STANDARD PROPERTY STRINGS "14" )
message( "Using CXX compiler standard -std=c++${CXX_COMPILER_STANDARD}" )

if( "${CMAKE_BUILD_TYPE}" STREQUAL "" )
	set( CMAKE_BUILD_TYPE "Release" )
endif()

set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" )

if( ${CMAKE_BUILD_TYPE} STREQUAL Debug )
	set( C_FLAGS "-g -Wall -Wextra -Wconversion -Wuninitialized -pedantic -pedantic-errors " CACHE STRING "C Compiler options" )
	message( "Using C compiler flags: ${C_FLAGS}" )

	set( CXX_FLAGS "-g -Wall -Wextra -Wconversion -Wuninitialized -pedantic -pedantic-errors " CACHE STRING "CXX Compiler options" )
	message( "Using CXX compiler flags: ${CXX_FLAGS}" )

	message( "Building project ${CMAKE_BUILD_TYPE} configuration" )
endif()

if( ${CMAKE_BUILD_TYPE} STREQUAL Release )
	set( C_FLAGS "-O3 -DNDEBUG -s " CACHE STRING "C Compiler options" )
	message( "Using C compiler flags: ${C_FLAGS}" )

	set( CXX_FLAGS "-O3 -DNDEBUG -s " CACHE STRING "CXX Compiler options" )
	message( "Using CXX compiler flags: ${CXX_FLAGS}" )

	message( "Building project ${CMAKE_BUILD_TYPE} configuration" )
endif()
