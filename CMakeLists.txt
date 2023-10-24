cmake_minimum_required(VERSION 3.23)
project(m5)

set(CMAKE_CXX_STANDARD 14)

add_executable(m5 main.cpp PosApp.cpp PosApp.h Bill.cpp Bill.h Item.cpp Item.h PosIO.cpp PosIO.h POS.h Error.cpp Error.h Date.cpp Date.h Utils.cpp Utils.h Perishable.cpp Perishable.h NonPerishable.cpp NonPerishable.h)
