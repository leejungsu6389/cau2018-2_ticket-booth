#include <iostream>
#include <random>
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world343d.lib")
#else
#pragma comment(lib, "opencv_world343.lib")
#endif
using namespace std;
using namespace cv;
void Erosion(Mat input,Mat output,int erosion_size, int erosion_type) {
	/*erosion_type = MORPH_RECT, MORPH_CROSS,MORPH_ELLIPSE*/
	Mat element = getStructuringElement(erosion_type,Size(2*erosion_size+1,2*erosion_size+1),Point(erosion_size,erosion_size));
	erode(input,output,element);
}
void Dilation(Mat input,Mat output,int erosion_size,int erosion_type) {
	/*erosion_type = MORPH_RECT, MORPH_CROSS,MORPH_ELLIPSE*/
	Mat element = getStructuringElement(erosion_type,Size(2*erosion_size+1,2*erosion_size+1),Point(erosion_size,erosion_size));
	dilate(input,output,element);
}
int main() {
	Mat capture;
	Ptr<BackgroundSubtractor> pKNN;
	pKNN = createBackgroundSubtractorKNN(500,400,true);
	VideoCapture stream("People.mp4");
	while(1) {
		if(!stream.read(capture)) {
			break;
		}
		imshow("video",capture);
		Erosion(capture,capture,3,MORPH_CROSS);
		Dilation(capture,capture,3,MORPH_CROSS);
		Dilation(capture,capture,3,MORPH_ELLIPSE);
		Erosion(capture,capture,3,MORPH_ELLIPSE);
		Dilation(capture,capture,3,MORPH_ELLIPSE);
		Erosion(capture,capture,3,MORPH_RECT);
		pKNN->apply(capture,capture);
		imshow("test",capture);
		waitKey(100);
	}
	return 0;
}
