cmake_minimum_required(VERSION 3.23)
project(GenshinCal)

set(CMAKE_CXX_STANDARD 23)

add_executable(GenshinCal main.cpp Character.cpp Character.h Weapon.cpp Weapon.h Artifact.cpp Artifact.h Basic_Elements.h Basic_Elements.cpp Deployment.cpp Deployment.h Config_File.cpp Config_File.h Reinforced_Artifact.cpp Reinforced_Artifact.h)

INCLUDE_DIRECTORIES(/usr/local/Cellar/jsoncpp/1.9.5/include)
LINK_DIRECTORIES(/usr/local/Cellar/jsoncpp/1.9.5/lib)

file(GLOB LIBRARIES "/usr/local/Cellar/jsoncpp/1.9.5/lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(GenshinCal ${LIBRARIES})