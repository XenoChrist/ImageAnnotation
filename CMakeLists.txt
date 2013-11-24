cmake_minimum_required(VERSION 2.8)
project(ImageAnnotation)
find_package(OpenCV REQUIRED)

add_executable(create_positive_samples create_positive_samples.cpp)
target_link_libraries(create_positive_samples ${OpenCV_LIBS})