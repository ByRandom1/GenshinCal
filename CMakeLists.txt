cmake_minimum_required(VERSION 3.23)
project(GenshinCal)

set(CMAKE_CXX_STANDARD 23)

add_executable(GenshinCal main.cpp Character.cpp Character.h Weapon.cpp Weapon.h Artifact.cpp Artifact.h Basic_Elements.h Character_data.cpp Character_data.h Weapon_data.cpp Weapon_data.h Artifact_data.cpp Artifact_data.h Deployment.cpp Deployment.h Basic_Elements.cpp Config_File.cpp Config_File.h)
