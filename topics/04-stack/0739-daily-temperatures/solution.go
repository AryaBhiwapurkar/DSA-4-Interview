/*
 * 0739. Daily Temperatures  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/daily-temperatures/
 *
 * Problem: For each day, how many days until a strictly warmer one?
 *          0 if none.
 *
 * Examples:
 *   [73,74,75,71,69,72,76,73]  -> [1 1 4 2 1 1 0 0]
 *   [30,40,50,60]              -> [1 1 1 0]
 *   [30,60,90]                 -> [1 1 0]
 *   [70,70]                    -> [0 0]
 *   [5,4,3]                    -> [0 0 0]
 *
 * Approaches:
 *   1. Brute force         O(n^2) time, O(1) extra space
 *   2. Monotonic stack  ⭐  O(n) time, O(n) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Brute Force ----------
func dailyTemperaturesBrute(t []int) []int {
	ans := make([]int, len(t))
	for i := range t {
		for j := i + 1; j < len(t); j++ {
			if t[j] > t[i] {
				ans[i] = j - i
				break
			}
		}
	}
	return ans
}

// ---------- Approach 2: Monotonic Stack ⭐ ----------
func dailyTemperatures(t []int) []int {
	ans := make([]int, len(t)) // unresolved days stay 0
	st := []int{}              // indices; temps decreasing bottom -> top
	for i, temp := range t {
		for len(st) > 0 && temp > t[st[len(st)-1]] { // strictly warmer resolves
			j := st[len(st)-1]
			st = st[:len(st)-1]
			ans[j] = i - j
		}
		st = append(st, i)
	}
	return ans
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{73, 74, 75, 71, 69, 72, 76, 73}, {30, 40, 50, 60}, {30, 60, 90}, {70, 70}, {5, 4, 3}}
	for _, t := range tests {
		fmt.Println("brute:", dailyTemperaturesBrute(t))
		fmt.Println("stack:", dailyTemperatures(t))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - make([]int, n) is zero-filled, so unresolved days default to 0.
 * - `for cond {}` is Go's while loop.
 * - Pop = read st[len(st)-1], then reslice st = st[:len(st)-1].
 */
