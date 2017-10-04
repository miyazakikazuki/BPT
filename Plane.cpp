#include <Plane.hpp>
using namespace Eigen;


Plane::Plane(Vector3d p, Vector3d n, Vector2d a) {
	point = p;
	normal = n;
	area = a;
	type = 0;
}

double Plane::calct(Ray r) {
	return (this->point - r.pos).dot(this->normal) / r.dir.dot(this->normal);
}