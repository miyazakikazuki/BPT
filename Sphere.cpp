#include <Sphere.hpp>
using namespace Eigen;


Sphere::Sphere(Vector3d c, double r) {
	center = c;
	radius = r;
	type = 1;
}

double Sphere::calct(Ray r) {
	double A, B, C, D;
	A = pow(r.dir.norm(), 2);
	B = r.dir.dot(r.pos - this->center);
	C = pow((r.pos - this->center).norm(), 2) - pow(this->radius, 2);
	D = B * B - A * C;
	if (D < 0) {
		return -1.0;
	}
	else {
		return (-B - sqrt(D)) / A;
	}
}