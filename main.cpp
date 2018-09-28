#include <iostream>
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world343d.lib")
#else
#pragma comment(lib, "opencv_world343.lib")
#endif
using namespace std;
using namespace cv;
void processVideo(char* video_name) {
	VideoCapture capture(video_name);
	Ptr<BackgroundSubtractor> pKNN;
	Ptr<BackgroundSubtractor> pMOG2;
	Mat fgMaskMOG2;
	Mat fgMaskKNN;
	Mat frame;
	double start;
	double end_time;
	pKNN = createBackgroundSubtractorKNN(500,400,true);
	pMOG2 = createBackgroundSubtractorMOG2(500,400,true);
	while(!capture.isOpened()) {
		std::cout<<"error"<<std::endl;
		exit(EXIT_FAILURE);
	}
	int count = 0;
	int flag = 0;
	start = clock();
	
	while(1) {
		if(!capture.read(frame)) {
			std::cout<<"file end"<<std::endl;
			break;
		}
		pKNN->apply(frame,fgMaskKNN);
		pMOG2->apply(frame,fgMaskMOG2);
		imshow("KNN",fgMaskKNN);
		imshow("MOG2",fgMaskMOG2);
		if(count>100 && flag == 0) {
			flag = 1;
			double end = clock();
		}
		waitKey(100);
		count++;
	}
}
int main() {
	char f_name[] = "People.mp4";
	processVideo(f_name);
	return 0;
}