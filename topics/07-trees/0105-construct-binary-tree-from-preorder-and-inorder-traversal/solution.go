/*
 * 0105. Construct Binary Tree from Preorder and Inorder Traversal  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 *
 * Problem: Rebuild a tree (unique values) from its preorder and inorder.
 *
 * Examples (output in level order):
 *   pre [3,9,20,15,7], in [9,3,15,20,7]  -> [3,9,20,null,null,15,7]
 *   pre [-1],          in [-1]           -> [-1]
 *   pre [1,2,3],       in [3,2,1]        -> [1,2,null,3]   (left-skewed)
 *
 * Approaches:
 *   1. Slice + linear search         O(n^2) time, O(n^2) space
 *   2. Index ranges + hashmap  ⭐     O(n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"math"
	"slices"
	"strconv"
	"strings"
)

type TreeNode struct {
	Val         int
	Left, Right *TreeNode
}

// ---------- Approach 1: Slice + Linear Search ----------
func buildTreeSlice(pre, in []int) *TreeNode {
	if len(pre) == 0 {
		return nil
	}
	mid := slices.Index(in, pre[0]) // O(n) search
	return &TreeNode{
		Val:   pre[0],
		Left:  buildTreeSlice(pre[1:1+mid], in[:mid]),
		Right: buildTreeSlice(pre[1+mid:], in[mid+1:]),
	}
}

// ---------- Approach 2: Index Ranges + Hashmap ⭐ ----------
func buildTree(preorder, inorder []int) *TreeNode {
	pos := make(map[int]int, len(inorder)) // value -> inorder index
	for i, v := range inorder {
		pos[v] = i
	}
	idx := 0
	var gen func(lo, hi int) *TreeNode
	gen = func(lo, hi int) *TreeNode {
		if lo > hi {
			return nil
		}
		val := preorder[idx] // next preorder value is this subtree's root
		idx++
		root := &TreeNode{Val: val}
		mid := pos[val]
		root.Left = gen(lo, mid-1) // LEFT first: preorder order
		root.Right = gen(mid+1, hi)
		return root
	}
	return gen(0, len(inorder)-1)
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
	tests := [][2][]int{{{3, 9, 20, 15, 7}, {9, 3, 15, 20, 7}}, {{-1}, {-1}}, {{1, 2, 3}, {3, 2, 1}}}
	for _, t := range tests {
		fmt.Println("slice:", serialize(buildTreeSlice(t[0], t[1])))
		fmt.Println("map  :", serialize(buildTree(t[0], t[1])))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Go sub-slices share memory (no copying), so approach 1 here is O(n^2)
 *   only because of the linear slices.Index search.
 * - make(map[int]int, n) pre-sizes the map.
 * - Named-field struct literals can nest recursive calls.
 */
