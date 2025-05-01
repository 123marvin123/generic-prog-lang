
from .base import Base, Undefined
from .exp import Exp, is_exp
from .primitive import Number

class FunctionSpecification:
    def __init__(self, name, description, concept_args, concept_result, generic_impls=None):
        if generic_impls is None:
            generic_impls = []
        self.name = name
        self.description = description
        self.concept_args = concept_args
        self.concept_result = concept_result
        self.generic_impls = generic_impls
        
    def __str__(self):
        return f"FunctionSpecification({self.name}, description={self.description}, concept_args={self.concept_args}, concept_result={self.concept_result}, generic_impls={len(self.generic_impls)})"
        
    def __repr__(self):
        return self.__str__()

class _Function(Base):

    def __init__(self, specification):
        self.specification = specification

    def reduce_space(self):
        return Number(0)
        
    def reduce_time(self):
        return Number(1)

    def apply_value(self, *args):
        for i, arg in enumerate(args):
            if not is_exp(arg):
                raise TypeError(f"Argument {i} must be an expression, got {type(arg).__name__}")

        exp = args[0].reduce_value()
        argument_list = args[1:] if len(args) > 1 else []

        # Evaluate the argument_list to a new list evaluated_args by calling reduce_value on each of them
        evaluated_args = [arg.reduce_value() for arg in argument_list]

        # TODO check if arguments satisfy the needed concepts for this fun 

        method = getattr(exp, self.specification.name, None)
        if method is not None:
            return method(*evaluated_args)

        generic_impls = getattr(self.specification, "GENERIC_IMPLS", [])
        for generic_impl in generic_impls:
            result = generic_impl(exp, *evaluated_args)
            if not isinstance(result, Undefined):
                return result
        
        # If we get here, neither specific nor generic implementations worked
        return Undefined(f"Neither specific implementation of {self.specification.name} nor any generic implementations are defined for this operation")

def Function(*args, **kwargs):
    return Exp(_Function(*args, **kwargs))