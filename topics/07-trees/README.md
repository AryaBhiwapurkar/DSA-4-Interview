# 07. Trees

## Core Idea
Almost every binary-tree problem is a traversal plus a decision about **what flows down** (parameters: depth, path max, remaining sum, allowed range) and **what flows up** (return values: height, gain, "found p or q"). DFS (recursion or a stack) handles path and subtree questions; BFS (a queue, one level at a time) handles level questions. For a BST, **inorder is sorted**, and the ordering lets you discard a whole subtree at each step (O(h) instead of O(n)).

## When to Use
- Height / depth / balance / diameter: DFS returning a value up (0104, 0110, 0543).
- Best path anywhere in the tree: return a one-sided value, record the bent path in a global (0543, 0124).
- Level by level, right side view, averages, zigzag: BFS with a level-size snapshot (0102, 0199, 0637, 0103).
- Root-to-node conditions: pass state down (0112, 0129, 1448, 0098).
- BST sorted order, k-th smallest, closest values: inorder (0230, 0530, 0173).
- BST search / LCA: walk down using the ordering (0235).
- Rebuild or encode trees: traversals + index maps, or null markers (0105, 0106, 0297).
- Compare structures: parallel DFS on two trees (0100, 0101, 0572).

## Templates

### DFS returning a value (height) + global answer
```cpp
int best = 0;
int dfs(TreeNode* n) {
    if (!n) return 0;
    int L = dfs(n->left), R = dfs(n->right);
    best = max(best, L + R);             // answer that "bends" at n
    return 1 + max(L, R);                // what the parent can use
}
```
```python
best = 0
def dfs(n):
    nonlocal best
    if not n:
        return 0
    L, R = dfs(n.left), dfs(n.right)
    best = max(best, L + R)
    return 1 + max(L, R)
```
```go
best := 0
var dfs func(n *TreeNode) int
dfs = func(n *TreeNode) int {
	if n == nil {
		return 0
	}
	L, R := dfs(n.Left), dfs(n.Right)
	best = max(best, L+R)
	return 1 + max(L, R)
}
```

### BFS by level
```cpp
queue<TreeNode*> q;
if (root) q.push(root);
while (!q.empty()) {
    for (int sz = q.size(); sz > 0; sz--) {   // exactly one level
        TreeNode* n = q.front(); q.pop();
        // process n
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
}
```
```python
q = deque([root] if root else [])
while q:
    for _ in range(len(q)):
        n = q.popleft()
        # process n
        if n.left: q.append(n.left)
        if n.right: q.append(n.right)
```
```go
q := []*TreeNode{}
if root != nil {
	q = append(q, root)
}
for len(q) > 0 {
	for sz := len(q); sz > 0; sz-- {
		n := q[0]
		q = q[1:]
		// process n
		if n.Left != nil {
			q = append(q, n.Left)
		}
		if n.Right != nil {
			q = append(q, n.Right)
		}
	}
}
```

### Iterative inorder (BST in sorted order)
```cpp
vector<TreeNode*> st;
for (TreeNode* cur = root; cur || !st.empty();) {
    while (cur) { st.push_back(cur); cur = cur->left; }
    cur = st.back(); st.pop_back();
    // visit cur (ascending order)
    cur = cur->right;
}
```
```python
st, cur = [], root
while cur or st:
    while cur:
        st.append(cur); cur = cur.left
    cur = st.pop()
    # visit cur
    cur = cur.right
```
```go
st := []*TreeNode{}
for cur := root; cur != nil || len(st) > 0; {
	for ; cur != nil; cur = cur.Left {
		st = append(st, cur)
	}
	cur = st[len(st)-1]
	st = st[:len(st)-1]
	// visit cur
	cur = cur.Right
}
```

## Common Variations
- **State passed down:** remaining sum (0112), number so far (0129), path max (1448), (lo, hi) bounds (0098).
- **Sentinel return values:** -1 for "unbalanced" (0110); null / node for "found" (0236).
- **Clamp negatives:** max(0, gain) when a branch can be skipped (0124).
- **Mirror recursion:** cross left/right arguments (0101).
- **Rebuild from traversals:** preorder/postorder give roots, inorder gives the split; a value→index map makes it O(n) (0105, 0106).
- **Null markers make one traversal enough** to serialize (0297, 0572).
- **O(1)-space tricks:** splice via the rightmost node of the left subtree (0114), walk levels through `next` (0117).
- **Use the shape:** perfect subtrees have 2^h - 1 nodes (0222); middle of a sorted array → balanced BST (0108).

