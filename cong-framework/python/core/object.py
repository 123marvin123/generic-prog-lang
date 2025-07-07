
from .val import Val
from .exp import Exp

class _Object(Val):
    def __init__(self, native_value):
        self._native = native_value
        
    @property
    def native(self):
        return self._native

    def __str__(self):
        return f"Object({self._native})"
        
    def __repr__(self):
        return self.__str__()

def Object(*args, **kwargs):
    return Exp(_Object(*args, **kwargs))