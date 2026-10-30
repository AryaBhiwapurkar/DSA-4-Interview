/*
 * 0098. Validate Binary Search Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/validate-binary-search-tree/
 *
 * Problem: Is the tree a BST (left subtree strictly less, right strictly
 *          greater, at every node)?
 *
 * Examples (level order, null = missing):
 *   [2,1,3]                   -> true
 *   [5,1,4,null,null,3,6]     -> false
 *   [5,4,6,null,null,3,7]     -> false  (3 violates the grandparent 5)
 *   [2,2,2]                   -> false  (duplicates)
 *   [2147483647]              -> true   (no INT_MAX sentinels)
 *
 * Approaches:
 *   1. Inorder strictly increasing   O(n) time, O(h) space
 *   2. DFS with bounds  ⭐            O(n) time, O(h) space   <- go-to
 */

package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

type TreeNode struct {
	Val         int
	Left, Right *TreeNode
}

// ---------- Approach 1: Inorder Strictly Increasing ----------
func isValidBSTInorder(root *TreeNode) bool {
	var prev *int // nil = nothing seen yet (no sentinel value)
	var inorder func(n *TreeNode) bool
	inorder = func(n *TreeNode) bool {
		if n == nil {
			return true
		}
		if !inorder(n.Left) {
			return false
		}
		if prev != nil && n.Val <= *prev { // must strictly increase
			return false
		}
		v := n.Val
		prev = &v
		return inorder(n.Right)
	}
	return inorder(root)
}

// ---------- Approach 2: DFS With Bounds ⭐ ----------
func valid(n, lo, hi *TreeNode) bool { // bounds are ancestor nodes; nil = unbounded
	if n == nil {
		return true
	}
	if (lo != nil && n.Val <= lo.Val) || (hi != nil && n.Val >= hi.Val) {
		return false
	}
	return valid(n.Left, lo, n) && valid(n.Right, n, hi)
}

func isValidBST(root *TreeNode) bool { return valid(root, nil, nil) }

// ---------- Driver ----------
const null = math.MinInt // marks a missing node in level-order input

func build(vals []int) *TreeNode { // LeetCode level order
	if len(vals) == 0 || vals[0] == null {
		return nil
	}
	root := &TreeNode{Val: vals[0]}
	q := []*TreeNode{root}
	for i := 1; i < len(vals); i += 2 {
		n := q[0]
		q = q[1:]
		if vals[i] != null {
			n.Left = &TreeNode{Val: vals[i]}
			q = append(q, n.Left)
		}
		if i+1 < len(vals) && vals[i+1] != null {
			n.Right = &TreeNode{Val: vals[i+1]}
			q = append(q, n.Right)
		}
	}
	return root
}

func serialize(root *TreeNode) string { // level order, trailing nulls trimmed
	out := []string{}
	q := []*TreeNode{root}
	for len(q) > 0 {
		n := q[0]
		q = q[1:]
		if n == nil {
			out = append(out, "null")
			continue
		}
		out = append(out, strconv.Itoa(n.Val))
		q = append(q, n.Left, n.Right)
	}
	for len(out) > 0 && out[len(out)-1] == "null" {
		out = out[:len(out)-1]
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := [][]int{{2, 1, 3}, {5, 1, 4, null, null, 3, 6}, {5, 4, 6, null, null, 3, 7}, {2, 2, 2}, {2147483647}}
	for _, v := range tests {
		root := build(v)
		fmt.Println("inorder:", isValidBSTInorder(root))
		fmt.Println("bounds :", isValidBST(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Nullable bounds via pointers (nil = no bound) avoid sentinel values.
 * - Taking the address of a local copy (v := n.Val; prev = &v) is safe:
 *   Go moves it to the heap if needed.
 */
