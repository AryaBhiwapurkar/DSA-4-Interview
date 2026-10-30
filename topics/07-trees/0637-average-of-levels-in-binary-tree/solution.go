/*
 * 0637. Average of Levels in Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/average-of-levels-in-binary-tree/
 *
 * Problem: Average value of the nodes on each level, top to bottom.
 *
 * Examples (level order, null = missing):
 *   [3,9,20,null,null,15,7]                  -> [3.00000,14.50000,11.00000]
 *   [3,9,20,15,7]                            -> [3.00000,14.50000,11.00000]
 *   [2147483647,2147483647,2147483647]       -> [2147483647.00000,2147483647.00000]
 *
 * Approaches:
 *   1. BFS with level sum  ⭐          O(n) time, O(w) space   <- go-to
 *   2. DFS (sum, count) per depth      O(n) time, O(h) space
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

// ---------- Approach 1: BFS With Level Sum ⭐ ----------
func averageOfLevels(root *TreeNode) []float64 {
	res := []float64{}
	q := []*TreeNode{}
	if root != nil {
		q = append(q, root)
	}
	for len(q) > 0 {
		sz, sum := len(q), 0 // int is 64-bit: no overflow
		for i := 0; i < sz; i++ {
			n := q[0]
			q = q[1:]
			sum += n.Val
			if n.Left != nil {
				q = append(q, n.Left)
			}
			if n.Right != nil {
				q = append(q, n.Right)
			}
		}
		res = append(res, float64(sum)/float64(sz))
	}
	return res
}

// ---------- Approach 2: DFS (sum, count) per Depth ----------
func averageOfLevelsDFS(root *TreeNode) []float64 {
	sums, cnts := []int{}, []int{}
	var dfs func(n *TreeNode, d int)
	dfs = func(n *TreeNode, d int) {
		if n == nil {
			return
		}
		if d == len(sums) {
			sums, cnts = append(sums, 0), append(cnts, 0)
		}
		sums[d] += n.Val
		cnts[d]++
		dfs(n.Left, d+1)
		dfs(n.Right, d+1)
	}
	dfs(root, 0)
	res := make([]float64, len(sums))
	for i := range sums {
		res[i] = float64(sums[i]) / float64(cnts[i])
	}
	return res
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

func show(v []float64) string {
	parts := make([]string, len(v))
	for i, x := range v {
		parts[i] = fmt.Sprintf("%.5f", x)
	}
	return "[" + strings.Join(parts, ",") + "]"
}

func main() {
	for _, v := range [][]int{{3, 9, 20, null, null, 15, 7}, {3, 9, 20, 15, 7}, {2147483647, 2147483647, 2147483647}} {
		root := build(v)
		fmt.Println("bfs:", show(averageOfLevels(root)))
		fmt.Println("dfs:", show(averageOfLevelsDFS(root)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Convert both operands: float64(sum) / float64(sz).
 * - fmt.Sprintf("%.5f", x) formats a float with five decimals.
 */
