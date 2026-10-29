"""
0013. Roman to Integer  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/roman-to-integer/

Problem: Convert a valid Roman numeral (1..3999) to an integer.
         IV, IX, XL, XC, CD, CM are subtractive pairs.

Examples:
  "III"       -> 3
  "LVIII"     -> 58
  "MCMXCIV"   -> 1994
  "MMMCMXCIX" -> 3999

Approaches:
  1. Match two-char pairs first   O(n) time, O(1) space
  2. Compare with next  ⭐         O(n) time, O(1) space   <- go-to
"""

VAL = {"I": 1, "V": 5, "X": 10, "L": 50, "C": 100, "D": 500, "M": 1000}
PAIRS = {"IV": 4, "IX": 9, "XL": 40, "XC": 90, "CD": 400, "CM": 900}


# ---------- Approach 1: Match Two-Char Pairs First ----------
def roman_to_int_pairs(s: str) -> int:
    total, i = 0, 0
    while i < len(s):
        if s[i : i + 2] in PAIRS:  # slicing past the end is safe in Python
            total += PAIRS[s[i : i + 2]]
            i += 2
        else:
            total += VAL[s[i]]
            i += 1
    return total


# ---------- Approach 2: Compare With Next ⭐ ----------
def roman_to_int(s: str) -> int:
    total = 0
    for i, c in enumerate(s):
        v = VAL[c]
        if i + 1 < len(s) and v < VAL[s[i + 1]]:  # smaller before larger: subtract
            total -= v
        else:
            total += v
    return total


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["III", "LVIII", "MCMXCIV", "MMMCMXCIX"]:
        print("pairs  :", roman_to_int_pairs(s))
        print("compare:", roman_to_int(s))
        print("---")

"""
Syntax notes (Python):
- Slicing past the end (s[i:i+2] at the last index) returns a shorter string, no error.
- Module-level dict constants are built once.
- enumerate gives (index, char) pairs.
"""
