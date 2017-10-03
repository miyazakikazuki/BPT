#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#define EIGEN_NO_DEBUG // �R�[�h����assert�𖳌����D
#define EIGEN_DONT_PARALLELIZE // ����𖳌����D
#define EIGEN_MPL2_ONLY // LGPL���C�Z���X�̃R�[�h���g��Ȃ��D
#include <Eigen/Core>
#include <Ray.hpp>
using namespace Eigen;

class Material {
private:
	static int count;
	int index;//�}�e���A���ԍ�
protected:
	int type;//�}�e���A���̎��
public:
	Material();
	double calct(Ray r);
};
#endif MATERIAL_HPP