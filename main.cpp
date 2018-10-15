#include <iostream>
#include <random>
#include <math.h>
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world343d.lib")
#else
#pragma comment(lib, "opencv_world343.lib")
#endif
using namespace std;
using namespace cv;

Mat km_sobel(Mat input) {
	Mat applied(input.rows-2,input.cols-2,input.type());
	applied.setTo(0);
	int sobelX[9] = {-1,0,1,-2,0,2,-1,0,1};
	int sobelY[9] = {-1,-2,-1,0,0,0,1,2,1};
	for(int i = 0; i<applied.rows; i++) {
		for(int j = 0; j<applied.cols; j++) {
			for(int c = 0; c<input.type(); c++) {
				double x = 0;
				double y = 0;
				for(int p = 0; p<3; p++) {
					for(int q = 0; q<3; q++) {
						x += (double)input.data[(i+p)*input.step+(j+q)*input.elemSize()+c]*sobelX[p*3+q];
						y += (double)input.data[(i+p)*input.step+(j+q)*input.elemSize()+c]*sobelY[p*3+q];
					}
				}
				if(x<0) {
					x = -x;
				}
				if(y<0) {
					y = -y;
				}
				applied.data[i*applied.step+j*applied.elemSize()+c] = 0.5*(x+y);
			}
		}
	}
	return applied;
}
Mat km_dilate(Mat input,int filt_size) {
	Mat applied(input.rows-filt_size+1,input.cols-filt_size+1,input.type());
	applied.setTo(0);
	for(int i = 0; i<applied.rows; i++) {
		for(int j = 0; j<applied.cols; j++) {
			for(int c = 0; c<input.elemSize(); c++) {
				int max = input.data[i*input.step+j*input.elemSize()+c];
				for(int p = 0; p<filt_size; p++) {
					for(int q = 0; q<filt_size; q++) {
						if(max<input.data[(i+p)*input.step+(j+q)*input.elemSize()+c]) {
							max = input.data[(i+p)*input.step+(j+q)*input.elemSize()+c];
						}
					}
				}
				applied.data[i*applied.step+j*applied.elemSize()+c] = max;
			}
		}
	}
	return applied;
}
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
Mat km_erode(Mat input,int filt_size) {
	Mat applied(input.rows-filt_size+1,input.cols-filt_size+1,input.type());
	applied.setTo(0);
	for(int i = 0; i<applied.rows; i++) {
		for(int j = 0; j<applied.cols; j++) {
			for(int c = 0; c<input.elemSize(); c++) {
				int min = input.data[i*input.step+j*input.elemSize()+c];
				for(int p = 0; p<filt_size; p++) {
					for(int q = 0; q<filt_size; q++) {
						if(min>input.data[(i+p)*input.step+(j+q)*input.elemSize()+c]) {
							min = input.data[(i+p)*input.step+(j+q)*input.elemSize()+c];
						}
					}
				}
				applied.data[i*applied.step+j*applied.elemSize()+c] = min;
			}
		}
	}
	return applied;
}
int main(void)
{
	Mat img = imread("avrill.jpg");
	Mat kmDilate = km_dilate(img,9);
	Mat kmErode = km_erode(img,9);
	Mat kmsobel = km_sobel(img);
	namedWindow("km_dilate",0);
	namedWindow("km_erode",0);
	namedWindow("kmsobel",0);
	imshow("km_dilate",kmDilate);
	imshow("km_erode",kmErode);
	imshow("kmsobel",kmsobel);
	waitKey(0);
	return(0);

}