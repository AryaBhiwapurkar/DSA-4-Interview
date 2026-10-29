"""
0271. Encode and Decode Strings  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/encode-and-decode-strings/

Problem: Design encode(list[str]) -> str and decode(str) -> list[str]
         with decode(encode(x)) == x. Strings can hold any ASCII character.

Examples:
  ["Hello","World"]  -> encoded "5#Hello5#World"  -> ["Hello","World"]
  [""]               -> encoded "0#"              -> [""]
  ["1#2","#","//;"]  -> round-trips unchanged
  []                 -> encoded ""                -> []

Approaches:
  1. Escaped delimiter     O(N) time, O(N) space
  2. Length prefix  ⭐      O(N) time, O(N) space   <- go-to
"""


# ---------- Approach 1: Escaped Delimiter ----------
# '/' is written as "//", and every string ends with "/;".
def encode_escaped(strs: list[str]) -> str:
    return "".join(s.replace("/", "//") + "/;" for s in strs)


def decode_escaped(s: str) -> list[str]:
    res: list[str] = []
    cur: list[str] = []
    i = 0
    while i < len(s):
        if s[i] == "/":
            if s[i + 1] == ";":  # terminator
                res.append("".join(cur))
                cur = []
            else:
                cur.append("/")  # "//" -> literal '/'
            i += 2
        else:
            cur.append(s[i])
            i += 1
    return res


# ---------- Approach 2: Length Prefix ⭐ ----------
def encode(strs: list[str]) -> str:
    return "".join(f"{len(s)}#{s}" for s in strs)


def decode(s: str) -> list[str]:
    res: list[str] = []
    i = 0
    while i < len(s):
        j = s.index("#", i)  # search from i: earlier content may contain '#'
        length = int(s[i:j])
        res.append(s[j + 1 : j + 1 + length])
        i = j + 1 + length
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for strs in [["Hello", "World"], [""], ["1#2", "#", "//;"], []]:
        print(f'encoded: "{encode(strs)}"')
        print("escaped:", decode_escaped(encode_escaped(strs)))
        print("length :", decode(encode(strs)))
        print("---")

"""
Syntax notes (Python):
- s.index(sub, start) searches from start (raises if absent; .find returns -1).
- "".join(generator) builds a string without repeated concatenation.
- Collect chars in a list and join once: += on str in a loop can be O(n^2).
"""
