#ifndef LIGHT_HPP
#define LIGHT_HPP
using namespace Eigen;

class Light{
private:
	Vector3d point;
	Vector3d normal;
	Vector2d area;
public:
	Light(Vector3d p, Vector3d n, Vector2d a);
};
#endif LIGHT_HPP
