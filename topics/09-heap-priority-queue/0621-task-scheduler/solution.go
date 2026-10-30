/*
 * 0621. Task Scheduler  |  Medium  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/task-scheduler/
 *
 * Problem: Unit-time tasks A-Z; equal tasks must be >= n units apart (idle
 *          allowed). Minimum total time.
 *
 * Examples:
 *   [A,A,A,B,B,B], n 2                  -> 8
 *   [A,C,A,B,D,B], n 1                  -> 6
 *   [A,A,A,B,B,B], n 3                  -> 10
 *   [A,A,A,A,A,A,B,C,D,E,F,G], n 2      -> 16
 *   [A,B,A], n 0                        -> 3
 *
 * Approaches:
 *   1. Max-heap + cooldown queue   O(T log 26) time, O(26) space
 *   2. Counting formula  ⭐         O(T) time, O(1) space   <- go-to
 */

package main

import (
	"container/heap"
	"fmt"
	"slices"
)

type MaxHeap []int

func (h MaxHeap) Len() int           { return len(h) }
func (h MaxHeap) Less(i, j int) bool { return h[i] > h[j] }
func (h MaxHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *MaxHeap) Push(x any)        { *h = append(*h, x.(int)) }
func (h *MaxHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

// ---------- Approach 1: Max-Heap + Cooldown Queue ----------
func leastIntervalHeap(tasks []byte, n int) int {
	var cnt [26]int
	for _, t := range tasks {
		cnt[t-'A']++
	}
	h := &MaxHeap{} // remaining counts of available tasks
	for _, c := range cnt {
		if c > 0 {
			*h = append(*h, c)
		}
	}
	heap.Init(h)
	type cooling struct{ count, ready int }
	cool := []cooling{}
	time := 0
	for h.Len() > 0 || len(cool) > 0 {
		time++
		if h.Len() > 0 { // run the most frequent available task
			c := heap.Pop(h).(int) - 1
			if c > 0 {
				cool = append(cool, cooling{c, time + n})
			}
		} // else: idle this unit
		if len(cool) > 0 && cool[0].ready == time {
			heap.Push(h, cool[0].count)
			cool = cool[1:]
		}
	}
	return time
}

// ---------- Approach 2: Counting Formula ⭐ ----------
func leastInterval(tasks []byte, n int) int {
	var cnt [26]int
	for _, t := range tasks {
		cnt[t-'A']++
	}
	maxc := slices.Max(cnt[:])
	tied := 0 // tasks sharing the max count
	for _, c := range cnt {
		if c == maxc {
			tied++
		}
	}
	return max(len(tasks), (maxc-1)*(n+1)+tied) // enough variety -> no idling
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		s string
		n int
	}{{"AAABBB", 2}, {"ACABDB", 1}, {"AAABBB", 3}, {"AAAAAABCDEFG", 2}, {"ABA", 0}}
	for _, t := range tests {
		fmt.Println("heap   :", leastIntervalHeap([]byte(t.s), t.n))
		fmt.Println("formula:", leastInterval([]byte(t.s), t.n))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - cnt[:] turns a fixed array into a slice (for slices.Max).
 * - Filling the heap's slice directly, then heap.Init, is an O(n) heapify.
 */
