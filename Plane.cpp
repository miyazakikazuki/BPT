#include <Plane.hpp>
using namespace Eigen;


Plane::Plane(Vector3d p, Vector3d n, Vector2d a) {
	point = p;
	normal = n;
	area = a;
	type = 0;
}