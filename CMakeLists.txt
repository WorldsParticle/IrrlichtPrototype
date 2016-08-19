cmake_minimum_required(VERSION 2.6)
PROJECT(IrrlichtProto)

INCLUDE_DIRECTORIES(
   "/usr/include/irrlicht"
   ${PROJECT_SOURCE_DIR}/include
)

FILE(GLOB SRCS src/*.cpp)
FILE(GLOB HDRS include/*.h)

ADD_EXECUTABLE(IrrlichtProto
   ${SRCS}
   ${HDRS}
)

TARGET_LINK_LIBRARIES(IrrlichtProto
   "/usr/lib/x86_64-linux-gnu/libIrrlicht.so"
)
