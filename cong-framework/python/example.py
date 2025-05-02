
from core.bind import Bind
from core.exp import Exp, eval
from core.function import FunctionSpecification, Function
from core.concept_sequence import SpecItemAt, SpecReplaceItemAt, ConceptObject
from core.base import Base
from core.primitive import Number, String
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
    return Bind(Function(SpecReplaceItemAt()), *args)

def itemAt(*args):
    return Bind(Function(SpecItemAt()), *args)

class SpecId(FunctionSpecification):
    def __init__(self):
        super().__init__(
            "id",
            "Returns itself",
            [ConceptObject.instance()],
            ConceptObject.instance(),
            [lambda x: x])

def id(*args):
    return Bind(Function(SpecId()), *args)

if __name__ == "__main__":
    seq = Exp(MySequence(Number(0), Number(10)))
    a = id(replaceItemAt(seq, Number(0), Number(5)))
    result = eval(a)
    print(f"Ergebnis: {result}, Sequenz nach Ersetzung: {seq}")

    replaceFirstItem = replaceItemAt(Proj(Number(1)), Number(0), Number(5))

    seq = Exp(MySequence(Number(0), Number(10)))
    result = eval(replaceFirstItem(seq))
    print(f"2 -- Ergebnis: {result}, Sequenz nach Ersetzung: {seq}")
