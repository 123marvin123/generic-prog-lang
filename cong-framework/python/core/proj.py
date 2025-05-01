"""
Proj-Klasse für das Cong-Framework

Eine Klasse, die einen Projektionsausdruck darstellt, der ein bestimmtes Argument aus einer Liste von Argumenten auswählt.
"""

from .base import Base
from .primitive import Number
from .exp import Exp

class _Proj(Base):

    def __init__(self, n):
        if n.value <= 0:
            raise ValueError("Proj benötigt einen Index >= 1")
        self.n = n

    def reduce_space(self):
        return Number(0)

    def reduce_time(self):
        return Number(1)
        
    def reduce_value(self):
        return self
        
    def apply_space(self):
        return Number(0)
        
    def apply_time(self):
        return Number(1)
        
    def apply_value(self, *args):
        index = self.n.value - 1
        
        if index >= len(args):
            raise IndexError(f"Proj({self.n}) benötigt mindestens {self.n} Argumente, aber es wurden {len(args)} übergeben")
        
        return args[index]
        
    def __str__(self):
        return f"Proj({self.n})"
        
    def __repr__(self):
        return f"Proj(n={self.n})"

def Proj(*args, **kwargs):
    return Exp(_Proj(*args, **kwargs))