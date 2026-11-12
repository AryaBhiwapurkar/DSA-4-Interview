/*
 * 0234. Palindrome Linked List  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/palindrome-linked-list/
 *
 * Problem: Return whether a singly linked list's values form a palindrome.
 *
 * Examples:
 *   [1,2,2,1]     -> true
 *   [1,2]         -> false
 *   [1]           -> true
 *   [1,2,3,2,1]   -> true
 *   [1,2,3,1]     -> false
 *   [1,1,2,1]     -> false
 *
 * Approaches:
 *   1. Copy to an array                 O(n) time, O(n) space
 *   2. Recursion with a front pointer   O(n) time, O(n) stack
 *   3. Reverse the second half  ⭐      O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// ---------- Approach 1: Copy to an Array ----------
bool isPalindromeArray(ListNode* head) {
    vector<int> v;
    for (ListNode* p = head; p; p = p->next) v.push_back(p->val);
    for (int i = 0, j = (int)v.size() - 1; i < j; i++, j--)
        if (v[i] != v[j]) return false;
    return true;
}

// ---------- Approach 2: Recursion with a Front Pointer ----------
bool checkFromBack(ListNode* node, ListNode*& front) {
    if (!node) return true;
    if (!checkFromBack(node->next, front)) return false;   // compare deepest first
    bool ok = node->val == front->val;
    front = front->next;
    return ok;
}

bool isPalindromeRecursive(ListNode* head) {
    ListNode* front = head;
    return checkFromBack(head, front);
}

// ---------- Approach 3: Reverse the Second Half ⭐ ----------
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* nxt = head->next;
        head->next = prev;
        prev = head;
        head = nxt;
    }
    return prev;
}

bool isPalindrome(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {   // slow stops at the end of the first half
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* second = reverseList(slow->next);
    bool ok = true;
    for (ListNode *p = head, *q = second; q; p = p->next, q = q->next)
        if (p->val != q->val) { ok = false; break; }
    slow->next = reverseList(second);          // restore the input
    return ok;
}

// ---------- Driver ----------
ListNode* build(const vector<int>& v) {
    ListNode dummy;
    ListNode* t = &dummy;
    for (int x : v) t = t->next = new ListNode(x);
    return dummy.next;
}

string str(ListNode* p) {
    string s = "[";
    for (; p; p = p->next) s += to_string(p->val) + (p->next ? "," : "");
    return s + "]";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 2, 1}, {1, 2}, {1}, {1, 2, 3, 2, 1}, {1, 2, 3, 1}, {1, 1, 2, 1}};
    cout << boolalpha;
    for (auto& t : tests) {
        ListNode* head = build(t);
        cout << "array    : " << isPalindromeArray(head) << "\n";
        cout << "recursive: " << isPalindromeRecursive(head) << "\n";
        cout << "reverse  : " << isPalindrome(head) << "  list after: " << str(head) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - ListNode*& front passes the pointer by reference so recursion can advance it.
 * - for (ListNode *p = head, *q = second; q; p = p->next, q = q->next) walks two lists.
 * - t = t->next = new ListNode(x) appends and advances the tail in one line.
 */
