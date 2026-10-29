/*
 * 0380. Insert Delete GetRandom O(1)  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/insert-delete-getrandom-o1/
 *
 * Problem: Design a set with insert, remove (both return whether they
 *          changed the set) and getRandom (uniform), all O(1) average.
 *
 * Examples:
 *   insert 1, remove 2, insert 2, getRandom, remove 1, insert 2, getRandom
 *   -> true, false, true, (1 or 2), true, false, 2
 *
 * Approaches:
 *   1. Hash set only               insert/remove O(1), getRandom O(n)
 *   2. Map + array, swap-delete  ⭐  all O(1) average, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Hash Set Only ----------
class RandomizedSetNaive {
    unordered_set<int> s;
public:
    bool insert(int val) { return s.insert(val).second; }
    bool remove(int val) { return s.erase(val) > 0; }
    int getRandom() {
        auto it = s.begin();
        advance(it, rand() % s.size());               // O(n) walk: no random access
        return *it;
    }
};

// ---------- Approach 2: Map + Array, Swap-Delete ⭐ ----------
class RandomizedSet {
    vector<int> arr;
    unordered_map<int, int> pos;                      // value -> index in arr
public:
    bool insert(int val) {
        if (pos.count(val)) return false;
        pos[val] = arr.size();
        arr.push_back(val);
        return true;
    }
    bool remove(int val) {
        auto it = pos.find(val);
        if (it == pos.end()) return false;
        int idx = it->second, last = arr.back();
        arr[idx] = last;                              // fill the hole with the last element
        pos[last] = idx;                              // update BEFORE erasing (val may equal last)
        arr.pop_back();
        pos.erase(val);
        return true;
    }
    int getRandom() { return arr[rand() % arr.size()]; }
};

// ---------- Driver ----------
template <typename Set>
void run(const string& label) {
    Set rs;
    cout << boolalpha << label << ": ";
    cout << rs.insert(1) << " " << rs.remove(2) << " " << rs.insert(2) << " ";
    int r = rs.getRandom();
    cout << "(rand in {1,2}: " << (r == 1 || r == 2) << ") ";
    cout << rs.remove(1) << " " << rs.insert(2) << " " << rs.getRandom() << "\n";
}

int main() {
    srand(42);
    run<RandomizedSetNaive>("naive");
    run<RandomizedSet>("map+array");
}

/*
 * Syntax notes (C++):
 * - unordered_set::erase(key) returns the number of elements removed (0 or 1).
 * - advance(it, k) moves a forward iterator k steps (O(k) for hash containers).
 * - rand() % n is fine for interviews; <random>'s mt19937 + uniform_int_distribution is unbiased.
 * - A function template lets one driver exercise both classes.
 */
