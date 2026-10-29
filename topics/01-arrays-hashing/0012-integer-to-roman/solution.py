"""
0012. Integer to Roman  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/integer-to-roman/

Problem: Convert an integer in [1, 3999] to a Roman numeral using the
         standard subtractive forms (IV, IX, XL, XC, CD, CM).

Examples:
  3749  -> "MMMDCCXLIX"
  58    -> "LVIII"
  1994  -> "MCMXCIV"
  3999  -> "MMMCMXCIX"

Approaches:
  1. Digit lookup tables          O(1) time, O(1) space
  2. Greedy over value table  ⭐   O(1) time, O(1) space   <- go-to
"""

TH = ["", "M", "MM", "MMM"]
HU = ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"]
TE = ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"]
ON = ["", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"]

# descending; includes subtractive pairs
TABLE = [
    (1000, "M"), (900, "CM"), (500, "D"), (400, "CD"), (100, "C"), (90, "XC"),
    (50, "L"), (40, "XL"), (10, "X"), (9, "IX"), (5, "V"), (4, "IV"), (1, "I"),
]


# ---------- Approach 1: Digit Lookup Tables ----------
def int_to_roman_tables(num: int) -> str:
    return TH[num // 1000] + HU[num % 1000 // 100] + TE[num % 100 // 10] + ON[num % 10]


# ---------- Approach 2: Greedy Over Value Table ⭐ ----------
def int_to_roman(num: int) -> str:
    out: list[str] = []
    for value, sym in TABLE:
        count, num = divmod(num, value)  # how many times this symbol fits
        out.append(sym * count)
    return "".join(out)


# ---------- Driver ----------
if __name__ == "__main__":
    for num in [3749, 58, 1994, 3999]:
        print("tables:", int_to_roman_tables(num))
        print("greedy:", int_to_roman(num))
        print("---")

"""
Syntax notes (Python):
- divmod(a, b) returns (a // b, a % b) in one call.
- "X" * 3 == "XXX"; "X" * 0 == "".
- Build with a list and "".join once instead of repeated +=.
"""
