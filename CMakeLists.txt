cmake_minimum_required(VERSION 2.6)
PROJECT(IrrlichtProto)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(OpenGL)
find_package(Irrlicht)

set(FMOD_LIBRARIES "${PROJECT_SOURCE_DIR}/lib/fmod_x86_64/libfmod.so")

include_directories(
        ${IRRLICHT_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/fmod
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -o2 -std=c++11 -Wall -pedantic -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -o2 -std=c++11 -W")

set(IRRLICHTPROTO_SOURCE_FILES
        src/Core.cpp
        src/ElementsModule.cpp
        src/main.cpp
        src/MyEventReceiver.cpp
        src/SkyboxModule.cpp
        src/SoundModule.cpp
        src/TerrainModule.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(IrrlichtProto WIN32 ${IRRLICHTPROTO_SOURCE_FILES})

target_link_libraries(IrrlichtProto
        ${IRRLICHT_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${FMOD_LIBRARIES}
)

