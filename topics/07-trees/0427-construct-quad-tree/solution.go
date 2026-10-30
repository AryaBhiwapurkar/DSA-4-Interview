/*
 * 0427. Construct Quad Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/construct-quad-tree/
 *
 * Problem: Build the quad tree of an n x n 0/1 grid (n a power of 2).
 *          Output: level order of [isLeaf, val] with null for missing children.
 *
 * Examples:
 *   [[0,1],[1,0]]       -> [[0,1],[1,0],[1,1],[1,1],[1,0]]
 *   8x8 (see README)    -> [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
 *   [[1]]               -> [[1,1]]
 *   [[0,0],[0,0]]       -> [[1,0]]
 *
 * Approaches:
 *   1. Check then split  ⭐          O(n^2 log n) time, O(log n) stack   <- go-to
 *   2. Split then merge (bottom-up)  O(n^2) time, O(log n) stack
 */

package main

import (
	"fmt"
	"strings"
)

type Node struct {
	Val, IsLeaf                                bool
	TopLeft, TopRight, BottomLeft, BottomRight *Node
}

// ---------- Approach 1: Check Then Split ⭐ ----------
func construct(grid [][]int) *Node {
	var gen func(r, c, size int) *Node
	gen = func(r, c, size int) *Node {
		uniform := true
		for i := r; i < r+size && uniform; i++ {
			for j := c; j < c+size; j++ {
				if grid[i][j] != grid[r][c] {
					uniform = false
					break
				}
			}
		}
		if uniform {
			return &Node{Val: grid[r][c] == 1, IsLeaf: true}
		}
		h := size / 2 // TL, TR, BL, BR: rows first, then columns
		return &Node{Val: true, IsLeaf: false,
			TopLeft: gen(r, c, h), TopRight: gen(r, c+h, h), BottomLeft: gen(r+h, c, h), BottomRight: gen(r+h, c+h, h)}
	}
	return gen(0, 0, len(grid))
}

// ---------- Approach 2: Split Then Merge ----------
func constructMerge(grid [][]int) *Node {
	var gen func(r, c, size int) *Node
	gen = func(r, c, size int) *Node {
		if size == 1 {
			return &Node{Val: grid[r][c] == 1, IsLeaf: true}
		}
		h := size / 2
		tl, tr, bl, br := gen(r, c, h), gen(r, c+h, h), gen(r+h, c, h), gen(r+h, c+h, h)
		if tl.IsLeaf && tr.IsLeaf && bl.IsLeaf && br.IsLeaf && tl.Val == tr.Val && tr.Val == bl.Val && bl.Val == br.Val {
			return &Node{Val: tl.Val, IsLeaf: true} // four equal leaves collapse into one
		}
		return &Node{Val: true, IsLeaf: false, TopLeft: tl, TopRight: tr, BottomLeft: bl, BottomRight: br}
	}
	return gen(0, 0, len(grid))
}

// ---------- Driver ----------
func b2i(b bool) int {
	if b {
		return 1
	}
	return 0
}

func serialize(root *Node) string { // LeetCode format: level order of [isLeaf,val]
	out := []string{}
	q := []*Node{root}
	for len(q) > 0 {
		n := q[0]
		q = q[1:]
		if n == nil {
			out = append(out, "null")
			continue
		}
		out = append(out, fmt.Sprintf("[%d,%d]", b2i(n.IsLeaf), b2i(n.Val)))
		q = append(q, n.TopLeft, n.TopRight, n.BottomLeft, n.BottomRight)
	}
	for len(out) > 0 && out[len(out)-1] == "null" {
		out = out[:len(out)-1]
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := [][][]int{
		{{0, 1}, {1, 0}},
		{{1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 0, 0, 0}},
		{{1}},
		{{0, 0}, {0, 0}},
	}
	for _, g := range tests {
		fmt.Println("split:", serialize(construct(g)))
		fmt.Println("merge:", serialize(constructMerge(g)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Go bools don't convert to ints: a tiny b2i helper does it.
 * - grid[r][c] == 1 turns an int cell into a bool.
 * - Several struct fields of the same type share one declaration line.
 */
