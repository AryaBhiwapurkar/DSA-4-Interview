"""
0068. Text Justification  |  Hard  |  Arrays & Hashing
Link: https://leetcode.com/problems/text-justification/

Problem: Greedily pack words into lines of exactly maxWidth chars and
         fully justify them (extra spaces go to the left gaps). The last
         line and single-word lines are left-justified, padded right.

Examples:
  ["This","is","an","example","of","text","justification."], 16
    -> ["This    is    an","example  of text","justification.  "]
  ["What","must","be","acknowledgment","shall","be"], 16
    -> ["What   must   be","acknowledgment  ","shall be        "]
  ["Science","is","what",...,"we","do"], 20
    -> ["Science  is  what we","understand      well","enough to explain to",
        "a  computer.  Art is","everything  else  we","do                  "]

Approaches:
  1. Greedy packing + space distribution  ⭐  O(N) time   <- go-to
"""


# ---------- Approach 1: Greedy Packing + Space Distribution ⭐ ----------
def full_justify(words: list[str], max_width: int) -> list[str]:
    res: list[str] = []
    i, n = 0, len(words)
    while i < n:
        j, letters = i, 0
        while j < n and letters + (j - i) + len(words[j]) <= max_width:  # (j - i) separating spaces
            letters += len(words[j])
            j += 1
        gaps = j - i - 1
        if j == n or gaps == 0:  # last line or single word: left-justify
            line = " ".join(words[i:j])
            res.append(line.ljust(max_width))
        else:
            base, extra = divmod(max_width - letters, gaps)
            parts: list[str] = []
            for g, w in enumerate(words[i : j - 1]):
                parts.append(w + " " * (base + (1 if g < extra else 0)))  # extras go left
            parts.append(words[j - 1])
            res.append("".join(parts))
        i = j
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        (["This", "is", "an", "example", "of", "text", "justification."], 16),
        (["What", "must", "be", "acknowledgment", "shall", "be"], 16),
        (
            ["Science", "is", "what", "we", "understand", "well", "enough", "to", "explain",
             "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do"],
            20,
        ),
    ]
    for words, w in tests:
        for line in full_justify(words, w):
            print(f'"{line}"')
        print("---")

"""
Syntax notes (Python):
- s.ljust(w) pads s with spaces on the right to width w.
- divmod(a, b) gives quotient and remainder together.
- " " * k builds k spaces (empty string for k = 0).
"""
