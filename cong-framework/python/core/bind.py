from .exp import Exp, eval, is_exp
from .base import Base

class _Bind:

    def __init__(self, implementation, *args):
        self._impl = implementation
        if not isinstance(self._impl, Base):
            raise TypeError(f"Die Implementierung muss eine Instanz von Base sein, nicht {type(self._impl).__name__}")
        
        self._args = args
    
    @property
    def impl(self):
        return self._impl

    def __getattr__(self, name):
        return getattr(self._impl, name)
    
    def __call__(self, *args, **kwargs):
        if callable(self._impl):
            return self._impl(*args, **kwargs)
        raise TypeError(f"'{type(self._impl).__name__}' Objekt ist nicht aufrufbar")
        
    def reduce_value(self):
        return self._impl.apply_value(*self._args)
    
    def apply_value(self, *args):
        self._args += args
        return self._impl.apply_value(*self._args)

def Bind(*args, **kwargs):
    return Exp(_Bind(*args, **kwargs))