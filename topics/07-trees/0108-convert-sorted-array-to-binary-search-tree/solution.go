/*
 * 0108. Convert Sorted Array to Binary Search Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
 *
 * Problem: Build a height-balanced BST from a sorted array of distinct ints.
 *          Any balanced BST is accepted.
 *
 * Examples (output in level order; left-middle choice, so it differs from
 * LeetCode's printed answer but is equally valid):
 *   [-10,-3,0,5,9]  -> [0,-10,5,null,-3,null,9]   (LC shows [0,-3,9,-10,null,5])
 *   [1,3]           -> [1,null,3]                 (LC shows [3,1])
 *   [1]             -> [1]
 *
 * Approaches:
 *   1. Recursive middle split  ⭐        O(n) time, O(log n) stack   <- go-to
 *   2. Iterative stack of (node, lo, hi) O(n) time, O(log n) space
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

// ---------- Approach 1: Recursive Middle Split ⭐ ----------
func sortedArrayToBST(nums []int) *TreeNode {
	var gen func(lo, hi int) *TreeNode
	gen = func(lo, hi int) *TreeNode {
		if lo > hi {
			return nil
		}
		mid := lo + (hi-lo)/2 // middle -> halves differ by at most 1
		return &TreeNode{Val: nums[mid], Left: gen(lo, mid-1), Right: gen(mid+1, hi)}
	}
	return gen(0, len(nums)-1)
}

// ---------- Approach 2: Iterative Stack of (node, lo, hi) ----------
func sortedArrayToBSTIter(a []int) *TreeNode {
	if len(a) == 0 {
		return nil
	}
	mid := func(lo, hi int) int { return lo + (hi-lo)/2 }
	type frame struct {
		node   *TreeNode
		lo, hi int
	}
	root := &TreeNode{Val: a[mid(0, len(a)-1)]}
	st := []frame{{root, 0, len(a) - 1}}
	for len(st) > 0 {
		f := st[len(st)-1]
		st = st[:len(st)-1]
		m := mid(f.lo, f.hi)
		if f.lo <= m-1 { // left range non-empty
			f.node.Left = &TreeNode{Val: a[mid(f.lo, m-1)]}
			st = append(st, frame{f.node.Left, f.lo, m - 1})
		}
		if m+1 <= f.hi {
			f.node.Right = &TreeNode{Val: a[mid(m+1, f.hi)]}
			st = append(st, frame{f.node.Right, m + 1, f.hi})
		}
	}
	return root
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
	for _, v := range [][]int{{-10, -3, 0, 5, 9}, {1, 3}, {1}} {
		fmt.Println("recursive:", serialize(sortedArrayToBST(v)))
		fmt.Println("iterative:", serialize(sortedArrayToBSTIter(v)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Struct literals with named fields can embed recursive calls.
 * - A func literal (mid) can be a local helper.
 */
