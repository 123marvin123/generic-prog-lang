
from core.bind import Bind
from core.exp import Exp, eval
from core.function import FunctionSpecification, Function
from core.concept_sequence import SpecItemAt, SpecReplaceItemAt, ConceptObject
from core.base import Base
from core.primitive import Number, String

class MySequence(Base):

    def __init__(self, start, end=None):
        if end is None:
            self._items = list(start)
        else:
            self._items = [Number(i) for i in range(start.value, end.value)]

    def itemAt(self, index):
        if index.value < 0 or index.value >= len(self._items):
            raise IndexError("Index out of range")
        return self._items[index.value]

    def replaceItemAt(self, index, newItem):
        if index.value < 0 or index.value >= len(self._items):
            raise IndexError("Index out of range")
        oldItem = self._items[index.value]
        self._items[index.value] = newItem
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
        super().__init__("id", "Returns itself", [ConceptObject.instance()], ConceptObject.instance(), [])

def id(*args):
    return Bind(Function(SpecId()), *args)

def run_tests():
    print("=== Cong-Framework Sequence-Tests ===")

    print("\nTest 1: Einfache Sequenz erstellen und Element abrufen")
    seq = Exp(MySequence(Number(0), Number(10)))
    print(f"Sequenz erstellt: {seq}")

    print(f"Element an Position 5: {eval(itemAt(seq, Number(5)))}")

    index_exp = itemAt(seq, Number(5))
    result = eval(index_exp)
    print(f"Element an Position 5 (über Framework): {result}")

    print("\nTest 2: Element ersetzen")
    old_value = replaceItemAt(seq, Number(0), Number(100))
    print(f"Altes Element an Position 0: {old_value}")
    print(f"Sequenz nach Ersetzung: {seq}")

    replace_exp = replaceItemAt(seq, Number(3), Number(300))
    old_value_framework = eval(replace_exp)
    print(f"Altes Element an Position 3 (über Framework): {old_value_framework}")
    print(f"Sequenz nach zweiter Ersetzung: {seq}")

    try:
        eval(itemAt(seq, Number(20)))
    except IndexError as e:
        print(f"Erwarteter Fehler im Framework aufgetreten: {e}")

    print("\nTest 4: Mit anderen Datentypen")
    string_seq = Exp(MySequence(["a", "b", "c", "d"]))
    print(f"String-Sequenz: {string_seq}")

    replace_str_exp = replaceItemAt(string_seq, Number(2), String("CHANGED"))
    old_str = eval(replace_str_exp)
    print(f"Altes String-Element: {old_str}")
    print(f"String-Sequenz nach Ersetzung: {string_seq}")

    print("\nTest 5: Verkettung von Operationen")
    mixed_seq = Exp(MySequence([10, "text", 3.14, True, None]))
    print(f"Gemischte Sequenz: {mixed_seq}")

    item = eval(itemAt(mixed_seq, Number(1)))
    print(f"Element an Position 1: {item}")
    replace_exp = replaceItemAt(mixed_seq, Number(1), String(f"{item}-modifiziert"))
    eval(replace_exp)
    print(f"Gemischte Sequenz nach Ersetzung: {mixed_seq}")

if __name__ == "__main__":
    seq = Exp(MySequence(Number(0), Number(10)))
    a = id(replaceItemAt(seq, Number(0), Number(5)))
    result = eval(a)
    print(f"Ergebnis: {result}, Sequenz nach Ersetzung: {seq}")

    run_tests()
