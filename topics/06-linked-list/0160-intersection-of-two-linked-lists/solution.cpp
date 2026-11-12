/*
 * 0160. Intersection of Two Linked Lists  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/intersection-of-two-linked-lists/
 *
 * Problem: Return the first node shared by two acyclic lists, or null.
 *          (skipA / skipB give where the shared tail starts; -1 = none.)
 *
 * Examples:
 *   A = [4,1,8,4,5],  B = [5,6,1,8,4,5], skipA 2, skipB 3   -> 8
 *   A = [1,9,1,2,4],  B = [3,2,4],       skipA 3, skipB 1   -> 2
 *   A = [2,6,4],      B = [1,5],         no intersection    -> null
 *   A = [1],          B = [1],           skipA 0, skipB 0   -> 1   (same head)
 *   A = [7],          B = [7],           no intersection    -> null (equal values only)
 *
 * Approaches:
 *   1. Hash set of A's nodes           O(m + n) time, O(m) space
 *   2. Length difference               O(m + n) time, O(1) space
 *   3. Head-switching two pointers ⭐  O(m + n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Hash Set of A's Nodes ----------
ListNode* getIntersectionNodeSet(ListNode* a, ListNode* b) {
    unordered_set<ListNode*> inA;
    for (; a; a = a->next) inA.insert(a);
    for (; b; b = b->next)
        if (inA.count(b)) return b;
    return nullptr;
}

// ---------- Approach 2: Length Difference ----------
int length(ListNode* p) {
    int n = 0;
    for (; p; p = p->next) n++;
    return n;
}

ListNode* getIntersectionNodeLength(ListNode* a, ListNode* b) {
    int la = length(a), lb = length(b);
    for (; la > lb; la--) a = a->next;        // align the longer list
    for (; lb > la; lb--) b = b->next;
    while (a != b) { a = a->next; b = b->next; }
    return a;                                  // shared node or nullptr
}

// ---------- Approach 3: Head-switching Two Pointers ⭐ ----------
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode *pa = headA, *pb = headB;
    while (pa != pb) {                         // both null together if no intersection
        pa = pa ? pa->next : headB;
        pb = pb ? pb->next : headA;
    }
    return pa;
}

// ---------- Driver ----------
pair<ListNode*, ListNode*> buildPair(const vector<int>& A, const vector<int>& B, int skipA, int skipB) {
    vector<ListNode*> na;
    for (int x : A) na.push_back(new ListNode(x));
    for (size_t i = 0; i + 1 < na.size(); i++) na[i]->next = na[i + 1];
    int ownB = skipA < 0 ? B.size() : skipB;  // B's private nodes
    ListNode dummy;
    ListNode* t = &dummy;
    for (int i = 0; i < ownB; i++) t = t->next = new ListNode(B[i]);
    if (skipA >= 0) t->next = na[skipA];       // join the shared tail
    return {na[0], dummy.next};
}

string show(ListNode* p) { return p ? to_string(p->val) : "null"; }

int main() {
    struct T { vector<int> A, B; int skipA, skipB; };
    vector<T> tests = {{{4, 1, 8, 4, 5}, {5, 6, 1, 8, 4, 5}, 2, 3}, {{1, 9, 1, 2, 4}, {3, 2, 4}, 3, 1},
                       {{2, 6, 4}, {1, 5}, -1, -1}, {{1}, {1}, 0, 0}, {{7}, {7}, -1, -1}};
    for (auto& t : tests) {
        auto [a, b] = buildPair(t.A, t.B, t.skipA, t.skipB);   // read-only: share the lists
        cout << "hashSet: " << show(getIntersectionNodeSet(a, b)) << "\n";
        cout << "length : " << show(getIntersectionNodeLength(a, b)) << "\n";
        cout << "switch : " << show(getIntersectionNode(a, b)) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - pa = pa ? pa->next : headB;  null counts as one step before switching.
 * - A local struct T groups each test's fields; aggregate-initialised with braces.
 * - for (; la > lb; la--) uses the for header with an empty init.
 */
