#include <Ray.hpp>
using namespace Eigen;

Ray::Ray(Vector3d p, Vector3d d) {
	pos = p;
	dir = d;
}

