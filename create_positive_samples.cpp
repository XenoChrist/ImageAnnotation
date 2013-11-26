// Program to create the positive samples file.

#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace cv;
using namespace std;

Point origin;
Rect selection;
Mat image;
bool selectObject;

void onMouse( int event, int x, int y, int, void* )
{
    if( selectObject )
    {
        selection.x = MIN(x, origin.x);
        selection.y = MIN(y, origin.y);
        selection.width = std::abs(x - origin.x);
        selection.height = std::abs(y - origin.y);
		
        selection &= Rect(0, 0, image.cols, image.rows);
    }
	
    switch( event )
    {
		case CV_EVENT_LBUTTONDOWN:
			origin = Point(x,y);
			selection = Rect(x,y,0,0);
			selectObject = true;
			break;
		case CV_EVENT_LBUTTONUP:
			selectObject = false;
			break;
    }
}

int main(int argc, char * const argv[]) {

	if(argc < 3)
	{
		cout << "USAGE:" << endl;
		cout << argv[0] << " <input_directory> <output_file>" << endl;
		return 1;
	}
	string dir(argv[1]), filepath;
	DIR *dp;
	dirent *ent;
	struct stat filestat;
	int count = 0;

	namedWindow("image");
	setMouseCallback( "image", onMouse, 0 );
		
	ofstream ofs(argv[2], fstream::out);
	
	Mat img;
	bool running = true;
	dp = opendir(dir.c_str());
	while ((ent = readdir(dp)) && running)
    {
    	count = 0;
    	stringstream ss;
		filepath = dir + "/" + ent->d_name;
		
		// If the file is a directory (or is in some way invalid) we'll skip it 
		if (stat(filepath.c_str(), &filestat))		continue;	//can't be openedz
		if (S_ISDIR(filestat.st_mode))				continue;	//a directory
		if (ent->d_name[0] == '.')					continue;	//hidden file

		cout << filepath << endl;
		ofs << filepath << " ";
		img = imread(filepath);
		Point text_place(20,40);
		while (true) {
			img.copyTo(image);
			if( selection.width > 0 && selection.height > 0 )
			{
				Mat roi(image, selection);
				bitwise_not(roi, roi);
			}
			imshow("image", image);
			int c = waitKey(10);
			
			if (c == ' ') {
				// ofs << endl;
				break;
			} else if (c == 27) {
				running = false;
				break;
			} else if (c != -1) {
				count++;
				if(selection.width != 0)
				{
					ss << selection.x << " " << selection.y << " " << selection.width << " " << selection.height << "  ";
				}
				selection = Rect(); 
			}
		}
		ofs << count << " " << ss.str() << endl;
    }
	closedir(dp);
	
	ofs.close();
}
