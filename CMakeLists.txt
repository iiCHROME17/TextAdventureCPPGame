cmake_minimum_required(VERSION 3.27)
project(CPP_Adv_Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP_Adv_Game main.cpp
        classes.h
        methods.h
        interpreter.h
        interactionLogic.h
)
