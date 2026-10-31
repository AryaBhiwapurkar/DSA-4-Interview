/*
 * 0210. Course Schedule II  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/course-schedule-ii/
 *
 * Problem: n courses, pairs [a, b] meaning b before a. Return any order
 *          that takes every course, or [] if impossible.
 *
 * Examples:
 *   2, [[1,0]]                    -> [0 1]
 *   4, [[1,0],[2,0],[3,1],[3,2]]  -> [0 2 1 3] or [0 1 2 3]
 *   1, []                         -> [0]
 *   2, [[1,0],[0,1]]              -> []
 *
 * Approaches:
 *   1. DFS post-order (reversed)   O(V + E) time, O(V + E) space
 *   2. Kahn's algorithm  ⭐         O(V + E) time, O(V + E) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: DFS Post-Order ----------
func findOrderDFS(n int, pre [][]int) []int {
	adj := make([][]int, n)
	for _, p := range pre {
		adj[p[1]] = append(adj[p[1]], p[0])
	}
	color := make([]int, n)
	out := []int{}
	var post func(u int) bool
	post = func(u int) bool {
		color[u] = 1
		for _, v := range adj[u] {
			if color[v] == 1 {
				return false // back edge: cycle
			}
			if color[v] == 0 && !post(v) {
				return false
			}
		}
		color[u] = 2
		out = append(out, u) // after everything that depends on u
		return true
	}
	for u := 0; u < n; u++ {
		if color[u] == 0 && !post(u) {
			return []int{}
		}
	}
	slices.Reverse(out)
	return out
}

// ---------- Approach 2: Kahn's Algorithm ⭐ ----------
func findOrder(n int, pre [][]int) []int {
	adj := make([][]int, n)
	indeg := make([]int, n)
	for _, p := range pre {
		adj[p[1]] = append(adj[p[1]], p[0])
		indeg[p[0]]++
	}
	q := []int{}
	for u := 0; u < n; u++ {
		if indeg[u] == 0 {
			q = append(q, u)
		}
	}
	order := []int{}
	for len(q) > 0 {
		u := q[0]
		q = q[1:]
		order = append(order, u)
		for _, v := range adj[u] {
			indeg[v]--
			if indeg[v] == 0 {
				q = append(q, v)
			}
		}
	}
	if len(order) < n {
		return []int{} // cycle
	}
	return order
}

// ---------- Driver ----------
func valid(n int, pre [][]int, order []int) bool {
	if len(order) != n {
		return false
	}
	pos := make([]int, n)
	for i, u := range order {
		pos[u] = i
	}
	for _, p := range pre {
		if pos[p[1]] > pos[p[0]] {
			return false
		}
	}
	return true
}

func main() {
	tests := []struct {
		n   int
		pre [][]int
	}{{2, [][]int{{1, 0}}}, {4, [][]int{{1, 0}, {2, 0}, {3, 1}, {3, 2}}}, {1, nil}, {2, [][]int{{1, 0}, {0, 1}}}}
	for _, t := range tests {
		a, b := findOrderDFS(t.n, t.pre), findOrder(t.n, t.pre)
		fmt.Println("dfs :", a, "valid:", valid(t.n, t.pre, a))
		fmt.Println("kahn:", b, "valid:", valid(t.n, t.pre, b))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Reverse reverses in place (Go 1.21+).
 * - Return []int{} rather than nil when callers print it: both print as [].
 */
