#include "det.h"

double
det(const Eigen::MatrixXd& xs)
{
  return xs.determinant();
}
