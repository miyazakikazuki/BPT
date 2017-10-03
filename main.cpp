#include <iostream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <Material.hpp>
#include <Plane.hpp>
using namespace Eigen;

int main() {
	Vector3d p;
	Vector3d n;
	Vector2d a;
	p << 0.0, 0.0, 0.0;
	n << 0.0, 1.0, 0.0;
	a << 1.0, 1.0;
	Plane *pl = new Plane(p, n, a);
	Plane *pl2 = new Plane(p, n, a);
	
	MatrixXd input = MatrixXd::Zero(200, 200);
	double* data = new double[input.cols()*input.rows()];
	cv::Mat img(input.cols(), input.rows(), CV_64FC1, data);
	for (int i = 0; i < input.rows(); i++) {
		for (int j = 0; j < input.cols(); j++) {
			data[i * input.cols() + j] = input(input.cols() - i - 1, input.rows() - j);
		}
	}
	cv::namedWindow("image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	cv::imshow("image", img);
	cv::waitKey(0);
}