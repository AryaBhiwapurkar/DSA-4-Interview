/*
 * 0380. Insert Delete GetRandom O(1)  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/insert-delete-getrandom-o1/
 *
 * Problem: Design a set with insert, remove (both return whether they
 *          changed the set) and getRandom (uniform), all O(1) average.
 *
 * Examples:
 *   insert 1, remove 2, insert 2, getRandom, remove 1, insert 2, getRandom
 *   -> true, false, true, (1 or 2), true, false, 2
 *
 * Approaches:
 *   1. Hash set only               insert/remove O(1), getRandom O(n)
 *   2. Map + array, swap-delete  ⭐  all O(1) average, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"math/rand"
)

// ---------- Approach 1: Hash Set Only ----------
type RandomizedSetNaive struct{ s map[int]struct{} }

func NewRandomizedSetNaive() *RandomizedSetNaive {
	return &RandomizedSetNaive{s: map[int]struct{}{}}
}

func (r *RandomizedSetNaive) Insert(val int) bool {
	if _, ok := r.s[val]; ok {
		return false
	}
	r.s[val] = struct{}{}
	return true
}

func (r *RandomizedSetNaive) Remove(val int) bool {
	if _, ok := r.s[val]; !ok {
		return false
	}
	delete(r.s, val)
	return true
}

func (r *RandomizedSetNaive) GetRandom() int {
	k := rand.Intn(len(r.s))
	for v := range r.s { // O(n) walk: maps have no random access
		if k == 0 {
			return v
		}
		k--
	}
	return 0
}

// ---------- Approach 2: Map + Array, Swap-Delete ⭐ ----------
type RandomizedSet struct {
	arr []int
	pos map[int]int // value -> index in arr
}

func Constructor() RandomizedSet {
	return RandomizedSet{pos: map[int]int{}}
}

func (r *RandomizedSet) Insert(val int) bool {
	if _, ok := r.pos[val]; ok {
		return false
	}
	r.pos[val] = len(r.arr)
	r.arr = append(r.arr, val)
	return true
}

func (r *RandomizedSet) Remove(val int) bool {
	idx, ok := r.pos[val] // comma-ok: index 0 is a valid position
	if !ok {
		return false
	}
	last := r.arr[len(r.arr)-1]
	r.arr[idx] = last // fill the hole with the last element
	r.pos[last] = idx // update BEFORE deleting (val may equal last)
	r.arr = r.arr[:len(r.arr)-1]
	delete(r.pos, val)
	return true
}

func (r *RandomizedSet) GetRandom() int {
	return r.arr[rand.Intn(len(r.arr))]
}

// ---------- Driver ----------
type set interface {
	Insert(int) bool
	Remove(int) bool
	GetRandom() int
}

func run(label string, rs set) {
	a, b, c := rs.Insert(1), rs.Remove(2), rs.Insert(2)
	x := rs.GetRandom()
	d, e, f := rs.Remove(1), rs.Insert(2), rs.GetRandom()
	fmt.Printf("%s: %v %v %v (rand in {1,2}: %v) %v %v %v\n", label, a, b, c, x == 1 || x == 2, d, e, f)
}

func main() {
	run("naive", NewRandomizedSetNaive())
	rs := Constructor()
	run("map+array", &rs)
}

/*
 * Syntax notes (Go):
 * - Methods with pointer receivers mutate the struct; pass &rs to an interface.
 * - A small interface lets one driver run both implementations.
 * - rand.Intn(n) returns [0, n); auto-seeded since Go 1.20.
 * - Map iteration order is randomized, but NOT uniformly: don't rely on it for getRandom.
 */
