#ifndef SPHERE_HPP
#define SPHERE_HPP
#include<Material.hpp>
using namespace Eigen;

class Sphere : public Material {
private:
	Vector3d center;
	double radius;
public:
	Sphere(Vector3d c, double r);
};
#endif SPHERE_HPP
