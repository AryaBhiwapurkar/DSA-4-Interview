"""
0187. Repeated DNA Sequences  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/repeated-dna-sequences/

Problem: Return every 10-letter substring of a DNA string (ACGT) that occurs more than once.

Examples:
  "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"  -> ["AAAAACCCCC","CCCCCAAAAA"]
  "AAAAAAAAAAAAA"                     -> ["AAAAAAAAAA"]
  "ACGT"                              -> []    (shorter than 10)
  "ACGTACGTACGTACGT"                  -> ["ACGTACGTAC","CGTACGTACG","GTACGTACGT"]

Approaches:
  1. Substring hash set  ⭐     O(n*L) time, O(n*L) space   <- go-to (L = 10)
  2. 2-bit rolling encoding     O(n) time, O(n) space
  (Output is printed sorted so both approaches compare equal.)
"""


# ---------- Approach 1: Substring Set ⭐ ----------
def find_repeated_dna_sequences(s: str) -> list[str]:
    seen: set[str] = set()
    repeated: set[str] = set()
    for i in range(len(s) - 9):  # empty range when len(s) < 10
        w = s[i:i + 10]
        if w in seen:
            repeated.add(w)
        else:
            seen.add(w)
    return list(repeated)


# ---------- Approach 2: 2-bit Rolling Encoding ----------
def find_repeated_dna_sequences_bits(s: str) -> list[str]:
    val = {"A": 0, "C": 1, "G": 2, "T": 3}
    mask = (1 << 20) - 1  # 10 letters x 2 bits
    seen: set[int] = set()
    added: set[int] = set()
    out: list[str] = []
    code = 0
    for i, c in enumerate(s):
        code = ((code << 2) | val[c]) & mask  # shift in the new letter, drop the oldest
        if i < 9:
            continue  # window not full yet
        if code in seen and code not in added:
            added.add(code)
            out.append(s[i - 9:i + 1])
        seen.add(code)
    return out


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT", "AAAAAAAAAAAAA", "ACGT", "ACGTACGTACGTACGT"]:
        print("set :", sorted(find_repeated_dna_sequences(s)))
        print("bits:", sorted(find_repeated_dna_sequences_bits(s)))
        print("---")

"""
Syntax notes (Python):
- range(len(s) - 9) is empty for short strings (negative stop), so no special case is needed.
- s[i:i + 10] slices a fixed-length window.
- & mask keeps only the low 20 bits, since Python ints otherwise grow without bound.
"""
