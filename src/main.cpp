#include <Eigen/Core>
#include <Eigen/LU>
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "slope/prox.h"
#include "det.h"

int
add(int i, int j)
{
  return i + j;
}

Eigen::MatrixXd
inv(const Eigen::MatrixXd& xs)
{
  return xs.inverse();
}

double
detExport(const Eigen::MatrixXd& xs)
{
  return det(xs);
}

Eigen::MatrixXd
proxExport(const Eigen::MatrixXd& beta,
           const Eigen::VectorXd& lambda,
           const int method)
{
  auto prox_method = ProxMethod(method);

  return prox(beta, lambda, prox_method);
}

PYBIND11_MODULE(_slopepy, m)
{
  m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

  m.def(
    "subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

  m.def("inv", &inv, "Compute the inverse of a matrix.");

  m.def("detxx", &detExport, "Compute the determinant of a matrix.");

  m.def("sorted_l1_prox", &proxExport, "Return the Sorted L1 Prox");
}
