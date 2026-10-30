/*
 * 0853. Car Fleet  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/car-fleet/
 *
 * Problem: Cars drive to target on one lane and can't pass; a car that
 *          catches up joins that fleet. Count fleets arriving at target.
 *
 * Examples:
 *   target 12,  pos [10,8,0,5,3], speed [2,4,1,1,3]  -> 3
 *   target 10,  pos [3],          speed [3]          -> 1
 *   target 100, pos [0,2,4],      speed [4,2,1]      -> 1
 *   target 10,  pos [0,4,8],      speed [1,1,1]      -> 3
 *
 * Approaches:
 *   1. Sort + stack of fleet times     O(n log n) time, O(n) space
 *   2. Sort + slowest fleet time  ⭐    O(n log n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"sort"
)

type car struct{ pos, speed int }

func sortedCars(position, speed []int) []car {
	cars := make([]car, len(position))
	for i := range position {
		cars[i] = car{position[i], speed[i]}
	}
	sort.Slice(cars, func(a, b int) bool { return cars[a].pos > cars[b].pos }) // closest to target first
	return cars
}

// ---------- Approach 1: Sort + Stack of Fleet Times ----------
func carFleetStack(target int, position, speed []int) int {
	st := []float64{} // arrival time of each fleet ahead
	for _, c := range sortedCars(position, speed) {
		st = append(st, float64(target-c.pos)/float64(c.speed))
		if len(st) >= 2 && st[len(st)-1] <= st[len(st)-2] { // caught up: merged
			st = st[:len(st)-1]
		}
	}
	return len(st)
}

// ---------- Approach 2: Sort + Slowest Fleet Time ⭐ ----------
func carFleet(target int, position, speed []int) int {
	fleets, last := 0, 0.0 // last = arrival time of the fleet directly ahead
	for _, c := range sortedCars(position, speed) {
		t := float64(target-c.pos) / float64(c.speed)
		if t > last { // can't catch it: new, slower fleet
			fleets++
			last = t
		}
	}
	return fleets
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		target     int
		pos, speed []int
	}{
		{12, []int{10, 8, 0, 5, 3}, []int{2, 4, 1, 1, 3}},
		{10, []int{3}, []int{3}},
		{100, []int{0, 2, 4}, []int{4, 2, 1}},
		{10, []int{0, 4, 8}, []int{1, 1, 1}},
	}
	for _, t := range tests {
		fmt.Println("stack  :", carFleetStack(t.target, t.pos, t.speed))
		fmt.Println("slowest:", carFleet(t.target, t.pos, t.speed))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Go never converts int to float64 implicitly: float64(a) / float64(b).
 * - sort.Slice with `>` sorts descending.
 * - `fleets, last := 0, 0.0` infers int and float64.
 */
