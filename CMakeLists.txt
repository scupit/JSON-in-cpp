################################################################################
# Generated with Skylar Cupit's json-to-cmake tool                             #
# GitHub: https://github.com/scupit/json-to-cmake-rewrite                      #
################################################################################

cmake_minimum_required( VERSION 3.12 )
project( json_parser_improved )

# ////////////////////////////////////////////////////////////////////////////////
# Custom Functions
# ////////////////////////////////////////////////////////////////////////////////

function( createLibraryWithTypeToggle libName libType libSources )
  if( libType STREQUAL STATIC )
    set( oppositeLibType SHARED )
  elseif( libType STREQUAL SHARED )
    set( oppositeLibType STATIC )
  endif()

  if( NOT ${libName}_LIB_TYPE )
    set( ${libName}_LIB_TYPE ${libType} CACHE STRING "${libName} library type" FORCE )
  endif()

  set_property( CACHE ${libName}_LIB_TYPE PROPERTY STRINGS "${libType}" "${oppositeLibType}" )

  if( ${libName}_LIB_TYPE STREQUAL ${libType} )
    add_library( ${libName} ${libType} ${libSources} )
  elseif( ${libName}_LIB_TYPE STREQUAL ${oppositeLibType} )
    add_library( ${libName} ${oppositeLibType} ${libSources} )
  endif()
endFunction()

# ////////////////////////////////////////////////////////////////////////////////
# LANGUAGE STANDARDS
# ////////////////////////////////////////////////////////////////////////////////

set( CMAKE_C_STANDARD 99 CACHE STRING "C compiler standard year" )
set_property( CACHE CMAKE_C_STANDARD PROPERTY STRINGS 99 )
message( "Using C compiler standard --std=c${CMAKE_C_STANDARD}" )

set( CMAKE_CXX_STANDARD 14 CACHE STRING "CXX compiler standard year" )
set_property( CACHE CMAKE_CXX_STANDARD PROPERTY STRINGS 14 17 )
message( "Using CXX compiler standard --std=c++${CMAKE_CXX_STANDARD}" )

set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( CMAKE_C_EXTENSIONS OFF )
set( CMAKE_CXX_EXTENSIONS OFF )

# ////////////////////////////////////////////////////////////////////////////////
# BUILD TARGETS
# ////////////////////////////////////////////////////////////////////////////////

set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" )

if( "${CMAKE_BUILD_TYPE}" STREQUAL "" )
	set( CMAKE_BUILD_TYPE "Debug" CACHE STRING "Project Configuration" FORCE )
endif()

if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
	set( CMAKE_CXX_FLAGS "-g -Wall -Wextra -Wconversion -Wuninitialized -pedantic -pedantic-errors " )
	set( CMAKE_C_FLAGS "-g -Wall -Wextra -Wconversion -Wuninitialized -pedantic -pedantic-errors " )
elseif( "${CMAKE_BUILD_TYPE}" STREQUAL "Release" )
	set( CMAKE_CXX_FLAGS "-O2 -s " )
	set( CMAKE_C_FLAGS "-O2 -s " )
	add_compile_definitions( NDEBUG )
endif()

message( "Using compiler flags: ${CMAKE_CXX_FLAGS}" )
message( "Building project '${CMAKE_BUILD_TYPE}' configuration" )

# ////////////////////////////////////////////////////////////////////////////////
# INDIVIDUAL OUTPUT STATIC LIBRARIES 
# ////////////////////////////////////////////////////////////////////////////////

# Output static library: jparser
set( jparser_HEADERS
	${PROJECT_SOURCE_DIR}/include/JsonParser.hpp
	${PROJECT_SOURCE_DIR}/include/JsonValue.hpp
)

set( jparser_SOURCES
	${jparser_HEADERS}
	${PROJECT_SOURCE_DIR}/src/JsonParser.cpp
	${PROJECT_SOURCE_DIR}/src/JsonValue.cpp
)

set( jparser_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include
)

createLibraryWithTypeToggle( jparser STATIC "${jparser_SOURCES}" )
target_include_directories( jparser PRIVATE ${jparser_INCLUDE_DIRS} )

set_target_properties( jparser PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}
)

# ////////////////////////////////////////////////////////////////////////////////
# OUTPUT EXECUTABLES 
# ////////////////////////////////////////////////////////////////////////////////

# Output executable: json_parser
set( json_parser_HEADERS
	${jparser_HEADERS}
)

set( json_parser_SOURCES
	${json_parser_HEADERS}
	${PROJECT_SOURCE_DIR}/main.cpp
)

set( json_parser_INCLUDE_DIRS
	${jparser_INCLUDE_DIRS}
)

add_executable( json_parser ${json_parser_SOURCES} )
target_include_directories( json_parser PRIVATE ${json_parser_INCLUDE_DIRS} )

set_target_properties( json_parser PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}
)

# Output executable: test
set( test_HEADERS
	${jparser_HEADERS}
	${PROJECT_SOURCE_DIR}/testing/include/ArithmeticTestFunctions.hpp
	${PROJECT_SOURCE_DIR}/testing/include/JsonValueTestFunctions.hpp
	${PROJECT_SOURCE_DIR}/testing/include/OperatorTestFunctions.hpp
	${PROJECT_SOURCE_DIR}/testing/include/TestPrinterFunctions.hpp
)

set( test_SOURCES
	${test_HEADERS}
	${PROJECT_SOURCE_DIR}/testing/test.cpp
	${PROJECT_SOURCE_DIR}/testing/src/ArithmeticTestFunctions.cpp
	${PROJECT_SOURCE_DIR}/testing/src/JsonValueTestFunctions.cpp
	${PROJECT_SOURCE_DIR}/testing/src/OperatorTestFunctions.cpp
	${PROJECT_SOURCE_DIR}/testing/src/TestPrinterFunctions.cpp
)

set( test_INCLUDE_DIRS
	${jparser_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}/testing/include
)

add_executable( test ${test_SOURCES} )
target_include_directories( test PRIVATE ${test_INCLUDE_DIRS} )

set_target_properties( test PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}
)

# ////////////////////////////////////////////////////////////////////////////////
# LINK LIBRARIES TO OUTPUTS
# ////////////////////////////////////////////////////////////////////////////////

target_link_libraries( json_parser
	jparser 
)

target_link_libraries( test
	jparser 
)

