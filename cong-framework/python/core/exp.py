from .base import Base, Undefined

class Exp(Base):
    def __init__(self, impl):
        self._impl = impl

    def __getattr__(self, name):
        return getattr(self._impl, name)

    def __call__(self, *args):
        from .bind import Bind
        return Exp(Bind(self, args))
    
    def reduce_space(self):
        return self._impl.reduce_space()
        
    def reduce_time(self):
        return self._impl.reduce_time()
    
    def reduce_value(self):
        return self._impl.reduce_value()
    
    def apply_space(self):
        return self._impl.apply_space()
        
    def apply_time(self):
        return self._impl.apply_time()
    
    def apply_value(self, *args):
        return self._impl.apply_value(*args)
    
    @property
    def impl(self):
        return self._impl
        
    def __str__(self):
        if hasattr(self._impl, '__str__'):
            return f"Exp({self._impl})"
        else:
            return f"Exp(type={type(self._impl).__name__})"
            
    def __repr__(self):
        return self.__str__()


def is_exp(obj):
    return isinstance(obj, Exp)


def is_defined(obj):
    return not isinstance(obj, Undefined)


def eval(exp):
    if not is_exp(exp):
        return exp
        
    try:
        return exp.reduce_value()
    except Exception as e:
        return Undefined(str(e)) #todo: add full stack trace