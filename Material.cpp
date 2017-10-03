#include <Material.hpp>
using namespace Eigen;

int Material::count;

Material::Material() {
	index = count;
	count++;
}

double Material::calct(Ray r) {
	return 0.0;
}