#ifndef CAMERA_HPP
#define CAMERA_HPP
#include<Material.hpp>
using namespace Eigen;

class Plane : public Material {
private:
	Vector3d point;
	Vector3d normal;
	Vector2d area;
public:
	Camera(Vector3d p, Vector3d n, Vector2d a);
};
#endif CAMERA_HPP
