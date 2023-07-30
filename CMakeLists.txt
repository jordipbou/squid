cmake_minimum_required (VERSION 3.8)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-std=c99 -pedantic")

project(squid LANGUAGES C)

set(squid_VERSION_MAJOR 0)
set(squid_VERSION_MINOR 1)

add_executable (
	squid 
	src/squid)
	#deps/Crossline/crossline.c)

target_include_directories (squid PRIVATE src deps/termbox2) #deps/Crossline)
