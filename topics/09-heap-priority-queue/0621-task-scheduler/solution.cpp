/*
 * 0621. Task Scheduler  |  Medium  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/task-scheduler/
 *
 * Problem: Unit-time tasks A-Z; equal tasks must be >= n units apart (idle
 *          allowed). Minimum total time.
 *
 * Examples:
 *   [A,A,A,B,B,B], n 2                  -> 8
 *   [A,C,A,B,D,B], n 1                  -> 6
 *   [A,A,A,B,B,B], n 3                  -> 10
 *   [A,A,A,A,A,A,B,C,D,E,F,G], n 2      -> 16
 *   [A,B,A], n 0                        -> 3
 *
 * Approaches:
 *   1. Max-heap + cooldown queue   O(T log 26) time, O(26) space
 *   2. Counting formula  ⭐         O(T) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Max-Heap + Cooldown Queue ----------
int leastIntervalHeap(const vector<char>& tasks, int n) {
    array<int, 26> cnt{};
    for (char t : tasks) cnt[t - 'A']++;
    priority_queue<int> pq;                // remaining counts of available tasks
    for (int c : cnt) if (c) pq.push(c);
    queue<pair<int, int>> cool;            // (remaining count, time it's ready again)
    int time = 0;
    while (!pq.empty() || !cool.empty()) {
        time++;
        if (!pq.empty()) {                 // run the most frequent available task
            int c = pq.top() - 1;
            pq.pop();
            if (c > 0) cool.push({c, time + n});
        }                                  // else: idle this unit
        if (!cool.empty() && cool.front().second == time) {
            pq.push(cool.front().first);
            cool.pop();
        }
    }
    return time;
}

// ---------- Approach 2: Counting Formula ⭐ ----------
int leastInterval(const vector<char>& tasks, int n) {
    array<int, 26> cnt{};
    for (char t : tasks) cnt[t - 'A']++;
    int maxc = *max_element(cnt.begin(), cnt.end());
    int tied = count(cnt.begin(), cnt.end(), maxc);   // tasks sharing the max count
    int frame = (maxc - 1) * (n + 1) + tied;
    return max((int)tasks.size(), frame);  // enough variety -> no idling at all
}

// ---------- Driver ----------
int main() {
    vector<pair<string, int>> tests = {
        {"AAABBB", 2}, {"ACABDB", 1}, {"AAABBB", 3}, {"AAAAAABCDEFG", 2}, {"ABA", 0}
    };
    for (auto& [s, n] : tests) {
        vector<char> tasks(s.begin(), s.end());
        cout << "heap   : " << leastIntervalHeap(tasks, n) << "\n";
        cout << "formula: " << leastInterval(tasks, n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - array<int, 26> cnt{} is a zeroed fixed array.
 * - count(b, e, x) counts occurrences of a value.
 * - Test tasks are written as strings and converted to vector<char>.
 */
