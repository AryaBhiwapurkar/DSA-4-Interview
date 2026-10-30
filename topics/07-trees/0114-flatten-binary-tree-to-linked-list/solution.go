/*
 * 0114. Flatten Binary Tree to Linked List  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
 *
 * Problem: Flatten in place into a right-pointer chain in preorder;
 *          every left pointer becomes nil.
 *
 * Examples (level order, null = missing):
 *   [1,2,5,3,4,null,6]  -> [1,null,2,null,3,null,4,null,5,null,6]
 *   []                  -> []
 *   [0]                 -> [0]
 *   [1,2,null,3]        -> [1,null,2,null,3]   (left chain)
 *
 * Approaches:
 *   1. Preorder list, relink         O(n) time, O(n) space
 *   2. Reverse preorder with prev    O(n) time, O(h) stack
 *   3. In-place splicing  ⭐          O(n) time, O(1) space   <- go-to
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

// ---------- Approach 1: Preorder List, Relink ----------
func flattenList(root *TreeNode) {
	nodes := []*TreeNode{}
	var pre func(n *TreeNode)
	pre = func(n *TreeNode) {
		if n == nil {
			return
		}
		nodes = append(nodes, n)
		pre(n.Left)
		pre(n.Right)
	}
	pre(root)
	for i, n := range nodes {
		n.Left = nil
		n.Right = nil
		if i+1 < len(nodes) {
			n.Right = nodes[i+1]
		}
	}
}

// ---------- Approach 2: Reverse Preorder With prev ----------
func flattenReverse(root *TreeNode) {
	var prev *TreeNode
	var rev func(n *TreeNode)
	rev = func(n *TreeNode) {
		if n == nil {
			return
		}
		rev(n.Right) // right, left, node = reverse preorder
		rev(n.Left)
		n.Right, n.Left = prev, nil
		prev = n
	}
	rev(root)
}

// ---------- Approach 3: In-Place Splicing ⭐ ----------
func flatten(root *TreeNode) {
	for cur := root; cur != nil; cur = cur.Right {
		if cur.Left == nil {
			continue
		}
		pred := cur.Left // rightmost of the left subtree precedes cur.Right
		for pred.Right != nil {
			pred = pred.Right
		}
		pred.Right = cur.Right
		cur.Right, cur.Left = cur.Left, nil
	}
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
	for _, v := range [][]int{{1, 2, 5, 3, 4, null, 6}, {}, {0}, {1, 2, null, 3}} { // fresh tree per approach
		a, b, c := build(v), build(v), build(v)
		flattenList(a)
		flattenReverse(b)
		flatten(c)
		fmt.Println("list   :", serialize(a))
		fmt.Println("reverse:", serialize(b))
		fmt.Println("splice :", serialize(c))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - `cur.Right, cur.Left = cur.Left, nil` evaluates the RHS first.
 * - `continue` in a for-with-post still runs the post statement (cur = cur.Right).
 */
