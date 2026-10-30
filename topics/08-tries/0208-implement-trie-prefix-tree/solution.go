/*
 * 0208. Implement Trie (Prefix Tree)  |  Medium  |  Tries
 * Link: https://leetcode.com/problems/implement-trie-prefix-tree/
 *
 * Problem: insert(word), search(word) for an exact word, startsWith(prefix).
 *
 * Examples:
 *   insert apple, search apple, search app, startsWith app, insert app, search app
 *     -> [null,null,true,false,true,null,true]
 *   insert a, search a, startsWith b, search ab
 *     -> [null,null,true,false,false]
 *
 * Approaches:
 *   1. Hash set of words           O(L) insert/search, O(N*L) startsWith
 *   2. Trie with 26 children  ⭐    O(L) per operation   <- go-to
 */

package main

import (
	"fmt"
	"strconv"
	"strings"
)

// ---------- Approach 1: Hash Set of Words ----------
type TrieSet struct{ words map[string]bool }

func (t *TrieSet) Insert(w string)      { t.words[w] = true }
func (t *TrieSet) Search(w string) bool { return t.words[w] }
func (t *TrieSet) StartsWith(p string) bool {
	for w := range t.words { // scans every word: O(N * L)
		if strings.HasPrefix(w, p) {
			return true
		}
	}
	return false
}

// ---------- Approach 2: Trie With 26 Children ⭐ ----------
type node struct {
	next  [26]*node // zero value: all nil
	isEnd bool
}

type Trie struct{ root *node }

func Constructor() Trie { return Trie{root: &node{}} }

func (t *Trie) walk(s string) *node { // node at the end of s, or nil
	n := t.root
	for i := 0; i < len(s); i++ {
		n = n.next[s[i]-'a']
		if n == nil {
			return nil
		}
	}
	return n
}

func (t *Trie) Insert(w string) {
	n := t.root
	for i := 0; i < len(w); i++ {
		c := w[i] - 'a'
		if n.next[c] == nil {
			n.next[c] = &node{}
		}
		n = n.next[c]
	}
	n.isEnd = true
}

func (t *Trie) Search(w string) bool {
	n := t.walk(w)
	return n != nil && n.isEnd // path existing isn't enough
}

func (t *Trie) StartsWith(p string) bool { return t.walk(p) != nil }

// ---------- Driver ----------
type trier interface {
	Insert(string)
	Search(string) bool
	StartsWith(string) bool
}

func run(t trier, ops, args []string) string {
	out := []string{"null"}
	for i := 1; i < len(ops); i++ {
		switch ops[i] {
		case "insert":
			t.Insert(args[i])
			out = append(out, "null")
		case "search":
			out = append(out, strconv.FormatBool(t.Search(args[i])))
		default:
			out = append(out, strconv.FormatBool(t.StartsWith(args[i])))
		}
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := []struct{ ops, args []string }{
		{[]string{"Trie", "insert", "search", "search", "startsWith", "insert", "search"},
			[]string{"", "apple", "apple", "app", "app", "app", "app"}},
		{[]string{"Trie", "insert", "search", "startsWith", "search"}, []string{"", "a", "a", "b", "ab"}},
	}
	for _, tc := range tests {
		tr := Constructor()
		fmt.Println("set :", run(&TrieSet{words: map[string]bool{}}, tc.ops, tc.args))
		fmt.Println("trie:", run(&tr, tc.ops, tc.args))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - [26]*node is a fixed array of pointers; its zero value is all nil.
 * - s[i]-'a' is a byte, usable directly as an array index.
 * - strings.HasPrefix(s, p) tests a prefix.
 */
