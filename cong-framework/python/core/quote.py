from .base import Base
from .exp import Exp


class _Quote(Base):

    def __init__(self, exp):
        self._exp = exp

    def apply_value(self, *args):
        return self._exp

    def reduce_value(self):
        return self._exp

    def __str__(self):
        return f"Quote({self._exp})"

    def __repr__(self):
        return f"Quote({self._exp})"


def Quote(*args, **kwargs):
    return Exp(_Quote(*args, **kwargs))