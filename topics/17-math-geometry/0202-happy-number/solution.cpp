/*
 * 0202. Happy Number  |  Easy  |  Math & Geometry
 * Link: https://leetcode.com/problems/happy-number/
 *
 * Problem: Repeatedly replace n by the sum of the squares of its digits.
 *          Happy if this reaches 1; otherwise it cycles forever.
 *
 * Examples:
 *   19          -> true   (19 -> 82 -> 68 -> 100 -> 1)
 *   2           -> false  (falls into the 4 -> 16 -> ... -> 4 cycle)
 *   1           -> true
 *   7           -> true
 *   2147483647  -> false
 *
 * Approaches:
 *   1. Hash set of seen values  ⭐  O(log n) per step, O(k) space   <- go-to
 *   2. Floyd slow/fast pointers      O(log n) per step, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

int nextNum(int n) {
    int s = 0;
    for (; n; n /= 10) s += (n % 10) * (n % 10);
    return s;
}

// ---------- Approach 1: Hash Set ⭐ ----------
bool isHappy(int n) {
    unordered_set<int> seen;
    while (n != 1 && !seen.count(n)) {             // stop at 1 or a repeat
        seen.insert(n);
        n = nextNum(n);
    }
    return n == 1;
}

// ---------- Approach 2: Floyd ----------
bool isHappyFloyd(int n) {
    int slow = n, fast = nextNum(n);
    while (fast != 1 && slow != fast) {            // 1 is a fixed point, so fast stays there
        slow = nextNum(slow);
        fast = nextNum(nextNum(fast));
    }
    return fast == 1;
}

// ---------- Driver ----------
int main() {
    cout << boolalpha;
    for (int n : {19, 2, 1, 7, 2147483647}) {
        cout << "set  : " << isHappy(n) << "\n";
        cout << "floyd: " << isHappyFloyd(n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - for (; n; n /= 10) peels decimal digits with n % 10.
 * - unordered_set::count(x) returns 0 or 1: a cheap membership test.
 * - Starting fast one step ahead avoids the slow == fast exit before the first move.
 */
