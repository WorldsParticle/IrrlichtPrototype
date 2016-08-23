cmake_minimum_required(VERSION 2.6)
PROJECT(IrrlichtProto)

INCLUDE_DIRECTORIES(
   "/usr/include/irrlicht"
   ${PROJECT_SOURCE_DIR}/include
   ${PROJECT_SOURCE_DIR}/include/fmod
)

FILE(GLOB SRCS src/*.cpp)
FILE(GLOB HDRS include/*.h)
FILE(GLOB HDRS include/fmod/*.h)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -o2 -W")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -o2")

ADD_EXECUTABLE(IrrlichtProto
   ${SRCS}
   ${HDRS}
)

TARGET_LINK_LIBRARIES(IrrlichtProto
   "/usr/lib/x86_64-linux-gnu/libIrrlicht.so"
   ${PROJECT_SOURCE_DIR}/lib/fmod_x86_64/libfmod.so
)

