#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay(Mat frame);

/** Global variables */
String human_cascade_name = "human_cascade.xml";
CascadeClassifier human_cascade;
String window_name = "ImageAnnotation";

int main(int argc, char const *argv[])
{
	// Check for image to be read
	if(argc < 2)
	{
		cout << "USAGE:" << endl;
		cout << argv[0] << " <input_image>" << endl;
		return -1;
	}

	// Load the cascades
	if(!human_cascade.load(human_cascade_name))
	{ 
		cout << "Error loading human cascade" << endl;
		return -1; 
	}

	// Read the image
	Mat frame = imread(argv[1]);

	namedWindow(window_name);

	// Apply the classifiers to the image
	detectAndDisplay(frame);

	return 0;
}

void detectAndDisplay(Mat frame)
{
	std::vector<Rect> humans;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    cout << "before detect\n";
    // Detect humans
    human_cascade.detectMultiScale(frame_gray, humans, 1.1, 2, 0, Size(40, 80));
    cout << "after detect " << humans.size() << endl;
    for(size_t i = 0; i < humans.size(); i++)
    {
    	Rect r(humans[i].x, humans[i].y, humans[i].width, humans[i].height);
    	cout << "Human Detected! At..." << endl;
    	cout << "x - " << humans[i].x << endl;
    	cout << "y - " << humans[i].y << endl;
    	cout << "width - " << humans[i].width << endl;
    	cout << "height - " << humans[i].height << endl;
    	rectangle(frame, r, Scalar(0, 255, 255), 5);
    }
    imshow(window_name, frame);
    waitKey(0);
}