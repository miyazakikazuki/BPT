#include <Material.hpp>
using namespace Eigen;

int Material::count;

Material::Material() {
	index = count;
	count++;
}

