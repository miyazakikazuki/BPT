#include <Light.hpp>
using namespace Eigen;


Light::Light(Vector3d p, Vector3d n, Vector2d a) {
	point = p;
	normal = n;
	area = a;
}