#include <iostream>
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world343d.lib")
#else
#pragma comment(lib, "opencv_world343.lib")
#endif
using namespace std;
using namespace cv;
int main() {
	VideoCapture stream("walking.mp4");
	Mat frame;
	Mat sub_frame;
	Mat old_frame;
	int flag = 1;
	while(1) {
		stream.read(frame);
		if(frame.empty()) {
			if(flag==1) {
				flag = 0;
				old_frame = frame.clone();
			}
			else {
				break;
			}
		}
		Sobel(frame,frame,CV_8U,1,0);
		sub_frame = frame-old_frame;
		imshow("walking",sub_frame);
		waitKey(100);
		old_frame = frame.clone();
	}
	waitKey(0);
	return 0;
}