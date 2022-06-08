import unittest

import numpy as np

import slopepy


class TestLinearAlgebra(unittest.TestCase):
    def test_prox(self):
        beta = np.array([0.2, -0.5, 0.01])
        lam = np.array([0.4, 0.1, 0.02])

        prox = slopepy.Prox(lam)
        res = prox.eval(beta)

        ref = np.array([[0.1], [-0.1], [0.0]])

        self.assertIsNone(np.testing.assert_array_almost_equal(res, ref),
                          "Prox is not working")

        beta = np.array([0.2, -0.5, 0.01])
        lam = np.array([0.2, 0.2, 0.2])

        prox = slopepy.Prox(lam)
        res = prox.eval(beta)

        ref = np.array([[0.0], [-0.3], [0.0]])

        self.assertIsNone(np.testing.assert_array_almost_equal(res, ref),
                          "Prox is not working")


if __name__ == '__main__':
    unittest.main()
