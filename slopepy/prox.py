import _slopepy

class Prox:
    """The Sorted L1 Prox

    Evaluate the proximal operator for the sorted L1 norm,

    .. math:: 

       \operatorname*{arg\,min}_x \left(J(x) + \frac 1 2 \lVert x - v \rVert_2^2\right)

    where :math:`J(x) = \sum_{i=1}\lambda_i|\beta_{(i)}|` is the 
    sorted :math:`\ell_1` norm.

    Parameters
    ----------
    x : array
        x in the defintion above, typically the coefficients
        
    v : array
        v in the definition above, typically the regularization weights
    
    Returns
    -------
    array
        An evaluation of the proximal operator
    """
    def __init__(self, v):
        self.v = v

    def eval(self, x):
        return _slopepy.sorted_l1_prox(x, self.v, 0)

