/*
 * 0049. Group Anagrams  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/group-anagrams/
 *
 * Problem: Group the strings that are anagrams of each other.
 *          Any order of groups / words is accepted.
 *
 * Examples (printed with groups sorted for stable output):
 *   ["eat","tea","tan","ate","nat","bat"] -> [["ate","eat","tea"],["bat"],["nat","tan"]]
 *   [""]                                  -> [[""]]
 *   ["a"]                                 -> [["a"]]
 *
 * Approaches:
 *   1. Pairwise compare        O(n^2 * k) time, O(n) space
 *   2. Sorted-string key  ⭐    O(n * k log k) time, O(n * k) space   <- go-to
 *   3. Letter-count key        O(n * k) time, O(n * k) space
 */

package main

import (
	"fmt"
	"slices"
)

func sameLetters(a, b string) bool {
	if len(a) != len(b) {
		return false
	}
	var cnt [26]int
	for i := 0; i < len(a); i++ {
		cnt[a[i]-'a']++
		cnt[b[i]-'a']--
	}
	return cnt == [26]int{} // arrays compare with ==
}

// ---------- Approach 1: Pairwise Compare ----------
func groupAnagramsBrute(strs []string) [][]string {
	var res [][]string
	used := make([]bool, len(strs))
	for i, s := range strs {
		if used[i] {
			continue
		}
		group := []string{s}
		for j := i + 1; j < len(strs); j++ {
			if !used[j] && sameLetters(s, strs[j]) {
				used[j] = true
				group = append(group, strs[j])
			}
		}
		res = append(res, group)
	}
	return res
}

// ---------- Approach 2: Sorted-String Key ⭐ ----------
func groupAnagrams(strs []string) [][]string {
	groups := make(map[string][]string)
	for _, s := range strs {
		b := []byte(s)
		slices.Sort(b)
		key := string(b)                     // all anagrams share this key
		groups[key] = append(groups[key], s) // nil slice + append works on first use
	}
	res := make([][]string, 0, len(groups))
	for _, words := range groups {
		res = append(res, words)
	}
	return res
}

// ---------- Approach 3: Letter-Count Key ----------
func groupAnagramsCount(strs []string) [][]string {
	groups := make(map[[26]int][]string) // fixed-size arrays are valid map keys
	for _, s := range strs {
		var cnt [26]int
		for i := 0; i < len(s); i++ {
			cnt[s[i]-'a']++
		}
		groups[cnt] = append(groups[cnt], s)
	}
	res := make([][]string, 0, len(groups))
	for _, words := range groups {
		res = append(res, words)
	}
	return res
}

// ---------- Driver ----------
func show(label string, g [][]string) {
	for _, grp := range g {
		slices.Sort(grp) // normalize: order is unspecified
	}
	slices.SortFunc(g, func(a, b []string) int { return slices.Compare(a, b) })
	fmt.Printf("%s: %q\n", label, g)
}

func main() {
	tests := [][]string{{"eat", "tea", "tan", "ate", "nat", "bat"}, {""}, {"a"}}
	for _, strs := range tests {
		show("brute ", groupAnagramsBrute(strs))
		show("sorted", groupAnagrams(strs))
		show("count ", groupAnagramsCount(strs))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Arrays ([26]int) are comparable and can be map keys; slices cannot.
 * - append on a nil slice from a missing map key just works.
 * - Map iteration order is random: sort before printing or comparing.
 * - slices.Compare orders slices lexicographically (handy in SortFunc).
 */
