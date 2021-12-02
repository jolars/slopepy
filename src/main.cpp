#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <Eigen/Core>
#include <Eigen/LU>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

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
det(const Eigen::MatrixXd& xs)
{
  return xs.determinant();
}

namespace py = pybind11;

PYBIND11_MODULE(_pyslope, m)
{
  m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: pyslope

        .. autosummary::
           :toctree: _generate

           add
           subtract
           inv
           det
    )pbdoc";

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

  m.def("det", &det, "Compute the determinant of a matrix.");

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
