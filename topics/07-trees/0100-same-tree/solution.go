/*
 * 0100. Same Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/same-tree/
 *
 * Problem: Are two binary trees identical in structure and values?
 *
 * Examples (level order, null = missing):
 *   [1,2,3], [1,2,3]        -> true
 *   [1,2],   [1,null,2]     -> false
 *   [1,2,1], [1,1,2]        -> false
 *   [],      []             -> true
 *   [1],     []             -> false
 *
 * Approaches:
 *   1. Recursive parallel DFS  ⭐   O(n) time, O(h) space   <- go-to
 *   2. Queue of pairs              O(n) time, O(w) space
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

// ---------- Approach 1: Recursive Parallel DFS ⭐ ----------
func isSameTree(p, q *TreeNode) bool {
	if p == nil && q == nil {
		return true
	}
	if p == nil || q == nil { // exactly one is nil
		return false
	}
	return p.Val == q.Val && isSameTree(p.Left, q.Left) && isSameTree(p.Right, q.Right)
}

// ---------- Approach 2: Queue of Pairs ----------
func isSameTreeBFS(p, q *TreeNode) bool {
	qu := [][2]*TreeNode{{p, q}}
	for len(qu) > 0 {
		a, b := qu[0][0], qu[0][1]
		qu = qu[1:]
		if a == nil && b == nil {
			continue
		}
		if a == nil || b == nil || a.Val != b.Val {
			return false
		}
		qu = append(qu, [2]*TreeNode{a.Left, b.Left}, [2]*TreeNode{a.Right, b.Right})
	}
	return true
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
	tests := [][2][]int{{{1, 2, 3}, {1, 2, 3}}, {{1, 2}, {1, null, 2}}, {{1, 2, 1}, {1, 1, 2}}, {{}, {}}, {{1}, {}}}
	for _, t := range tests {
		p, q := build(t[0]), build(t[1])
		fmt.Println("dfs:", isSameTree(p, q))
		fmt.Println("bfs:", isSameTreeBFS(p, q))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - [2]*TreeNode is a fixed-size pair of pointers, handy as a queue item.
 * - && short-circuits, so later recursive calls are skipped after a false.
 */
