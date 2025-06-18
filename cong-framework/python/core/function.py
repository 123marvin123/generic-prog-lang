
from .base import Base, Undefined
from .exp import Exp, is_exp
from .primitive import Number

class FunctionSpecification:
    def __init__(self, name, description, concept_args, concept_result, generic_impls=None):
        if generic_impls is None:
            generic_impls = []

        for impl in generic_impls:
            if not isinstance(impl, _GenericFunction):
                raise TypeError(
                    f"Alle Elemente in generic_impls müssen Instanzen von _GenericFunction sein, aber {type(impl).__name__} gefunden.")

        self.name = name
        self.description = description
        self.concept_args = concept_args
        self.concept_result = concept_result
        self.generic_impls = generic_impls
        
    def __str__(self):
        return f"FunctionSpecification({self.name}, description={self.description}, concept_args={self.concept_args}, concept_result={self.concept_result}, generic_impls={len(self.generic_impls)})"
        
    def __repr__(self):
        return self.__str__()

class _FunctionFromSpec(Base):

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

        # Evaluate the argument_list to a new list evaluated_args by calling reduce_value on each of them
        # TODO: only evaluate args if we are sure that there is a specific / generic impl we can use
        evaluated_args = [arg.reduce_value() for arg in args]

        # TODO check if arguments satisfy the needed concepts for this fun

        # We iterate through all our arguments to see if any of the arguments implement our target function
        # We always prioritize specific impls, e.g. we assume that they are optimized
        # TODO: if we have multiple impls (e.g. because more than 1 argument implements the function), we should pick the best (by cost)
        for exp in evaluated_args:
            method = getattr(exp, self.specification.name, None)
            if method is not None:
                return method(*evaluated_args)

        generic_impls_from_spec = getattr(self.specification, "generic_impls", [])

        best_generic_impl = None
        lowest_cost_value = float('inf')

        if not generic_impls_from_spec:
            return Undefined(f"Neither specific implementation of {self.specification.name} nor any generic implementations are defined.")

        for gen_impl_wrapper in generic_impls_from_spec:
            cost_obj = gen_impl_wrapper.apply_space(*evaluated_args)
            if not isinstance(cost_obj, Undefined) and hasattr(cost_obj, 'value'):
                actual_cost = cost_obj.value
                if not isinstance(actual_cost, Undefined) and isinstance(actual_cost, (int, float)):
                    if actual_cost < lowest_cost_value:
                        lowest_cost_value = actual_cost
                        best_generic_impl = gen_impl_wrapper

        if best_generic_impl is not None:
            return best_generic_impl.apply_value(*evaluated_args)

        # If we get here, neither specific nor generic implementations worked
        return Undefined(f"No applicable generic implementation with defined and valid costs found for {self.specification.name}.")

def FunctionFromSpec(*args, **kwargs):
    return Exp(_FunctionFromSpec(*args, **kwargs))

class _GenericFunction(Base):

    def __init__(self, impl, time_complexity=Undefined("Operation time cost not defined"), space_complexity=Undefined("Operation space cost not defined")):
        if not isinstance(time_complexity, _CostFun):
            raise TypeError("time_complexity must be a CostFun")
        if not isinstance(space_complexity, _CostFun):
            raise TypeError("space_complexity must be a CostFun")

        self.impl = impl
        self.time_complexity = time_complexity
        self.space_complexity = space_complexity

    def reduce_space(self):
        return Number(0)

    def reduce_time(self):
        return Number(1)

    def apply_space(self, *args):
        if self.space_complexity is not None and not isinstance(self.space_complexity, Undefined):
            res = self.space_complexity.apply_value(*args)
            if not isinstance(res, Undefined):
                return res
        return Undefined("Operation space cost not defined")

    def apply_time(self, *args):
        if self.time_complexity is not None and not isinstance(self.time_complexity, Undefined):
            res = self.time_complexity.apply_value(*args)
            if not isinstance(res, Undefined):
                return res
        return Undefined("Operation time cost not defined")

    def apply_value(self, *args):
        return self.impl(*args)

def GenericFunction(*args):
    return _GenericFunction(*args)

class _CostFun(Base):
    def __init__(self, fn):
        if fn is None:
            raise TypeError("Function cannot be none")

        self.fn = fn

    def reduce_space(self):
        return Number(0)

    def reduce_time(self):
        return Number(0)

    def reduce_value(self):
        return super().reduce_value()

    # TODO: how to declare cost of evaluating cost func?
    def apply_space(self, *args):
        return super().apply_space(*args)

    # TODO: how to declare cost of evaluating cost func?
    def apply_time(self, *args):
        return super().apply_time(*args)

    def apply_value(self, *args):
        return self.fn(*args)

def CostFun(*args):
    return _CostFun(*args)