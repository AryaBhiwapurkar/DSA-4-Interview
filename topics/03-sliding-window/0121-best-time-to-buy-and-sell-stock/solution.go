/*
 * 0121. Best Time to Buy and Sell Stock  |  Easy  |  Sliding Window
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 *
 * Problem: Buy on one day and sell on a later day; return the max profit
 *          (0 if no profit is possible).
 *
 * Examples:
 *   [7,1,5,3,6,4]  -> 5
 *   [7,6,4,3,1]    -> 0
 *   [2,4,1]        -> 2
 *   [5]            -> 0
 *
 * Approaches:
 *   1. Brute force        O(n^2) time, O(1) space
 *   2. Running min  ⭐     O(n) time, O(1) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Brute Force ----------
func maxProfitBrute(prices []int) int {
	best := 0
	for i := range prices {
		for j := i + 1; j < len(prices); j++ {
			best = max(best, prices[j]-prices[i])
		}
	}
	return best
}

// ---------- Approach 2: Running Min ⭐ ----------
func maxProfit(prices []int) int {
	minPrice, best := prices[0], 0
	for _, p := range prices[1:] {
		best = max(best, p-minPrice) // sell today, bought at the cheapest earlier day
		minPrice = min(minPrice, p)
	}
	return best
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{7, 1, 5, 3, 6, 4}, {7, 6, 4, 3, 1}, {2, 4, 1}, {5}}
	for _, p := range tests {
		fmt.Println("brute  :", maxProfitBrute(p))
		fmt.Println("run min:", maxProfit(p))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Seed the min with prices[0] and range over prices[1:] (n >= 1 guaranteed).
 * - math.MaxInt also works as an "infinity" seed.
 * - min/max are built-ins since Go 1.21.
 */
