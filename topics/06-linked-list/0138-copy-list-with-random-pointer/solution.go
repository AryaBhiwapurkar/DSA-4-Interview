/*
 * 0138. Copy List with Random Pointer  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/copy-list-with-random-pointer/
 *
 * Problem: Deep-copy a list whose nodes have next and random pointers.
 *          Shown as [val, index of random or null].
 *
 * Examples (printed as the copy, then whether it shares no nodes with the input):
 *   [[7,null],[13,0],[11,4],[10,2],[1,0]]  -> same, deep
 *   [[1,1],[2,1]]                          -> same, deep
 *   [[3,null],[3,0],[3,null]]              -> same, deep
 *   []                                     -> [], deep
 *
 * Approaches:
 *   1. Two-pass hashmap  ⭐     O(n) time, O(n) space   <- go-to
 *   2. Interleave copies       O(n) time, O(1) extra space
 */

package main

import (
	"fmt"
	"strconv"
	"strings"
)

type Node struct {
	Val    int
	Next   *Node
	Random *Node
}

// ---------- Approach 1: Two-Pass Hashmap ⭐ ----------
func copyRandomList(head *Node) *Node {
	cp := map[*Node]*Node{} // missing key (incl. nil) reads as nil
	for p := head; p != nil; p = p.Next {
		cp[p] = &Node{Val: p.Val}
	}
	for p := head; p != nil; p = p.Next { // all copies exist: forward randoms are safe
		cp[p].Next = cp[p.Next]
		cp[p].Random = cp[p.Random]
	}
	return cp[head]
}

// ---------- Approach 2: Interleave Copies ----------
func copyRandomListInterleave(head *Node) *Node {
	for p := head; p != nil; p = p.Next.Next { // A -> A' -> B -> B' ...
		p.Next = &Node{Val: p.Val, Next: p.Next}
	}
	for p := head; p != nil; p = p.Next.Next {
		if p.Random != nil {
			p.Next.Random = p.Random.Next // copy of random = random's next
		}
	}
	dummy := &Node{}
	tail := dummy
	for p := head; p != nil; p = p.Next { // split, restoring the original
		tail.Next = p.Next
		tail = tail.Next
		p.Next = p.Next.Next
	}
	return dummy.Next
}

// ---------- Driver ----------
func build(spec [][2]int) *Node { // {val, random index or -1}
	nodes := make([]*Node, len(spec))
	for i, s := range spec {
		nodes[i] = &Node{Val: s[0]}
	}
	for i, s := range spec {
		if i+1 < len(nodes) {
			nodes[i].Next = nodes[i+1]
		}
		if s[1] >= 0 {
			nodes[i].Random = nodes[s[1]]
		}
	}
	if len(nodes) == 0 {
		return nil
	}
	return nodes[0]
}

func show(orig, cp *Node) string {
	origSet := map[*Node]bool{}
	for p := orig; p != nil; p = p.Next {
		origSet[p] = true
	}
	idx := map[*Node]int{}
	i := 0
	for p := cp; p != nil; p = p.Next {
		idx[p] = i
		i++
	}
	parts, deep := []string{}, true
	for p := cp; p != nil; p = p.Next {
		if origSet[p] || (p.Random != nil && origSet[p.Random]) {
			deep = false
		}
		r := "null"
		if p.Random != nil {
			r = strconv.Itoa(idx[p.Random])
		}
		parts = append(parts, fmt.Sprintf("[%d,%s]", p.Val, r))
	}
	return "[" + strings.Join(parts, ",") + "] deep=" + strconv.FormatBool(deep)
}

func main() {
	tests := [][][2]int{
		{{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}}, {{1, 1}, {2, 1}}, {{3, -1}, {3, 0}, {3, -1}}, {},
	}
	for _, spec := range tests {
		a := build(spec)
		fmt.Println("hashmap   :", show(a, copyRandomList(a)))
		b := build(spec)
		fmt.Println("interleave:", show(b, copyRandomListInterleave(b))) // show also checks b was restored
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - map[*Node]*Node keys on pointer identity; a nil key reads as nil.
 * - &Node{Val: v, Next: n} sets named fields; the rest are zero (nil).
 * - fmt.Sprintf builds a string; strconv.FormatBool prints true/false.
 */
