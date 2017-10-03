#include <Camera.hpp>
using namespace Eigen;


Camera::Camera(Vector3d p, Vector3d n, Vector2d a) {
	point = p;
	normal = n;
	area = a;
	type = 0;
}