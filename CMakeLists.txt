cmake_minimum_required(VERSION 2.4)

project(Deque)

set(HEADERS
	include/deque.h
)

set(SOURCES
	src/deque.c
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

#enable option for dynamic resizing
if(DYNAMIC_DEQUE)
	target_compile_definitions(${PROJECT_NAME} PUBLIC DYNAMIC_DEQUE)
endif()

#enable option for building tests
if(BUILD_TESTS)
	add_executable(${PROJECT_NAME}_tests src/test.c)
	target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME})
endif()
