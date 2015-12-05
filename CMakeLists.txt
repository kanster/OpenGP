cmake_minimum_required(VERSION 2.8)
project( OpenGP )


# add eigen
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)
find_package( Eigen3 REQUIRED )
if(EIGEN3_FOUND)
	message(STATUS "Found Eigen3 ${EIGEN3_INCLUDE_DIR}")
	include_directories(${EIGEN3_INCLUDE_DIR})
	set(EIGEN3_FOUND TRUE)
else()
	set(EIGEN3_FOUND FALSE)
endif()

# add boost
find_package(Boost COMPONENTS thread)
if(Boost_FOUND)
	message(STATUS "Found Boost ${Boost_INCLUDE_DIRS}")
	include_directories(${Boost_INCLUDE_DIRS})
	set(Boost_FOUND TRUE)
else()
	set(Boost_FOUND FALSE)
endif()

# add dlib
find_package(dlib REQUIRED)
if(dlib_FOUND)
	message(STATUS "Found dlib ${dlib_INCLUDE_DIRS} ${dlib_LIBRARIES}")
	include_directories(${dlib_INCLUDE_DIRS})
	set(dlib_FOUND TRUE)
else()
	set(dlib_FOUND FALSE)
endif()

set( HEADER
	${PROJECT_SOURCE_DIR}/../include/GP.h
	${PROJECT_SOURCE_DIR}/../include/cov.h
	${PROJECT_SOURCE_DIR}/../include/inf.h
	${PROJECT_SOURCE_DIR}/../include/mean.h
)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/../src/*.hpp)

include_directories(${PROJECT_SOURCE_DIR})

add_executable( main main.cpp ${HEADER} ${SRC})
link_libraries( main ${Boost_LIRARIES} ${dlib_LIBRARIES}
	${PROJECT_SOURCE_DIR}/../externals/gtest-1.7.0/build/libgtest.a
	${PROJECT_SOURCE_DIR}/../externals/gtest-1.7.0/build/libgtest_main.a )
