#include "homography/compute_homography_model.hpp"

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace Eigen;
using namespace cv;

HomographyModel ComputeHomographyModel::operator()(const vector<HomographyMeasurement>& m) {
  // TODO: implement this function
  m.size();
  Matrix<double, 8, 9> A = Matrix<double, 8, 9>::Zero();
  // Vector<double, 8> b = Vector<double, 8>::Zero();
  for(int i = 0; i < 4; i++) {
    const HomographyMeasurement& measurement = m[i];
    double x = measurement.src.x, y = measurement.src.y, xp = measurement.dst.x, yp = measurement.dst.y;

    A(2*i,0) = x;
    A(2*i,1) = y;
    A(2*i,2) = 1;
    A(2*i,6) = -x*xp;
    A(2*i,7) = -y*xp;
    A(2*i,8) = -xp;

    A(2*i+1,3) = x;
    A(2*i+1,4) = y;
    A(2*i+1,5) = 1;
    A(2*i+1,6) = -x*yp;
    A(2*i+1,7) = -y*yp;
    A(2*i+1,8) = -yp;

    // b(2*i) = xp;
    // b(2*i+1) = yp;
  }
  MatrixXd ATA = A.transpose()*A;
  SelfAdjointEigenSolver<MatrixXd> solver(ATA);
  auto h = solver.eigenvectors.col(0);

  Matrix3d H;
  H(0,0) = h(0);
  H(0,1) = h(1);
  H(0,2) = h(2);
  H(1,0) = h(3);
  H(1,1) = h(4);
  H(1,2) = h(5);
  H(2,0) = h(6);
  H(2,1) = h(7);
  H(2,2) = h(8);
  
  return HomographyModel(H);
};