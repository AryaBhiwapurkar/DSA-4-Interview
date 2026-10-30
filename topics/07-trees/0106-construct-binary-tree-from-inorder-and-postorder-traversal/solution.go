/*
 * 0106. Construct Binary Tree from Inorder and Postorder Traversal  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
 *
 * Problem: Rebuild a tree (unique values) from its inorder and postorder.
 *
 * Examples (output in level order):
 *   in [9,3,15,20,7], post [9,15,7,20,3]  -> [3,9,20,null,null,15,7]
 *   in [-1],          post [-1]           -> [-1]
 *   in [1,2,3],       post [3,2,1]        -> [1,null,2,null,3]   (right-skewed)
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
func buildTreeSlice(in, post []int) *TreeNode {
	if len(post) == 0 {
		return nil
	}
	rootVal := post[len(post)-1]
	mid := slices.Index(in, rootVal) // O(n) search
	return &TreeNode{
		Val:   rootVal,
		Left:  buildTreeSlice(in[:mid], post[:mid]),
		Right: buildTreeSlice(in[mid+1:], post[mid:len(post)-1]),
	}
}

// ---------- Approach 2: Index Ranges + Hashmap ⭐ ----------
func buildTree(inorder, postorder []int) *TreeNode {
	pos := make(map[int]int, len(inorder))
	for i, v := range inorder {
		pos[v] = i
	}
	idx := len(postorder) - 1
	var gen func(lo, hi int) *TreeNode
	gen = func(lo, hi int) *TreeNode {
		if lo > hi {
			return nil
		}
		val := postorder[idx] // postorder read backwards: root, right..., left...
		idx--
		root := &TreeNode{Val: val}
		mid := pos[val]
		root.Right = gen(mid+1, hi) // RIGHT first
		root.Left = gen(lo, mid-1)
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
	tests := [][2][]int{{{9, 3, 15, 20, 7}, {9, 15, 7, 20, 3}}, {{-1}, {-1}}, {{1, 2, 3}, {3, 2, 1}}}
	for _, t := range tests {
		fmt.Println("slice:", serialize(buildTreeSlice(t[0], t[1])))
		fmt.Println("map  :", serialize(buildTree(t[0], t[1])))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - In a struct literal, fields are evaluated in source order; in approach 1
 *   that's harmless because each call gets its own sub-slices.
 * - In approach 2 the order of the two gen calls matters (shared idx).
 */
