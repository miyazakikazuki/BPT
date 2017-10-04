#define EIGEN_NO_DEBUG // コード内のassertを無効化．
#define EIGEN_DONT_PARALLELIZE // 並列を無効化．
#define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．
#define PI 3.141592653589793;

#include <iostream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Plane.hpp>
#include <Sphere.hpp>
#include<Ray.hpp>
using namespace Eigen;
const int N = 100;


MatrixXd Pathtracing(
	MatrixXd input,
	class Plane eye,
	class Plane lens,
	class Plane light
);

double Le(Vector3d x, Vector3d wo);
double BSDF(Vector3d x, Vector3d wi, Vector3d wo);




int main(int argc, char const *argv[]) {
	/* code */
	MatrixXd input = MatrixXd::Zero(200, 200);
	Plane *eye, *lens, *light;
	Vector3d ep, en, lep, len, lip, lin;
	Vector2d ea, lea, lia;
	ep << 5.0, 0.0, 0.0;
	ea << 0.1, 0.1;
	en = -ep.normalized();
	lep << 3.2, 0.0, 0.0;
	lea << 1.0, 1.0;
	len = -lep.normalized();
	lip << 0.0, 4.0, 3.0;
	lia << 1.0, 1.0;
	lin = -lip.normalized();
	eye = new Plane(ep, en, ea);
	lens = new Plane(lep, len, lea);
	light = new Plane(lip, lin, lia);
	
	input = Pathtracing(input, *eye, *lens, *light);

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

MatrixXd Pathtracing(
	MatrixXd input,
	Plane eye,
	Plane lens,
	Plane light)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<double> point(0.0, 1.0);

	Vector3d xp, x0;
	Vector3d x, tangent;
	tangent.x() = eye.normal.z() / sqrt(eye.normal.x() * eye.normal.x() + eye.normal.z() * eye.normal.z());
	tangent.y() = 0;
	tangent.z() = -eye.normal.x() / sqrt(eye.normal.x() * eye.normal.x() + eye.normal.z() * eye.normal.z());
	Vector3d binormal = eye.normal.cross(tangent);
	Ray ray = { Vector3d::Zero(), Vector3d::Zero() };
	//オブジェクトの設定
	Plane horizontal = { Vector3d::Zero(), Vector3d::Zero(),  Vector2d::Zero() };
	horizontal.point << 0.0, -1.0, 0.0;
	horizontal.normal << 0.0, 1.0, 0.0;
	horizontal.area << 1.0, 1.0;
	Sphere unitsphere = { Vector3d::Zero(), 1.0 };
	double A, B, C, D;

	Vector3d raynormal, wo, wi;

	double t = 0.0, tplane, tsphere, tlight;
	int paramflag;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < input.rows(); j++) {
			for (int k = 0; k < input.cols(); k++) {
				xp = eye.point + ((k + point(mt)) / input.cols() - 0.5) * eye.area.x() * tangent
					+ ((j + point(mt)) / input.rows() - 0.5) * eye.area.y() * binormal;

				double paxp = input.cols() * input.rows() / (eye.area.x() * eye.area.y());

				x0 = lens.point + ((k + point(mt)) / input.cols() - 0.5) * lens.area.x() * tangent
					+ ((j + point(mt)) / input.rows() - 0.5) * lens.area.y() * binormal;
				double pax0 = input.cols() * input.rows() / (lens.area.x() * lens.area.y());

				ray.pos = x0;
				ray.dir = (x0 - xp).normalized();
				double psigma = 1.0 / 2.0 * PI;
				double alpha = 1.0;

				do {
					tplane = horizontal.calct(ray);
					tlight = light.calct(ray);
					tsphere = unitsphere.calct(ray);

					tplane = 1.0 / tplane;
					tlight = 1.0 / tlight;
					tsphere = 1.0 / tsphere;

					if (tlight < tplane) {
						if (tplane < tsphere) {
							t = tsphere;
							paramflag = 2;
						}
						else {
							t = tplane;
							paramflag = 0;
						}
					}
					else if (tlight < tsphere) {
						t = tsphere;
						paramflag = 2;
					}
					else {
						t = tlight;
						paramflag = 3;
					}
					t = fmax(t, 0);

					if (t <= 0) break;

					x = ray.pos + ray.dir / t;
					wo = -ray.dir;
					switch (paramflag) {
					case 0:
						raynormal = horizontal.normal;
						break;
					case 1:
					case 2:
						raynormal = x - unitsphere.center;
						break;
					case 3:
						input(j, k) = input(j, k) + alpha * Le(x, wo);
						break;
					}
					if (paramflag == 3) {
						break;
					}
					wi << point(mt), point(mt), point(mt);
					if (wi.dot(raynormal) < 0) {
						wi = -wi;
					}
					wi = wi / wi.norm();

					double psigmawi = 1.0;

					alpha = alpha * BSDF(x, wi, wo) * wi.dot(raynormal) / psigmawi;

					double prr = 0.5;

					if (point(mt) > prr) {
						break;
					}
					ray.pos = x;
					ray.dir = wi;

					alpha = alpha / prr;
				} while (t > 0.0);
			}
		}
		std::cout << "loading..." << (double)i / (double)N * 100.0 << "%" << std::endl;
	}

	return input / (double)N;
}

double Le(Vector3d x, Vector3d wo) {
	return 1.0;
}

double BSDF(Vector3d x, Vector3d wi, Vector3d wo) {
	return 1.0;
}