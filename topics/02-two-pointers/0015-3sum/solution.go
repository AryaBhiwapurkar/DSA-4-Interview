/*
 * 0015. 3Sum  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/3sum/
 *
 * Problem: Return all unique value-triplets [a,b,c] from different indices
 *          with a + b + c == 0. Any order.
 *
 * Examples (printed sorted for stable output):
 *   [-1,0,1,2,-1,-4]  -> [[-1,-1,2],[-1,0,1]]
 *   [0,1,1]           -> []
 *   [0,0,0]           -> [[0,0,0]]
 *   [0,0,0,0]         -> [[0,0,0]]
 *
 * Approaches:
 *   1. Brute force + set        O(n^3) time, O(k) space
 *   2. Hash set per fixed i     O(n^2) time, O(n) space
 *   3. Sort + two pointers  ⭐   O(n^2) time, O(1) extra space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

func sorted3(a, b, c int) [3]int {
	t := [3]int{a, b, c}
	slices.Sort(t[:]) // canonical order for dedup
	return t
}

func toSlices(found map[[3]int]bool) [][]int {
	res := [][]int{}
	for t := range found {
		res = append(res, []int{t[0], t[1], t[2]})
	}
	return res
}

// ---------- Approach 1: Brute Force + Set ----------
func threeSumBrute(nums []int) [][]int {
	found := map[[3]int]bool{}
	n := len(nums)
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			for k := j + 1; k < n; k++ {
				if nums[i]+nums[j]+nums[k] == 0 {
					found[sorted3(nums[i], nums[j], nums[k])] = true
				}
			}
		}
	}
	return toSlices(found)
}

// ---------- Approach 2: Hash Set per Fixed Element ----------
func threeSumHash(nums []int) [][]int {
	found := map[[3]int]bool{}
	for i := range nums {
		seen := map[int]bool{}
		for j := i + 1; j < len(nums); j++ {
			need := -nums[i] - nums[j]
			if seen[need] {
				found[sorted3(nums[i], nums[j], need)] = true
			}
			seen[nums[j]] = true
		}
	}
	return toSlices(found)
}

// ---------- Approach 3: Sort + Two Pointers ⭐ ----------
func threeSum(nums []int) [][]int {
	a := slices.Clone(nums)
	slices.Sort(a)
	res := [][]int{}
	n := len(a)
	for i := 0; i < n-2; i++ {
		if a[i] > 0 { // smallest is positive: no more zeros possible
			break
		}
		if i > 0 && a[i] == a[i-1] { // same first value already handled
			continue
		}
		l, r := i+1, n-1
		for l < r {
			sum := a[i] + a[l] + a[r]
			switch {
			case sum < 0:
				l++
			case sum > 0:
				r--
			default:
				res = append(res, []int{a[i], a[l], a[r]})
				l, r = l+1, r-1
				for l < r && a[l] == a[l-1] { // skip duplicate seconds
					l++
				}
				for l < r && a[r] == a[r+1] { // skip duplicate thirds
					r--
				}
			}
		}
	}
	return res
}

// ---------- Driver ----------
func show(label string, v [][]int) {
	slices.SortFunc(v, func(x, y []int) int { return slices.Compare(x, y) }) // normalize: order is unspecified
	fmt.Println(label+":", v)
}

func main() {
	tests := [][]int{{-1, 0, 1, 2, -1, -4}, {0, 1, 1}, {0, 0, 0}, {0, 0, 0, 0}}
	for _, nums := range tests {
		show("brute   ", threeSumBrute(nums))
		show("hash    ", threeSumHash(nums))
		show("pointers", threeSum(nums))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - [3]int arrays are comparable, so they work as map keys for dedup.
 * - t[:] turns an array into a slice (to pass to slices.Sort).
 * - map[int]bool as a set: missing keys read false.
 */
