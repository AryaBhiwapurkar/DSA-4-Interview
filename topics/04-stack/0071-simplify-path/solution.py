"""
0071. Simplify Path  |  Medium  |  Stack
Link: https://leetcode.com/problems/simplify-path/

Problem: Turn an absolute Unix path into canonical form: single slashes,
         no trailing slash, "." and ".." resolved ("..." is a name).

Examples:
  "/home/"                             -> "/home"
  "/home//foo/"                        -> "/home/foo"
  "/home/user/Documents/../Pictures"   -> "/home/user/Pictures"
  "/../"                               -> "/"
  "/.../a/../b/c/../d/./"              -> "/.../b/d"
  "/a/./b/../../c/"                    -> "/c"
  "/"                                  -> "/"

Approaches:
  1. Split + stack  ⭐   O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Split + Stack ⭐ ----------
def simplify_path(path: str) -> str:
    st: list[str] = []
    for part in path.split("/"):  # "" between repeated slashes
        if part in ("", "."):
            continue
        if part == "..":
            if st:  # ".." at root is a no-op
                st.pop()
        else:
            st.append(part)
    return "/" + "/".join(st)  # empty stack gives "/"


# ---------- Driver ----------
if __name__ == "__main__":
    tests = ["/home/", "/home//foo/", "/home/user/Documents/../Pictures", "/../",
             "/.../a/../b/c/../d/./", "/a/./b/../../c/", "/"]
    for p in tests:
        print(f'stack: "{simplify_path(p)}"')
        print("---")

"""
Syntax notes (Python):
- s.split("/") keeps empty strings between consecutive separators
  (unlike s.split() with no argument, which drops them).
- `part in ("", ".")` is a compact multi-value equality check.
- "/" + "/".join([]) is "/", so the root case needs no special branch.
"""
