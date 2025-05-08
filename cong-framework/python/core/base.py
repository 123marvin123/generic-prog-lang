import traceback

class Undefined:
    def __init__(self, error_message="Expression not defined"):
        self._error_message = error_message
        stack = traceback.extract_stack()
        if len(stack) > 1:
            caller = stack[-2]
            self._filename = caller.filename
            self._lineno = caller.lineno
            self._funcname = caller.name
            self._location_info = f" (in {self._funcname} at {self._filename}:{self._lineno})"
        else:
            # Fallback, falls der Stack nicht wie erwartet aussieht
            self._location_info = " (location unknown)"

    def __str__(self):
        return f"Undefined: {self._error_message}{self._location_info}"
        
    def __repr__(self):
        return self.__str__()
        
    @property
    def error_message(self):
        return self._error_message
        
    @error_message.setter
    def error_message(self, message):
        self._error_message = message

class Base:

    def reduce_space(self):
        return Undefined("Operation space cost not defined")
        
    def reduce_time(self):
        return Undefined("Operation time cost not defined")
        
    def reduce_value(self):
        from .exp import Exp
        return Exp(self)
        
    # Apply-Eigenschaften
    def apply_space(self, *args):
        return Undefined("Operation space cost not defined")
        
    def apply_time(self, *args):
        return Undefined("Operation time cost not defined")
        
    def apply_value(self, *args):
        return Undefined("Implementation not present")