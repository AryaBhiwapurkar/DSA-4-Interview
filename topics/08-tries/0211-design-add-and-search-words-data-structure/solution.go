/*
 * 0211. Design Add and Search Words Data Structure  |  Medium  |  Tries
 * Link: https://leetcode.com/problems/design-add-and-search-words-data-structure/
 *
 * Problem: addWord(word); search(pattern) where '.' matches any one letter.
 *
 * Examples:
 *   add bad, add dad, add mad, search pad, search bad, search .ad, search b..
 *     -> [null,null,null,null,false,true,true,true]
 *   add a, search ., search a., search ..
 *     -> [null,null,true,false,false]
 *
 * Approaches:
 *   1. List of words, compare each   O(N*L) per search
 *   2. Trie + wildcard DFS  ⭐        O(L) add, O(26^dots * L) search   <- go-to
 */

package main

import (
	"fmt"
	"strconv"
	"strings"
)

// ---------- Approach 1: List of Words ----------
type WordDictionaryList struct{ words []string }

func (d *WordDictionaryList) AddWord(w string) { d.words = append(d.words, w) }
func (d *WordDictionaryList) Search(p string) bool {
	for _, w := range d.words {
		if len(w) != len(p) {
			continue
		}
		ok := true
		for i := 0; i < len(p) && ok; i++ {
			ok = p[i] == '.' || p[i] == w[i]
		}
		if ok {
			return true
		}
	}
	return false
}

// ---------- Approach 2: Trie + Wildcard DFS ⭐ ----------
type node struct {
	next  [26]*node
	isEnd bool
}

type WordDictionary struct{ root *node }

func Constructor() WordDictionary { return WordDictionary{root: &node{}} }

func (d *WordDictionary) AddWord(w string) {
	n := d.root
	for i := 0; i < len(w); i++ {
		c := w[i] - 'a'
		if n.next[c] == nil {
			n.next[c] = &node{}
		}
		n = n.next[c]
	}
	n.isEnd = true
}

func (d *WordDictionary) Search(p string) bool {
	var dfs func(n *node, i int) bool
	dfs = func(n *node, i int) bool {
		if i == len(p) {
			return n.isEnd // whole pattern consumed
		}
		if p[i] != '.' {
			c := n.next[p[i]-'a']
			return c != nil && dfs(c, i+1) // one fixed branch
		}
		for _, c := range n.next { // '.': try every existing child
			if c != nil && dfs(c, i+1) {
				return true
			}
		}
		return false
	}
	return dfs(d.root, 0)
}

// ---------- Driver ----------
type dict interface {
	AddWord(string)
	Search(string) bool
}

func run(d dict, ops, args []string) string {
	out := []string{"null"}
	for i := 1; i < len(ops); i++ {
		if ops[i] == "addWord" {
			d.AddWord(args[i])
			out = append(out, "null")
		} else {
			out = append(out, strconv.FormatBool(d.Search(args[i])))
		}
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := []struct{ ops, args []string }{
		{[]string{"WordDictionary", "addWord", "addWord", "addWord", "search", "search", "search", "search"},
			[]string{"", "bad", "dad", "mad", "pad", "bad", ".ad", "b.."}},
		{[]string{"WordDictionary", "addWord", "search", "search", "search"}, []string{"", "a", ".", "a.", ".."}},
	}
	for _, tc := range tests {
		wd := Constructor()
		fmt.Println("list:", run(&WordDictionaryList{}, tc.ops, tc.args))
		fmt.Println("trie:", run(&wd, tc.ops, tc.args))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Ranging over a [26]*node array yields each child pointer (nil if absent).
 * - A recursive closure captures the pattern p, so it needs only (node, index).
 */
