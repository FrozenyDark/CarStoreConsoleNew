cmake_minimum_required(VERSION 3.25)
project(CarStore VERSION 1.03)

set(CMAKE_CXX_STANDARD 23)

include_directories(/usr/local/Cellar/boost/1.82.0/include)
link_directories(/usr/local/Cellar/boost/1.82.0/lib)

add_executable(CarStore main.cpp model/common/Includes.h model/object/Object.cpp model/object/Object.h model/table/BasicTable.cpp model/table/BasicTable.h model/table/Table.h model/table/View.cpp model/table/View.h model/common/Extensions.h model/ui/UserInterface.cpp model/ui/UserInterface.h model/configuration/Configuration.cpp model/configuration/Configuration.h model/configuration/DemoData.cpp model/configuration/DemoData.h)

add_subdirectory(Tests)
