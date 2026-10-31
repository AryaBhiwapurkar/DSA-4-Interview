/*
 * 0207. Course Schedule  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/course-schedule/
 *
 * Problem: n courses, pairs [a, b] meaning b before a. Can all be taken?
 *          (Is the prerequisite graph acyclic?)
 *
 * Examples:
 *   2, [[1,0]]                       -> true
 *   2, [[1,0],[0,1]]                 -> false
 *   3, []                            -> true
 *   4, [[1,0],[2,1],[3,2],[1,3]]     -> false (cycle 1-2-3)
 *   4, [[1,0],[2,0],[3,1],[3,2]]     -> true  (diamond)
 *
 * Approaches:
 *   1. DFS three-color            O(V + E) time, O(V + E) space
 *   2. Kahn's algorithm  ⭐        O(V + E) time, O(V + E) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: DFS Three-Color ----------
func canFinishDFS(n int, pre [][]int) bool {
	adj := make([][]int, n)
	for _, p := range pre {
		adj[p[1]] = append(adj[p[1]], p[0])
	}
	color := make([]int, n) // 0 new, 1 on path, 2 done
	var hasCycle func(u int) bool
	hasCycle = func(u int) bool {
		color[u] = 1
		for _, v := range adj[u] {
			if color[v] == 1 || (color[v] == 0 && hasCycle(v)) {
				return true // back edge
			}
		}
		color[u] = 2
		return false
	}
	for u := 0; u < n; u++ {
		if color[u] == 0 && hasCycle(u) {
			return false
		}
	}
	return true
}

// ---------- Approach 2: Kahn's Algorithm ⭐ ----------
func canFinish(n int, pre [][]int) bool {
	adj := make([][]int, n)
	indeg := make([]int, n)
	for _, p := range pre { // b -> a
		adj[p[1]] = append(adj[p[1]], p[0])
		indeg[p[0]]++
	}
	q := []int{}
	for u := 0; u < n; u++ {
		if indeg[u] == 0 {
			q = append(q, u)
		}
	}
	taken := 0
	for len(q) > 0 {
		u := q[0]
		q = q[1:]
		taken++
		for _, v := range adj[u] {
			indeg[v]--
			if indeg[v] == 0 {
				q = append(q, v)
			}
		}
	}
	return taken == n // leftovers sit on a cycle
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		n   int
		pre [][]int
	}{
		{2, [][]int{{1, 0}}}, {2, [][]int{{1, 0}, {0, 1}}}, {3, nil},
		{4, [][]int{{1, 0}, {2, 1}, {3, 2}, {1, 3}}}, {4, [][]int{{1, 0}, {2, 0}, {3, 1}, {3, 2}}},
	}
	for _, t := range tests {
		fmt.Println("dfs :", canFinishDFS(t.n, t.pre))
		fmt.Println("kahn:", canFinish(t.n, t.pre))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Appending to a nil inner slice (adj[u]) allocates it on demand.
 * - Ranging over a nil slice runs zero times, so `nil` works as "no edges".
 * - Go has no `--x` expression; decrement, then test.
 */
