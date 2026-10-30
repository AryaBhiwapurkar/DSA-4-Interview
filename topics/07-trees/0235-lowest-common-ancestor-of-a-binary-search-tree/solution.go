/*
 * 0235. Lowest Common Ancestor of a Binary Search Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 *
 * Problem: In a BST, return the deepest node that has both p and q as
 *          descendants (a node is its own descendant).
 *
 * Examples (level order, null = missing; answer printed as a value):
 *   [6,2,8,0,4,7,9,null,null,3,5], p 2, q 8  -> 6
 *   [6,2,8,0,4,7,9,null,null,3,5], p 2, q 4  -> 2
 *   [2,1],                         p 2, q 1  -> 2
 *   [6,2,8,0,4,7,9,null,null,3,5], p 3, q 5  -> 4
 *
 * Approaches:
 *   1. Recursive descent        O(h) time, O(h) stack
 *   2. Iterative descent  ⭐     O(h) time, O(1) space   <- go-to
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

// ---------- Approach 1: Recursive Descent ----------
func lcaRecursive(root, p, q *TreeNode) *TreeNode {
	if p.Val < root.Val && q.Val < root.Val {
		return lcaRecursive(root.Left, p, q)
	}
	if p.Val > root.Val && q.Val > root.Val {
		return lcaRecursive(root.Right, p, q)
	}
	return root // split point (or root is p or q)
}

// ---------- Approach 2: Iterative Descent ⭐ ----------
func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	for root != nil {
		switch {
		case p.Val < root.Val && q.Val < root.Val: // strict: stop on equality
			root = root.Left
		case p.Val > root.Val && q.Val > root.Val:
			root = root.Right
		default:
			return root
		}
	}
	return nil // unreachable when p and q exist
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

func find(root *TreeNode, v int) *TreeNode { // BST lookup to get the actual node
	for root != nil && root.Val != v {
		if v < root.Val {
			root = root.Left
		} else {
			root = root.Right
		}
	}
	return root
}

func main() {
	big := []int{6, 2, 8, 0, 4, 7, 9, null, null, 3, 5}
	tests := []struct {
		v    []int
		a, b int
	}{{big, 2, 8}, {big, 2, 4}, {[]int{2, 1}, 2, 1}, {big, 3, 5}}
	for _, t := range tests {
		root := build(t.v)
		p, q := find(root, t.a), find(root, t.b)
		fmt.Println("recursive:", lcaRecursive(root, p, q).Val)
		fmt.Println("iterative:", lowestCommonAncestor(root, p, q).Val)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A tagless switch reads like the three-way BST decision.
 * - The driver's find() turns test values into the node pointers LeetCode passes.
 */
