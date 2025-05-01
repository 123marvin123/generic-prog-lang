
from .object import _Object
from .exp import Exp

class PrimitiveVal(_Object):

    def __init__(self, value):
        super().__init__(value)
        
    @property
    def value(self):
        return self._native
        
    def reduce_value(self):
        return self
        
    def __str__(self):
        return f"{type(self).__name__}({self.value})"
        
    def __repr__(self):
        return self.__str__()


class _Number(PrimitiveVal):

    def __init__(self, value):
        if not isinstance(value, (int, float)):
            raise TypeError(f"Number erwartet int oder float, bekam {type(value)}")
        super().__init__(value)
    

def Number(*args, **kwargs):
    return Exp(_Number(*args, **kwargs))

class _Boolean(PrimitiveVal):

    def __init__(self, value):
        if not isinstance(value, bool):
            raise TypeError(f"Boolean erwartet bool, bekam {type(value)}")
        super().__init__(value)

def Boolean(*args, **kwargs):
    return Exp(_Boolean(*args, **kwargs))

class _String(PrimitiveVal):
    def __init__(self, value):
        if not isinstance(value, str):
            raise TypeError(f"String erwartet str, bekam {type(value)}")
        super().__init__(value)

def String(*args, **kwargs):
    return Exp(_String(*args, **kwargs))

class _Real(_Number):

    def __init__(self, value):
        super().__init__(float(value))

def Real(*args, **kwargs):
    return Exp(_Real(*args, **kwargs))