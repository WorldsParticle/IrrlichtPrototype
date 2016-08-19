cmake_minimum_required(VERSION 2.6)
PROJECT(IrrlichtProto)

INCLUDE_DIRECTORIES(
   "/usr/include/irrlicht"
   ${PROJECT_SOURCE_DIR}
)

FILE(GLOB SRCS *.cpp)
FILE(GLOB HDRS *.h)

ADD_EXECUTABLE(IrrlichtProto
   ${SRCS}
   ${HDRS}
)

TARGET_LINK_LIBRARIES(IrrlichtProto
   "/usr/lib/x86_64-linux-gnu/libIrrlicht.so"
)