## ⚠️ Pitfalls
- **Null checks first:** check `node` before `node.val`; check both nulls before comparing two trees.
- **Leaf vs null:** path problems end at leaves (no children), not at null children.
- **Local vs global BST checks:** compare against the whole allowed range, not just the parent (0098).
- **Sentinels at the int limits:** values can be INT_MIN / INT_MAX; use 64-bit or nullable bounds.
- **Python recursion limit (~1000):** deep skewed trees need BFS / an explicit stack or `sys.setrecursionlimit`.
- **Level size snapshot:** read the queue size before pushing children.
- **Build order with a shared index:** preorder builds left first, postorder (read backwards) builds right first.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0100 | [Same Tree](0100-same-tree/) | Easy | Parallel DFS | ✅ |
| 0101 | [Symmetric Tree](0101-symmetric-tree/) | Easy | Mirror DFS | ✅ |
| 0104 | [Maximum Depth of Binary Tree](0104-maximum-depth-of-binary-tree/) | Easy | DFS height | ✅ |
| 0108 | [Convert Sorted Array to Binary Search Tree](0108-convert-sorted-array-to-binary-search-tree/) | Easy | Divide at middle | ✅ |
| 0110 | [Balanced Binary Tree](0110-balanced-binary-tree/) | Easy | DFS height with early exit | ✅ |
| 0112 | [Path Sum](0112-path-sum/) | Easy | DFS with remaining sum | ✅ |
| 0222 | [Count Complete Tree Nodes](0222-count-complete-tree-nodes/) | Easy | Compare left/right heights | ✅ |
| 0226 | [Invert Binary Tree](0226-invert-binary-tree/) | Easy | DFS swap children | ✅ |
| 0530 | [Minimum Absolute Difference in BST](0530-minimum-absolute-difference-in-bst/) | Easy | Inorder, track prev | ✅ |
| 0543 | [Diameter of Binary Tree](0543-diameter-of-binary-tree/) | Easy | DFS height, update global | ✅ |
| 0572 | [Subtree of Another Tree](0572-subtree-of-another-tree/) | Easy | DFS + same-tree check | ✅ |
| 0637 | [Average of Levels in Binary Tree](0637-average-of-levels-in-binary-tree/) | Easy | BFS by level | ✅ |
| 0098 | [Validate Binary Search Tree](0098-validate-binary-search-tree/) | Medium | DFS with bounds | ✅ |
| 0102 | [Binary Tree Level Order Traversal](0102-binary-tree-level-order-traversal/) | Medium | BFS by level | ✅ |
| 0103 | [Binary Tree Zigzag Level Order Traversal](0103-binary-tree-zigzag-level-order-traversal/) | Medium | BFS, alternate direction | ✅ |
| 0105 | [Construct Binary Tree from Preorder and Inorder Traversal](0105-construct-binary-tree-from-preorder-and-inorder-traversal/) | Medium | Recursion + inorder index map | ✅ |
| 0106 | [Construct Binary Tree from Inorder and Postorder Traversal](0106-construct-binary-tree-from-inorder-and-postorder-traversal/) | Medium | Recursion + inorder index map | ✅ |
| 0114 | [Flatten Binary Tree to Linked List](0114-flatten-binary-tree-to-linked-list/) | Medium | Reverse preorder / Morris | ✅ |
| 0117 | [Populating Next Right Pointers in Each Node II](0117-populating-next-right-pointers-in-each-node-ii/) | Medium | Level linking with dummy | ✅ |
| 0129 | [Sum Root to Leaf Numbers](0129-sum-root-to-leaf-numbers/) | Medium | DFS carrying the number | ✅ |
| 0173 | [Binary Search Tree Iterator](0173-binary-search-tree-iterator/) | Medium | Controlled inorder with stack | ✅ |
| 0199 | [Binary Tree Right Side View](0199-binary-tree-right-side-view/) | Medium | BFS, last per level | ✅ |
| 0230 | [Kth Smallest Element in a BST](0230-kth-smallest-element-in-a-bst/) | Medium | Inorder traversal | ✅ |
| 0235 | [Lowest Common Ancestor of a Binary Search Tree](0235-lowest-common-ancestor-of-a-binary-search-tree/) | Medium | BST split point | ✅ |
| 0236 | [Lowest Common Ancestor of a Binary Tree](0236-lowest-common-ancestor-of-a-binary-tree/) | Medium | Postorder DFS | ✅ |
| 0427 | [Construct Quad Tree](0427-construct-quad-tree/) | Medium | Divide & conquer on grid | ✅ |
| 1448 | [Count Good Nodes in Binary Tree](1448-count-good-nodes-in-binary-tree/) | Medium | DFS with path max | ✅ |
| 0124 | [Binary Tree Maximum Path Sum](0124-binary-tree-maximum-path-sum/) | Hard | DFS gain, update global | ✅ |
| 0297 | [Serialize and Deserialize Binary Tree](0297-serialize-and-deserialize-binary-tree/) | Hard | Preorder with null markers | ✅ |
