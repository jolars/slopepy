#pragma once

#include <Eigen/Dense>

enum class ProxMethod
{
  stack = 0,
  pava  = 1
};

Eigen::MatrixXd
prox(const Eigen::MatrixXd& beta,
     const Eigen::VectorXd& lambda,
     const ProxMethod prox_method);
