
from .val import Val
from .exp import Exp

class _Object(Val):
    def __init__(self, native_value):
        self._native = native_value
        
    @property
    def native(self):
        return self._native

    def reduce_value(self):
        return self
    
    def apply_value(self, *args):
        return self

    def id(self):
        return self

    def __str__(self):
        return f"ObjectDynamic({self._native})"
        
    def __repr__(self):
        return self.__str__()

def Object(*args, **kwargs):
    return Exp(_Object(*args, **kwargs))