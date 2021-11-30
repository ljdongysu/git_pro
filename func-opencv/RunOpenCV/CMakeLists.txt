cmake_minimum_required(VERSION 3.0.0)
project(RunOpenCV)

set(CMAKE_CXX_STANDARD 14)
#include_directories(/home/indemind/application/tool/opencv/opencv-3.4.3/build/install/include)
#link_directories(/home/indemind/application/tool/opencv/opencv-3.4.3/build/install/lib)
#link_libraries(open_core)
message("CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
set(OpenCV_DIR /home/indemind/application/tool/opencv/opencv-3.4.3/build/install/share/OpenCV/)
find_package(OpenCV REQUIRED)

add_executable(RunOpenCV main.cpp)
target_link_libraries(RunOpenCV  ${OpenCV_LIBS})

set(PROJECT_NAME affinetransform)


add_executable(${PROJECT_NAME} testaffinetransform.cpp)
target_link_libraries(${PROJECT_NAME}  ${OpenCV_LIBS})
message("CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
