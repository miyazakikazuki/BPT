#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#define EIGEN_NO_DEBUG // コード内のassertを無効化．
#define EIGEN_DONT_PARALLELIZE // 並列を無効化．
#define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．
#include <Eigen/Core>
using namespace Eigen;

struct Material {
	static int count;
	int index;//マテリアル番号
	int type;//マテリアルの種類
	Material();
};
#endif MATERIAL_HPP