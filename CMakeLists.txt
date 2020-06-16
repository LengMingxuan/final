cmake_minimum_required(VERSION 3.16)
project(final C)

set(CMAKE_C_STANDARD 99)

add_executable(final main.c bank_lmx.c bank_lmx.h Disk_lmx.c Disk_lmx.h FCFSlmx.c FCFS_SJFlmx.h SJFlmx.c replacementlmx.c replacementlmx.h)