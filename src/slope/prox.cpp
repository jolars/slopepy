#include "prox.h"
#include "utils.h"
#include <iostream>

// #include "prox.h"
// #include "sortIndex.h"

// Stack-based algorithm (Algorithm 4 in Bogdan et al. 2015)
void
proxStack(Eigen::VectorXd& x, const Eigen::VectorXd& lambda)
{
  using namespace Eigen;

  typedef Matrix<size_t, Dynamic, 1> VectorXu;

  size_t p = x.size();

  VectorXd s(p);
  VectorXd w(p);
  VectorXu idx_i(p);
  VectorXu idx_j(p);

  size_t k = 0;

  for (size_t i = 0; i < p; i++) {
    idx_i[k] = i;
    idx_j[k] = i;
    s[k]     = x[i] - lambda[i];
    w[k]     = s[k];

    while ((k > 0) && (w[k - 1] <= w[k])) {
      k--;
      idx_j[k] = i;
      s[k] += s[k + 1];
      w[k] = s[k] / (i - idx_i[k] + 1.0);
    }
    k++;
  }

  for (size_t j = 0; j < k; j++) {
    double d = std::max(w[j], 0.0);
    for (size_t i = idx_i[j]; i <= idx_j[j]; i++) {
      x[i] = d;
    }
  }
}

// void
// proxPava(Eigen::VectorXd& y, const Eigen::VectorXd& lambda)
// {
//   using namespace Eigen;

//   size_t n = y.size();

//   VectorXd yc(n + 1);
//   double tmp{ 0 };

//   double slope{ 0 };

//   yc[0]      = 0;
//   yc.tail(n) = cumSum(y - lambda);

//   size_t known = 0;
//   size_t ip    = 0;

//   auto INF = std::numeric_limits<double>::infinity();

//   do {
//     slope = -INF;

//     for (size_t i = known + 1; i <= n; ++i) {
//       tmp = (yc[i] - yc[known]) / (i - known);

//       if (tmp > slope) {
//         slope = tmp;
//         ip    = i;
//       }
//     }

//     for (size_t i = known; i < ip; ++i) {
//       y(i) = (yc[ip] - yc[known]) / (ip - known);
//     }

//   } while ((known = ip) < n);

//   // std::for_each(
//   //   y.begin(), y.end(), [](double& y_i) { y_i = std::max(y_i, 0.0); });

//   for (auto& y_i : y) {
//     y_i = std::max(y_i, 0.0);
//   }
// }

Eigen::MatrixXd
prox(const Eigen::MatrixXd& beta,
     const Eigen::VectorXd& lambda,
     const ProxMethod prox_method)
{
  using namespace Eigen;

  size_t p = beta.rows();
  size_t m = beta.cols();

  // collect sign of beta and work with sorted absolutes
  VectorXd beta_vec       = beta.reshaped(p * m, 1).eval();
  const ArrayXd beta_sign = beta_vec.cwiseSign();
  beta_vec                = beta_vec.cwiseAbs();

  const auto ord = sortIndex(beta_vec, "descending");
  // beta_vec = beta_vec(ord).eval();

  permute(beta_vec, ord);

  print(beta_vec);

  switch (prox_method) {
    case ProxMethod::stack:
      proxStack(beta_vec, lambda);
      break;
    case ProxMethod::pava:
      // prox_pava(beta_vec, lambda);
      break;
  }

  print(beta_vec);

  // reset permutation and signs
  // beta_vec(ord) = beta_vec;
  inversePermute(beta_vec, ord);

  print(beta_vec);

  beta_vec.array() *= beta_sign;

  const MatrixXd beta_out = beta_vec.reshaped(p, m).eval();

  return beta_out;
}
