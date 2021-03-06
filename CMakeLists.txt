cmake_minimum_required(VERSION 3.6)

PROJECT(amultios)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(MySQL REQUIRED)


include_directories(".")
file(GLOB SOURCES *.cpp *.h)

include_directories(${MYSQL_INCLUDE_DIR})
link_directories(${MYSQL_LIBRARY})


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(amultios ${SOURCES})
target_link_libraries(amultios ${MYSQL_LIBRARY})
target_link_libraries(amultios Threads::Threads)
if(WIN32)
  target_link_libraries(amultios wsock32 ws2_32)
endif()