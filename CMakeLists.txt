cmake_minimum_required(VERSION 3.12)

project(desafio-origem VERSION 1.0)

add_library(cp header/cp.hpp src/cp.cpp)
add_library(etb header/etb.hpp src/etb.cpp)
add_library(host header/host.hpp src/host.cpp)
add_library(moto header/moto.hpp src/moto.cpp)
add_library(battery header/battery.hpp src/battery.cpp)

add_executable(desafio-origem main.cpp)

target_link_libraries(desafio-origem PRIVATE cp)
target_link_libraries(desafio-origem PRIVATE etb)
target_link_libraries(desafio-origem PRIVATE host)
target_link_libraries(desafio-origem PRIVATE moto)
target_link_libraries(desafio-origem PRIVATE battery)