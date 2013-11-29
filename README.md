ImageAnnotation
===============

An Image Annotator software developed with OpenCV.

The system detects objects like

1. Humans
2. Cars

Building and running the system
-------------------------------

1. cmake .
2. make
3. ./create_positive_samples
4. ./create_negative_samples
5. perl createtrainsamples.pl
6. ./mergevec
7. opencv_traincascade
8. ./test_classifier
