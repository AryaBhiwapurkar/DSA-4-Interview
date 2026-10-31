/*
 * 0133. Clone Graph  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/clone-graph/
 *
 * Problem: Deep-copy a connected undirected graph given one of its nodes.
 *          Test input/output is an adjacency list (node i+1's neighbours).
 *
 * Examples:
 *   [[2,4],[1,3],[2,4],[1,3]]  -> [[2 4] [1 3] [2 4] [1 3]]
 *   [[]]                       -> [[]]
 *   []                         -> []
 *   [[2],[1,3],[2]]            -> [[2] [1 3] [2]]   (path 1-2-3)
 *
 * Approaches:
 *   1. DFS + map  ⭐   O(V + E) time, O(V) space   <- go-to
 *   2. BFS + map       O(V + E) time, O(V) space
 */

package main

import (
	"fmt"
	"slices"
)

type Node struct {
	Val       int
	Neighbors []*Node
}

// ---------- Approach 1: DFS + Map ⭐ ----------
func cloneGraph(node *Node) *Node {
	copies := map[*Node]*Node{}
	var dfs func(n *Node) *Node
	dfs = func(n *Node) *Node {
		if c, ok := copies[n]; ok {
			return c
		}
		c := &Node{Val: n.Val}
		copies[n] = c // before recursing: cycles find it
		for _, nb := range n.Neighbors {
			c.Neighbors = append(c.Neighbors, dfs(nb))
		}
		return c
	}
	if node == nil {
		return nil
	}
	return dfs(node)
}

// ---------- Approach 2: BFS + Map ----------
func cloneGraphBFS(node *Node) *Node {
	if node == nil {
		return nil
	}
	copies := map[*Node]*Node{node: {Val: node.Val}}
	q := []*Node{node}
	for len(q) > 0 {
		cur := q[0]
		q = q[1:]
		for _, nb := range cur.Neighbors {
			if _, ok := copies[nb]; !ok {
				copies[nb] = &Node{Val: nb.Val}
				q = append(q, nb)
			}
			copies[cur].Neighbors = append(copies[cur].Neighbors, copies[nb])
		}
	}
	return copies[node]
}

// ---------- Driver ----------
func build(adj [][]int) []*Node {
	nodes := make([]*Node, len(adj))
	for i := range adj {
		nodes[i] = &Node{Val: i + 1}
	}
	for i, nbs := range adj {
		for _, v := range nbs {
			nodes[i].Neighbors = append(nodes[i].Neighbors, nodes[v-1])
		}
	}
	return nodes
}

func collect(start *Node) []*Node {
	if start == nil {
		return nil
	}
	seen := map[*Node]bool{start: true}
	out, st := []*Node{}, []*Node{start}
	for len(st) > 0 {
		cur := st[len(st)-1]
		st = st[:len(st)-1]
		out = append(out, cur)
		for _, nb := range cur.Neighbors {
			if !seen[nb] {
				seen[nb] = true
				st = append(st, nb)
			}
		}
	}
	slices.SortFunc(out, func(a, b *Node) int { return a.Val - b.Val })
	return out
}

func show(clone *Node, orig []*Node) string {
	adj := [][]int{}
	deep := true
	for _, n := range collect(clone) {
		if slices.Contains(orig, n) {
			deep = false
		}
		row := []int{}
		for _, nb := range n.Neighbors {
			row = append(row, nb.Val)
		}
		adj = append(adj, row)
	}
	return fmt.Sprint(adj, " deep copy: ", deep)
}

func main() {
	tests := [][][]int{{{2, 4}, {1, 3}, {2, 4}, {1, 3}}, {{}}, {}, {{2}, {1, 3}, {2}}}
	for _, adj := range tests {
		orig := build(adj)
		var start *Node
		if len(orig) > 0 {
			start = orig[0]
		}
		fmt.Println("dfs:", show(cloneGraph(start), orig))
		fmt.Println("bfs:", show(cloneGraphBFS(start), orig))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - map[*Node]*Node keys on pointer identity.
 * - In a map literal of pointers, `node: {Val: 1}` is shorthand for &Node{Val: 1}.
 * - slices.Contains(orig, n) compares pointers with ==.
 */
