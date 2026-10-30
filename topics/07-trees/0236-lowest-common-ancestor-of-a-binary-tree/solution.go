/*
 * 0236. Lowest Common Ancestor of a Binary Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
 *
 * Problem: LCA of two distinct nodes p, q in a general binary tree.
 *
 * Examples (level order, null = missing; answer printed as a value):
 *   [3,5,1,6,2,0,8,null,null,7,4], p 5, q 1  -> 3
 *   [3,5,1,6,2,0,8,null,null,7,4], p 5, q 4  -> 5
 *   [1,2],                         p 1, q 2  -> 1
 *   [3,5,1,6,2,0,8,null,null,7,4], p 7, q 8  -> 3
 *
 * Approaches:
 *   1. Parent pointers + ancestor set   O(n) time, O(n) space
 *   2. Recursive postorder  ⭐           O(n) time, O(h) space   <- go-to
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

// ---------- Approach 1: Parent Pointers + Ancestor Set ----------
func lcaParents(root, p, q *TreeNode) *TreeNode {
	parent := map[*TreeNode]*TreeNode{root: nil}
	st := []*TreeNode{root}
	for {
		_, okP := parent[p]
		_, okQ := parent[q]
		if okP && okQ { // stop once both are mapped
			break
		}
		n := st[len(st)-1]
		st = st[:len(st)-1]
		for _, c := range []*TreeNode{n.Left, n.Right} {
			if c != nil {
				parent[c] = n
				st = append(st, c)
			}
		}
	}
	anc := map[*TreeNode]bool{}
	for a := p; a != nil; a = parent[a] {
		anc[a] = true
	}
	b := q
	for !anc[b] {
		b = parent[b]
	}
	return b
}

// ---------- Approach 2: Recursive Postorder ⭐ ----------
func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	if root == nil || root == p || root == q { // found one (or nothing)
		return root
	}
	L := lowestCommonAncestor(root.Left, p, q)
	R := lowestCommonAncestor(root.Right, p, q)
	if L != nil && R != nil { // p and q on different sides
		return root
	}
	if L != nil { // pass up whichever side found something
		return L
	}
	return R
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

func findVal(n *TreeNode, v int) *TreeNode { // locate the node LeetCode would pass
	if n == nil || n.Val == v {
		return n
	}
	if l := findVal(n.Left, v); l != nil {
		return l
	}
	return findVal(n.Right, v)
}

func main() {
	big := []int{3, 5, 1, 6, 2, 0, 8, null, null, 7, 4}
	tests := []struct {
		v    []int
		a, b int
	}{{big, 5, 1}, {big, 5, 4}, {[]int{1, 2}, 1, 2}, {big, 7, 8}}
	for _, t := range tests {
		root := build(t.v)
		p, q := findVal(root, t.a), findVal(root, t.b)
		fmt.Println("parents  :", lcaParents(root, p, q).Val)
		fmt.Println("postorder:", lowestCommonAncestor(root, p, q).Val)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - The root's parent is stored as nil, so a comma-ok check tells
 *   "mapped to nil" apart from "not mapped yet".
 * - Pointer comparison (root == p) checks node identity.
 */
