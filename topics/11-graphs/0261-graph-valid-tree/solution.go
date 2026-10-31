/*
 * 0261. Graph Valid Tree  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/graph-valid-tree/
 *
 * Problem: Do n nodes and these undirected edges form a tree
 *          (connected and acyclic)?
 *
 * Examples:
 *   5, [[0,1],[0,2],[0,3],[1,4]]         -> true
 *   5, [[0,1],[1,2],[2,3],[1,3],[1,4]]   -> false
 *   1, []                                -> true
 *   4, [[0,1],[2,3]]                     -> false (two components)
 *   4, [[0,1],[1,2],[2,0]]               -> false (cycle, node 3 isolated)
 *
 * Approaches:
 *   1. DFS connectivity + edge count     O(n + E) time, O(n + E) space
 *   2. Edge count + Union-Find  ⭐        O(n + E * alpha) time, O(n) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: DFS Connectivity + Edge Count ----------
func validTreeDFS(n int, edges [][]int) bool {
	if len(edges) != n-1 {
		return false
	}
	adj := make([][]int, n)
	for _, e := range edges {
		adj[e[0]] = append(adj[e[0]], e[1])
		adj[e[1]] = append(adj[e[1]], e[0])
	}
	seen := make([]bool, n)
	seen[0] = true
	st, reached := []int{0}, 1
	for len(st) > 0 {
		u := st[len(st)-1]
		st = st[:len(st)-1]
		for _, v := range adj[u] {
			if !seen[v] {
				seen[v] = true
				reached++
				st = append(st, v)
			}
		}
	}
	return reached == n // n-1 edges + connected => acyclic
}

// ---------- Approach 2: Edge Count + Union-Find ⭐ ----------
type DSU struct{ parent, rank []int }

func newDSU(n int) *DSU {
	d := &DSU{make([]int, n), make([]int, n)}
	for i := range d.parent {
		d.parent[i] = i
	}
	return d
}

func (d *DSU) find(x int) int {
	if d.parent[x] != x {
		d.parent[x] = d.find(d.parent[x])
	}
	return d.parent[x]
}

func (d *DSU) union(a, b int) bool {
	a, b = d.find(a), d.find(b)
	if a == b {
		return false // already connected: this edge closes a cycle
	}
	if d.rank[a] < d.rank[b] {
		a, b = b, a
	}
	d.parent[b] = a
	if d.rank[a] == d.rank[b] {
		d.rank[a]++
	}
	return true
}

func validTree(n int, edges [][]int) bool {
	if len(edges) != n-1 {
		return false
	}
	dsu := newDSU(n)
	for _, e := range edges {
		if !dsu.union(e[0], e[1]) {
			return false
		}
	}
	return true
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		n     int
		edges [][]int
	}{
		{5, [][]int{{0, 1}, {0, 2}, {0, 3}, {1, 4}}}, {5, [][]int{{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}}},
		{1, nil}, {4, [][]int{{0, 1}, {2, 3}}}, {4, [][]int{{0, 1}, {1, 2}, {2, 0}}},
	}
	for _, t := range tests {
		fmt.Println("dfs:", validTreeDFS(t.n, t.edges))
		fmt.Println("uf :", validTree(t.n, t.edges))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A struct of two slices (parent, rank) is the usual Go DSU.
 * - `a, b = d.find(a), d.find(b)` reassigns both before the comparison.
 */
