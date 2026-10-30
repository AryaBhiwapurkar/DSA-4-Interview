/*
 * 0146. LRU Cache  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/lru-cache/
 *
 * Problem: Fixed-capacity cache; get(key) -> value or -1; put(key, value)
 *          inserts/updates and evicts the least recently used key. O(1).
 *
 * Examples:
 *   cap 2: put 1 1, put 2 2, get 1, put 3 3, get 2, put 4 4, get 1, get 3, get 4
 *     -> [null,null,null,1,null,-1,null,-1,3,4]
 *   cap 1: put 2 1, get 2, put 3 2, get 2, get 3
 *     -> [null,null,1,null,-1,2]
 *   cap 2: put 1 1, put 2 2, put 1 10, put 3 3, get 1, get 2, get 3   (update = use)
 *     -> [null,null,null,null,null,10,-1,3]
 *
 * Approaches:
 *   1. Ordered list, linear search    O(cap) per op, O(cap) space
 *   2. Hashmap + DLL  ⭐               O(1) per op, O(cap) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Ordered List, Linear Search ----------
class LRUCacheBrute {
    int cap;
    vector<pair<int, int>> items;          // back = most recent
public:
    LRUCacheBrute(int capacity) : cap(capacity) {}
    int get(int key) {
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i].first != key) continue;
            auto kv = items[i];
            items.erase(items.begin() + i);
            items.push_back(kv);           // mark as most recent
            return kv.second;
        }
        return -1;
    }
    void put(int key, int value) {
        for (size_t i = 0; i < items.size(); i++)
            if (items[i].first == key) { items.erase(items.begin() + i); break; }
        if ((int)items.size() == cap) items.erase(items.begin());   // evict least recent
        items.push_back({key, value});
    }
};

// ---------- Approach 2: Hashmap + Doubly Linked List ⭐ ----------
class LRUCache {
    struct Node {
        int key = 0, val = 0;              // key stored so eviction can erase it from the map
        Node *prev = nullptr, *next = nullptr;
    };
    int cap;
    unordered_map<int, Node*> m;
    Node head, tail;                       // sentinels: head.next = MRU, tail.prev = LRU

    void unlink(Node* n) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
    void pushFront(Node* n) {
        n->prev = &head;
        n->next = head.next;
        head.next->prev = n;
        head.next = n;
    }

public:
    LRUCache(int capacity) : cap(capacity) {
        head.next = &tail;
        tail.prev = &head;
    }
    int get(int key) {
        auto it = m.find(key);             // find, not m[key]: don't insert on a miss
        if (it == m.end()) return -1;
        unlink(it->second);
        pushFront(it->second);
        return it->second->val;
    }
    void put(int key, int value) {
        auto it = m.find(key);
        if (it != m.end()) {               // update: no eviction
            it->second->val = value;
            unlink(it->second);
            pushFront(it->second);
            return;
        }
        if ((int)m.size() == cap) {
            Node* lru = tail.prev;
            unlink(lru);
            m.erase(lru->key);
            delete lru;
        }
        Node* n = new Node;
        n->key = key;
        n->val = value;
        m[key] = n;
        pushFront(n);
    }
    ~LRUCache() {
        for (auto& [k, n] : m) delete n;
    }
};

// ---------- Driver ----------
template <class C>
void run(const string& label, const vector<string>& ops, const vector<vector<int>>& args) {
    C c(args[0][0]);
    cout << label << ": [null";
    for (size_t i = 1; i < ops.size(); i++) {
        if (ops[i] == "put") { c.put(args[i][0], args[i][1]); cout << ",null"; }
        else cout << "," << c.get(args[i][0]);
    }
    cout << "]\n";
}

int main() {
    vector<pair<vector<string>, vector<vector<int>>>> tests = {
        {{"LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"},
         {{2}, {1, 1}, {2, 2}, {1}, {3, 3}, {2}, {4, 4}, {1}, {3}, {4}}},
        {{"LRUCache", "put", "get", "put", "get", "get"},
         {{1}, {2, 1}, {2}, {3, 2}, {2}, {3}}},
        {{"LRUCache", "put", "put", "put", "put", "get", "get", "get"},
         {{2}, {1, 1}, {2, 2}, {1, 10}, {3, 3}, {1}, {2}, {3}}},
    };
    for (auto& [ops, args] : tests) {
        run<LRUCacheBrute>("brute", ops, args);
        run<LRUCache>("dll  ", ops, args);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Sentinel nodes as members (Node head, tail;) are addressed with &head.
 * - A nested struct with default member initializers needs no constructor.
 * - Library variant: list<pair<int,int>> + unordered_map<int, list<...>::iterator>,
 *   and l.splice(l.begin(), l, it) moves a node to the front in O(1).
 * - Structured bindings in a range-for: for (auto& [k, n] : m).
 */
