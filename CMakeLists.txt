cmake_minimum_required(VERSION 3.19)
project(memory_game)
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS  "-g")
find_package(Qt5Widgets REQUIRED)
include_directories("/usr/include/qt5/QtWidgets/"
                    "/usr/include/qt5/QtCore/")

add_executable(memory_game main.cpp MemoryGrid.cpp MemoryCard.cpp MemoryTimer.cpp MemoryWindow.cpp MemoryWindow.h)
set_target_properties(memory_game PROPERTIES AUTOMOC TRUE)
target_link_libraries(memory_game Qt5::Widgets)
