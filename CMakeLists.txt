PROJECT(ImageAnnotation)
cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE( OpenCV 2.3 REQUIRED )
message(${OpenCV_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

set (CMAKE_CXX_FLAGS -fopenmp )

ADD_EXECUTABLE(create_positive_samples create_positive_samples.cpp)
TARGET_LINK_LIBRARIES(create_positive_samples ${OpenCV_LIBS})

ADD_EXECUTABLE(create_negative_samples create_negative_samples.cpp)
TARGET_LINK_LIBRARIES(create_negative_samples ${OpenCV_LIBS})

ADD_EXECUTABLE(test_classifier test_classifier.cpp)
TARGET_LINK_LIBRARIES(test_classifier ${OpenCV_LIBS})