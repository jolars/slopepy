import os
from glob import glob

import pybind11
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import Extension, setup

__version__ = "0.0.1"

# The main interface is through Pybind11Extension.
# * You can add cxx_std=11/14/17, and then build_ext can be removed.
# * You can set include_pybind11=false to add the include directory yourself,
#   say from a submodule.
#
# Note:
#   Sort input source files if you glob sources to ensure bit-for-bit
#   reproducible builds (https://github.com/pybind/python_example/pull/53)

localincl = "extern"
eigen_ver = "3.4.0"

if not os.path.exists(os.path.join(localincl, "eigen-" + eigen_ver, "Eigen", "Core")):
    raise RuntimeError("couldn't find Eigen headers")

include_dirs = [
    os.path.join(localincl, "eigen-" + eigen_ver),
]

ext_modules = [
    Pybind11Extension(
        "_slopepy",
        sources=sorted(glob("src/**/*.cpp", recursive=True)),
        define_macros=[("VERSION_INFO", __version__)],
        cxx_std=14,
        include_dirs=include_dirs,
    ),
]

# cpp_args = ['-std=c++14', '-undefined dynamic_lookup', '-shared']

# ext_modules = [
#     Extension(
#         "_slopepy",
#         sorted(glob("src/*.cpp")),
#         include_dirs=[pybind11.get_include(), 'extern/eigen-3.4.0'],
#         language='c++',
#         extra_compile_args=cpp_args,
#     ),
# ]

setup(
    name="slopepy",
    version=__version__,
    author="Johan Larsson",
    author_email="johanlarsson@outlook.com",
    url="https://github.com/jolars/slopepy",
    description="Sorted L-One Penalized Estimation",
    long_description="",
    ext_modules=ext_modules,
    install_requires=["numpy"],
    # extras_require={"test": "pytest"},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    # cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
