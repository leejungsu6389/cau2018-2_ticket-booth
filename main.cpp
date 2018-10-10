#include <iostream>
#include <random>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>
#include <opencv\cvaux.h>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world343d.lib")
#else
#pragma comment(lib, "opencv_world343.lib")
#endif
using namespace std;
using namespace cv;
Mat cvDilation(Mat input,int erosion_size,int erosion_type) {
	/*erosion_type = MORPH_RECT, MORPH_CROSS,MORPH_ELLIPSE*/
	Mat output = input.clone();
	Mat element = getStructuringElement(erosion_type,Size(2*erosion_size+1,2*erosion_size+1),Point(erosion_size,erosion_size));
	dilate(input,output,element);
	return output;
}
Mat cvErosion(Mat input,int erosion_size,int erosion_type) {
	/*erosion_type = MORPH_RECT, MORPH_CROSS,MORPH_ELLIPSE*/
	Mat output = input.clone();
	Mat element = getStructuringElement(erosion_type,Size(2*erosion_size+1,2*erosion_size+1),Point(erosion_size,erosion_size));
	erode(input,output,element);
	return output;
}
int main(void) {
	VideoCapture stream("People.mp4");
	Mat capture;
	Ptr<BackgroundSubtractor> pMOG2;
	vector<vector <Point>> contours;
	vector<Vec4i> hierarchy;
	char cau[] = "Ticket_Booth_cau";
	while(1) {
		if(!stream.read(capture)) {
			break;
		}
		Mat store = capture.clone();
		cvtColor(capture,capture,CV_RGB2GRAY);
		GaussianBlur(capture,capture,Size(7,7),1.5,1.5);
		threshold(capture,capture,128,255,CV_THRESH_BINARY);
		cvErosion(capture,10,MORPH_RECT);
		cvDilation(capture,10,MORPH_RECT);
		cvDilation(capture,10,MORPH_RECT);
		cvErosion(capture,25,MORPH_RECT);
		findContours(capture.clone(),contours,hierarchy,RETR_CCOMP,CHAIN_APPROX_SIMPLE);
		vector<vector<Point> > contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());
		for(int i = 0; i<contours.size(); i++) {
			approxPolyDP(Mat(contours[i]),contours_poly[i],3,true);
			boundRect[i] = boundingRect(Mat(contours_poly[i]));
		}
		for(int i = 0; i<contours.size(); i++) {
			rectangle(store,boundRect[i].tl(),boundRect[i].br(),Scalar(0,255,0),1,8,0);
		}
		putText(store,cau,Point(30,20),CV_FONT_NORMAL,1,Scalar(0,0,0),2,1);
		imshow("capture",store);
		waitKey(100);
	}
	waitKey(0);
	return 0;
}