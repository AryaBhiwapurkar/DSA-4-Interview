/*
 * 0637. Average of Levels in Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/average-of-levels-in-binary-tree/
 *
 * Problem: Average value of the nodes on each level, top to bottom.
 *
 * Examples (level order, null = missing):
 *   [3,9,20,null,null,15,7]                  -> [3.00000,14.50000,11.00000]
 *   [3,9,20,15,7]                            -> [3.00000,14.50000,11.00000]
 *   [2147483647,2147483647,2147483647]       -> [2147483647.00000,2147483647.00000]
 *
 * Approaches:
 *   1. BFS with level sum  ⭐          O(n) time, O(w) space   <- go-to
 *   2. DFS (sum, count) per depth      O(n) time, O(h) space
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(x), left(l), right(r) {}
};

// ---------- Approach 1: BFS With Level Sum ⭐ ----------
vector<double> averageOfLevels(TreeNode* root) {
    vector<double> res;
    queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        long long sum = 0;                 // a level of big values overflows int
        for (int i = 0; i < sz; i++) {
            TreeNode* n = q.front();
            q.pop();
            sum += n->val;
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        res.push_back((double)sum / sz);
    }
    return res;
}

// ---------- Approach 2: DFS (sum, count) per Depth ----------
void dfs(TreeNode* n, int d, vector<long long>& sum, vector<int>& cnt) {
    if (!n) return;
    if (d == (int)sum.size()) { sum.push_back(0); cnt.push_back(0); }
    sum[d] += n->val;
    cnt[d]++;
    dfs(n->left, d + 1, sum, cnt);
    dfs(n->right, d + 1, sum, cnt);
}

vector<double> averageOfLevelsDFS(TreeNode* root) {
    vector<long long> sum;
    vector<int> cnt;
    dfs(root, 0, sum, cnt);
    vector<double> res;
    for (size_t i = 0; i < sum.size(); i++) res.push_back((double)sum[i] / cnt[i]);
    return res;
}

// ---------- Driver ----------
const int null = INT_MIN;                  // marks a missing node in level-order input

TreeNode* build(const vector<int>& v) {    // LeetCode level order
    if (v.empty() || v[0] == null) return nullptr;
    TreeNode* root = new TreeNode(v[0]);
    queue<TreeNode*> q;
    q.push(root);
    for (size_t i = 1; i < v.size(); i += 2) {
        TreeNode* n = q.front();
        q.pop();
        if (v[i] != null) q.push(n->left = new TreeNode(v[i]));
        if (i + 1 < v.size() && v[i + 1] != null) q.push(n->right = new TreeNode(v[i + 1]));
    }
    return root;
}

string serialize(TreeNode* root) {         // level order, trailing nulls trimmed
    vector<string> out;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        out.push_back(n ? to_string(n->val) : "null");
        if (n) { q.push(n->left); q.push(n->right); }
    }
    while (!out.empty() && out.back() == "null") out.pop_back();
    string s = "[";
    for (size_t i = 0; i < out.size(); i++) s += (i ? "," : "") + out[i];
    return s + "]";
}

void print(const string& label, const vector<double>& v) {
    printf("%s: [", label.c_str());
    for (size_t i = 0; i < v.size(); i++) printf("%s%.5f", i ? "," : "", v[i]);
    printf("]\n");
}

int main() {
    vector<vector<int>> tests = {{3, 9, 20, null, null, 15, 7}, {3, 9, 20, 15, 7}, {2147483647, 2147483647, 2147483647}};
    for (auto& v : tests) {
        TreeNode* root = build(v);
        print("bfs", averageOfLevels(root));
        print("dfs", averageOfLevelsDFS(root));
        printf("---\n");
    }
}

/*
 * Syntax notes (C++):
 * - long long sum; (double)sum / sz forces floating division.
 * - printf("%.5f") for fixed decimals; label.c_str() for %s.
 */
