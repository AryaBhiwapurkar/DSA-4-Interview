/*
 * 0981. Time Based Key-Value Store  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/time-based-key-value-store/
 *
 * Problem: set(key, value, t) stores a version; get(key, t) returns the
 *          value with the largest timestamp <= t, or "". Set timestamps
 *          are strictly increasing.
 *
 * Examples:
 *   set foo bar 1, get foo 1, get foo 3, set foo bar2 4, get foo 4, get foo 5
 *     -> [null,null,"bar","bar",null,"bar2","bar2"]
 *   set a x 5, get a 4, get b 1, get a 5
 *     -> [null,null,"","","x"]
 *
 * Approaches:
 *   1. Hashmap + linear scan        O(1) set, O(n) get, O(n) space
 *   2. Hashmap + binary search  ⭐   O(1) set, O(log n) get, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"sort"
	"strconv"
	"strings"
)

type entry struct {
	t   int
	val string
}

// ---------- Approach 1: Hashmap + Linear Scan ----------
type TimeMapLinear struct{ m map[string][]entry }

func (tm *TimeMapLinear) Set(key, value string, t int) {
	tm.m[key] = append(tm.m[key], entry{t, value})
}
func (tm *TimeMapLinear) Get(key string, t int) string {
	v := tm.m[key]                     // missing key: nil slice, length 0
	for i := len(v) - 1; i >= 0; i-- { // newest first
		if v[i].t <= t {
			return v[i].val
		}
	}
	return ""
}

// ---------- Approach 2: Hashmap + Binary Search ⭐ ----------
type TimeMap struct{ m map[string][]entry } // per key: sorted by time for free

func Constructor() TimeMap { return TimeMap{m: map[string][]entry{}} }

func (tm *TimeMap) Set(key, value string, t int) { tm.m[key] = append(tm.m[key], entry{t, value}) }
func (tm *TimeMap) Get(key string, t int) string {
	v := tm.m[key]
	i := sort.Search(len(v), func(j int) bool { return v[j].t > t }) // upper bound
	if i == 0 {
		return ""
	}
	return v[i-1].val
}

// ---------- Driver ----------
type timeMapper interface {
	Set(key, value string, t int)
	Get(key string, t int) string
}

func run(tm timeMapper, ops []string, args [][]string) string {
	out := []string{"null"} // ops[0] is the constructor
	for i := 1; i < len(ops); i++ {
		if ops[i] == "set" {
			t, _ := strconv.Atoi(args[i][2])
			tm.Set(args[i][0], args[i][1], t)
			out = append(out, "null")
		} else {
			t, _ := strconv.Atoi(args[i][1])
			out = append(out, strconv.Quote(tm.Get(args[i][0], t)))
		}
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := []struct {
		ops  []string
		args [][]string
	}{
		{[]string{"TimeMap", "set", "get", "get", "set", "get", "get"},
			[][]string{{}, {"foo", "bar", "1"}, {"foo", "1"}, {"foo", "3"}, {"foo", "bar2", "4"}, {"foo", "4"}, {"foo", "5"}}},
		{[]string{"TimeMap", "set", "get", "get", "get"},
			[][]string{{}, {"a", "x", "5"}, {"a", "4"}, {"b", "1"}, {"a", "5"}}},
	}
	for _, t := range tests {
		tm := Constructor()
		fmt.Println("linear:", run(&TimeMapLinear{m: map[string][]entry{}}, t.ops, t.args))
		fmt.Println("binary:", run(&tm, t.ops, t.args))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - sort.Search(n, pred) returns the first index where pred is true;
 *   with `> t` that's the upper bound.
 * - Reading a missing map key gives the zero value (nil slice), and
 *   append(nil, x) works, so Set needs no existence check.
 * - A struct holding a map must initialise it (map[string][]entry{}) before
 *   writes; writing to a nil map panics.
 * - strconv.Quote(s) wraps a string in double quotes.
 */
