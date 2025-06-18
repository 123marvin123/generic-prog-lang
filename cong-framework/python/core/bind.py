from .exp import Exp, is_exp
from .base import Base, Undefined
from .proj import _Proj

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
        return self.apply_value(*args)

    def reduce_value(self):
        return self._impl.apply_value(*self._args)
    
    def apply_value(self, *args):
        resolved_args = []
        for existing_arg in self._args:
            if is_exp(existing_arg) and isinstance(existing_arg.impl, _Proj):
                try:
                    resolved_value = existing_arg.apply_value(*args)
                    resolved_args.append(resolved_value)
                except Exception as e:
                    return Undefined(f"Unerwarteter Fehler beim Auflösen von {existing_arg}: {e}")
            else:
                resolved_args.append(existing_arg)
        return Bind(self._impl, *resolved_args)

def Bind(*args, **kwargs):
    return Exp(_Bind(*args, **kwargs))