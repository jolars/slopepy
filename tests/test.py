import unittest

import numpy as np

import pyslope

# assert pyslope.add(1, 2) == 3
# assert pyslope.subtract(1, 2) == -1

# assert pyslope.subtract(1, 2) == -1

class TestLinearAlgebra(unittest.TestCase):
    def test_det(self):
        a = np.array([[1, 0.1], [0.1, 1]])
        det = pyslope.det(a)
        self.assertEqual(det, 0.99, "0.99")

    def test_add(self):
        self.assertEqual(pyslope.add(1, 2), 3, "Should be 3")

if __name__ == '__main__':
    unittest.main()
