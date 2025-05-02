
from .base import Base
from .exp import Exp

class _Proj(Base):

    def __init__(self, n):
        if n.value <= 0:
            raise ValueError("Proj benötigt einen Index >= 1")
        self.n = n
        
    def apply_value(self, *args):
        index = self.n.value - 1
        
        if index >= len(args):
            return Exp(self)
        
        return args[index]
        
    def __str__(self):
        return f"Proj({self.n})"
        
    def __repr__(self):
        return f"Proj(n={self.n})"

def Proj(*args, **kwargs):
    return Exp(_Proj(*args, **kwargs))