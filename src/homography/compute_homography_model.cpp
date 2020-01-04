#include "homography/compute_homography_model.hpp"

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/IterativeLinearSolvers>

using namespace Eigen;
using namespace cv;

HomographyModel ComputeHomographyModel::operator()(vector<HomographyMeasurement> m) {
  Matrix<double, 8, 8> A = Matrix<double, 8, 8>::Zero();
  Matrix<double, 8, 1> b = Matrix<double, 8, 1>::Zero();

  // normalize the points
  double m_x=0, m_y=0, d=0;
  double m_xp=0, m_yp=0, dp=0;

  // calculate translation
  for(int i = 0; i < 4; i++) {
    HomographyMeasurement& measurement = m[i];
    float &x = measurement.src.x, &y = measurement.src.y, &xp = measurement.dst.x, &yp = measurement.dst.y;
    m_x += x/4;
    m_y += y/4;
    m_xp += xp/4;
    m_yp += yp/4;
  }
  // calculate distance
  for(int i = 0; i < 4; i++) {
    HomographyMeasurement& measurement = m[i];
    float &x = measurement.src.x, &y = measurement.src.y, &xp = measurement.dst.x, &yp = measurement.dst.y;
    d += sqrt((x-m_x)*(x-m_x) + (y-m_y)*(y-m_y))/4/sqrt(2);
    dp += sqrt((xp-m_xp)*(xp-m_xp) + (yp-m_yp)*(yp-m_yp))/4/sqrt(2);
  }
  // transform points
  for(int i = 0; i < 4; i++) {
    HomographyMeasurement& measurement = m[i];
    float &x = measurement.src.x, &y = measurement.src.y, &xp = measurement.dst.x, &yp = measurement.dst.y;
    x = (x-m_x)/d; 
    y = (y-m_y)/d;
    xp = (xp-m_xp)/dp;
    yp = (yp-m_yp)/dp;
  }

  Matrix3d T = Matrix3d::Zero();
  Matrix3d Tpi = Matrix3d::Zero();
  Matrix3d S = Matrix3d::Zero();
  Matrix3d Spi = Matrix3d::Zero();

  T(0,2) = -m_x;
  T(1,2) = -m_y;
  T(0,0) = T(1,1) = T(2,2) = 1;
  S(0,0) = S(1,1) = 1/d;
  S(2,2) = 1;

  Tpi(0,2) = +m_xp;
  Tpi(1,2) = +m_yp;
  Tpi(0,0) = Tpi(1,1) = Tpi(2,2) = 1;
  Spi(0,0) = Spi(1,1) = dp;
  Spi(2,2) = 1;

  for(int i = 0; i < 4; i++) {
    const HomographyMeasurement& measurement = m[i];
    double x = measurement.src.x, y = measurement.src.y, xp = measurement.dst.x, yp = measurement.dst.y;

    A(2*i,0) = x;
    A(2*i,1) = y;
    A(2*i,2) = 1;
    A(2*i,6) = -x*xp;
    A(2*i,7) = -y*xp;
    // A(2*i,8) = -xp;

    A(2*i+1,3) = x;
    A(2*i+1,4) = y;
    A(2*i+1,5) = 1;
    A(2*i+1,6) = -x*yp;
    A(2*i+1,7) = -y*yp;
    // A(2*i+1,8) = -yp;

    b(2*i) = xp;
    b(2*i+1) = yp;
  }
  // MatrixXd ATA = A.transpose()*A;
  // SelfAdjointEigenSolver<MatrixXd> solver(ATA);
  // auto h = solver.eigenvectors().col(0);
  FullPivLU<MatrixXd> solver(A);
  // b = A.transpose()*b;
  auto h = solver.solve(b);

  Matrix3d H;

  H(0,0) = h(0);
  H(0,1) = h(1);
  H(0,2) = h(2);
  H(1,0) = h(3);
  H(1,1) = h(4);
  H(1,2) = h(5);
  H(2,0) = h(6);
  H(2,1) = h(7);
  // H(2,2) = h(8);
  H(2,2) = 1;
  
  H = Tpi*Spi*H*S*T;
  
  return HomographyModel(H/H(2,2));
};