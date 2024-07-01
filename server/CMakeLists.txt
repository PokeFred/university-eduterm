project(server C)
set(CMAKE_C_STANDARD 23)
cmake_minimum_required(VERSION 3.28)

add_executable(writer
    src/writer.c
    src/shared_memory.h src/shared_memory.cpp
    src/semaphore.h src/semaphore.cpp
)

add_executable(reader
    src/reader.c
    src/shared_memory.h src/shared_memory.cpp
    src/semaphore.h src/semaphore.cpp
    src/dataframe.h
)
