from .exp import Exp
from .base import Base

class Val(Base):
    def reduce_space(self):
        from .primitive import Number
        return Exp(Number(0))

    def reduce_time(self):
        from .primitive import Number
        return Exp(Number(1))

    def apply_space(self):
        from .primitive import Number
        return Exp(Number(0))

    def apply_time(self):
        from .primitive import Number
        return Exp(Number(1))
        
    def apply_value(self, *args):
        return args[0] if args else self