# -D BOOST_ROOT=/Users/bl/ClionProjects/boost_1_59_0/ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake_minimum_required(VERSION 3.3)
project(operator_forwarding)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories (".")

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set (EXTRA_LIBS ${EXTRA_LIBS} ${Boost_LIBRARIES})
endif()

#find_package( BOOST REQUIRED)
#if ( BOOST_FOUND )
#    include_directories( ${Boost_INCLUDE_DIR} )
#    set (EXTRA_LIBS ${EXTRA_LIBS} ${Boost_LIBRARIES})
#endif( BOOST_FOUND )


set(SOURCE_FILES main.cpp ui_history.h ui_object.h ui_object_container.h common_helpers.h geo_point.h geo_rectangle.h)
add_executable(operator_forwarding ${SOURCE_FILES})

# add the executable
#target_link_libraries (${EXTRA_LIBS})
target_link_libraries (operator_forwarding ${EXTRA_LIBS})
