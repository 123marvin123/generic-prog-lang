
from core.bind import Bind
from core.exp import Exp, eval
from core.function import FunctionSpecification, FunctionFromSpec, GenericFunction, CostFun
from core.concept_sequence import SpecItemAt, SpecReplaceItemAt, ConceptObject
from core.base import Base
from core.primitive import Number
from core.proj import Proj

class MySequence(Base):

    def __init__(self, start, end=None):
        if end is None:
            self._items = list(start)
        else:
            self._items = [Number(i) for i in range(start.value, end.value)]

    @staticmethod
    def itemAt(seq, index):
        if index.value < 0 or index.value >= len(seq._items):
            raise IndexError("Index out of range")
        return seq._items[index.value]

    @staticmethod
    def replaceItemAt(seq, index, newItem):
        if index.value < 0 or index.value >= len(seq._items):
            raise IndexError("Index out of range")
        oldItem = seq._items[index.value]
        seq._items[index.value] = newItem
        return oldItem

    def length(self):
        return Number(len(self._items))

    def __str__(self):
        return f"MySequence({self._items})"

def replaceItemAt(*args):
    return Bind(FunctionFromSpec(SpecReplaceItemAt()), *args)

def itemAt(*args):
    return Bind(FunctionFromSpec(SpecItemAt()), *args)

class SpecId(FunctionSpecification):
    def __init__(self):
        super().__init__(
            "id",
            "Returns itself",
            [ConceptObject.instance()],
            ConceptObject.instance(),
            [
                GenericFunction(
                    lambda x: x,
                    CostFun(lambda x: Number(1)),
                    CostFun(lambda x: Number(0))
                )
            ]
        )

def id(*args):
    return Bind(FunctionFromSpec(SpecId()), *args)

if __name__ == "__main__":
    seq = Exp(MySequence(Number(0), Number(10)))
    a = id(replaceItemAt(seq, Number(0), Number(5)))
    result = eval(a)
    print(f"Ergebnis: {result}, Sequenz nach Ersetzung: {seq}")

    replaceFirstItem = replaceItemAt(Proj(1), Number(0), Number(5))

    seq = Exp(MySequence(Number(0), Number(10)))
    result = eval(replaceFirstItem(seq))
    print(f"2 -- Ergebnis: {result}, Sequenz nach Ersetzung: {seq}")
