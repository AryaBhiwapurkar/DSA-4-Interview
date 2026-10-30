/*
 * 0230. Kth Smallest Element in a BST  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/kth-smallest-element-in-a-bst/
 *
 * Problem: Return the k-th smallest value (1-indexed) in a BST.
 *
 * Examples (level order, null = missing):
 *   [3,1,4,null,2],            k 1  -> 1
 *   [5,3,6,2,4,null,null,1],   k 3  -> 3
 *   [5,3,6,2,4,null,null,1],   k 6  -> 6
 *   [1],                       k 1  -> 1
 *
 * Approaches:
 *   1. Full inorder into a list       O(n) time, O(n) space
 *   2. Iterative inorder, stop at k ⭐ O(h + k) time, O(h) space   <- go-to
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

// ---------- Approach 1: Full Inorder Into a List ----------
func kthSmallestList(root *TreeNode, k int) int {
	vals := []int{}
	var inorder func(n *TreeNode)
	inorder = func(n *TreeNode) {
		if n == nil {
			return
		}
		inorder(n.Left)
		vals = append(vals, n.Val)
		inorder(n.Right)
	}
	inorder(root)
	return vals[k-1]
}

// ---------- Approach 2: Iterative Inorder, Stop at k ⭐ ----------
func kthSmallest(root *TreeNode, k int) int {
	st := []*TreeNode{}
	cur := root
	for cur != nil || len(st) > 0 {
		for cur != nil { // go as far left as possible
			st = append(st, cur)
			cur = cur.Left
		}
		cur = st[len(st)-1]
		st = st[:len(st)-1]
		k--
		if k == 0 { // k-th node in sorted order
			return cur.Val
		}
		cur = cur.Right
	}
	return -1 // unreachable for valid k
}

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
	t2 := []int{5, 3, 6, 2, 4, null, null, 1}
	tests := []struct {
		v []int
		k int
	}{{[]int{3, 1, 4, null, 2}, 1}, {t2, 3}, {t2, 6}, {[]int{1}, 1}}
	for _, t := range tests {
		root := build(t.v)
		fmt.Println("list :", kthSmallestList(root, t.k))
		fmt.Println("stack:", kthSmallest(root, t.k))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - k is a copy (pass by value), so decrementing it doesn't affect the caller.
 * - Explicit stack = slice of pointers; pop by reslicing.
 */
