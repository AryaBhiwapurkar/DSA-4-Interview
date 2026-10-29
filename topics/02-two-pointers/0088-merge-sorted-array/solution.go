/*
 * 0088. Merge Sorted Array  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/merge-sorted-array/
 *
 * Problem: nums1 holds m sorted values plus n free slots; nums2 holds n
 *          sorted values. Merge nums2 into nums1 in place, sorted.
 *
 * Examples:
 *   [1,2,3,0,0,0], m=3, [2,5,6], n=3   -> [1,2,2,3,5,6]
 *   [1], m=1, [], n=0                  -> [1]
 *   [0], m=0, [1], n=1                 -> [1]
 *   [4,5,0,0], m=2, [1,2], n=2         -> [1,2,4,5]
 *
 * Approaches:
 *   1. Copy + sort              O((m+n) log(m+n)) time, O(1) extra
 *   2. Forward merge with copy  O(m+n) time, O(m) space
 *   3. Backward merge  ⭐        O(m+n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Copy + Sort ----------
func mergeSort(nums1 []int, m int, nums2 []int, n int) {
	copy(nums1[m:], nums2)
	slices.Sort(nums1)
}

// ---------- Approach 2: Forward Merge With a Copy ----------
func mergeForward(nums1 []int, m int, nums2 []int, n int) {
	a := slices.Clone(nums1[:m]) // save nums1's values before overwriting
	i, j := 0, 0
	for w := 0; w < m+n; w++ {
		if j == n || (i < m && a[i] <= nums2[j]) {
			nums1[w] = a[i]
			i++
		} else {
			nums1[w] = nums2[j]
			j++
		}
	}
}

// ---------- Approach 3: Backward Merge ⭐ ----------
func merge(nums1 []int, m int, nums2 []int, n int) {
	i, j, w := m-1, n-1, m+n-1
	for j >= 0 { // once nums2 is used up, nums1's rest is in place
		if i >= 0 && nums1[i] > nums2[j] {
			nums1[w] = nums1[i]
			i--
		} else {
			nums1[w] = nums2[j]
			j--
		}
		w--
	}
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums1 []int
		m     int
		nums2 []int
		n     int
	}{
		{[]int{1, 2, 3, 0, 0, 0}, 3, []int{2, 5, 6}, 3},
		{[]int{1}, 1, []int{}, 0},
		{[]int{0}, 0, []int{1}, 1},
		{[]int{4, 5, 0, 0}, 2, []int{1, 2}, 2},
	}
	for _, t := range tests {
		a, b, c := slices.Clone(t.nums1), slices.Clone(t.nums1), slices.Clone(t.nums1)
		mergeSort(a, t.m, t.nums2, t.n)
		mergeForward(b, t.m, t.nums2, t.n)
		merge(c, t.m, t.nums2, t.n)
		fmt.Println("sort    :", a)
		fmt.Println("forward :", b)
		fmt.Println("backward:", c)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - copy(dst[m:], src) writes src into the tail of dst.
 * - slices.Clone(nums1[:m]) copies a prefix (a plain reslice would share memory).
 * - Go's i++ / i-- are statements, so update indices on separate lines.
 */
