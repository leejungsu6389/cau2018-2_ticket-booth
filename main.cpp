#include <iostream>
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world343d.lib")
#else
#pragma comment(lib, "opencv_world343.lib")
#endif
using namespace std;
using namespace cv;
Mat k_downsize(int tar_r,int tar_c,Mat input) {
	double Rr = input.rows/(double)tar_r;
	double Rc = input.cols/(double)tar_c;
	Mat output(tar_r,tar_c,CV_8UC3);
	output.setTo(0);
	for(int i = 0; i<tar_r; i++) {
		int start_y = 0;
		double start_range = 0.0;
		int end_y = 0;
		double end_range = 0.0;
		int p = 0;
		while(1) {
			if(p+1>Rr*i) {
				start_y = p;
				start_range = p+1-(Rr*i);
				break;
			}
			p++;
		}
		while(1) {
			if(p+1>Rr *(i+1)) {
				end_y = p;
				end_range = Rr*(i+1)-p;
				break;
			}
			p++;
		}
		for(int j = 0; j<tar_c; j++) {
			int start_x = 0;
			double xstart_range = 0.0;
			int end_x = 0;
			double xend_range = 0.0;
			int q = 0;
			while(1) {
				if(q+1>Rc*j) {
					start_x = q;
					xstart_range = q+1-(Rc*j);
					break;
				}
				q++;
			}
			while(1) {
				if(q+1>Rc *(j+1)) {
					end_x = q;
					xend_range = Rc*(j+1)-q;

					break;
				}
				q++;
			}
			double accumr = 0.0;
			double accumg = 0.0;
			double accumb = 0.0;
			for(int n = start_y; n<=end_y; n++) {
				for(int m = start_x; m<=end_x; m++) {
					double ratio = 1.0;
					if(start_y!=end_y) {
						if(n==start_y) {
							ratio *= start_range;
						}
						if(n==end_y) {
							ratio *= end_range;
						}
					}
					else {
						ratio *= 1-(2-start_range-end_range);
					}
					if(start_x!=end_x) {
						if(m==start_x) {
							ratio *= xstart_range;
						}
						if(m==end_x) {
							ratio *= xend_range;
						}
					}
					else {
						ratio *= 1-(2-xstart_range-xend_range);
					}
					accumr += (ratio)* input.data[(n*input.step)+(m*input.elemSize())+0];
					accumg += (ratio)* input.data[(n*input.step)+(m*input.elemSize())+1];
					accumb += (ratio)* input.data[(n*input.step)+(m*input.elemSize())+2];
				}
			}
			output.data[i*output.step+j*output.elemSize()+0] += (unsigned char)(accumr/(Rr*Rc));
			output.data[i*output.step+j*output.elemSize()+1] += (unsigned char)(accumg/(Rr*Rc));
			output.data[i*output.step+j*output.elemSize()+2] += (unsigned char)(accumb/(Rr*Rc));
		}
	}
	return output;
}
int main() {
	Mat frame = imread("Avril.jpg",1);
	Mat test = k_downsize(2000,2000,frame);
	namedWindow("test",0);
	imshow("avril",frame);
	imshow("test",test);
	waitKey(0);
	return 0;
}
