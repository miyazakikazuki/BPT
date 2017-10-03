#ifndef PLANE_HPP
#define PLANE_HPP
#include<Material.hpp>
using namespace Eigen;

class Plane : public Material {
private:
	Vector3d point;
	Vector3d normal;
	Vector2d area;
public:
	Plane(Vector3d p, Vector3d n, Vector2d a);
};
#endif PLANE_HPP
