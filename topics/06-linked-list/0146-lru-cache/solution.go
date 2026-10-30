/*
 * 0146. LRU Cache  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/lru-cache/
 *
 * Problem: Fixed-capacity cache; get(key) -> value or -1; put(key, value)
 *          inserts/updates and evicts the least recently used key. O(1).
 *
 * Examples:
 *   cap 2: put 1 1, put 2 2, get 1, put 3 3, get 2, put 4 4, get 1, get 3, get 4
 *     -> [null,null,null,1,null,-1,null,-1,3,4]
 *   cap 1: put 2 1, get 2, put 3 2, get 2, get 3
 *     -> [null,null,1,null,-1,2]
 *   cap 2: put 1 1, put 2 2, put 1 10, put 3 3, get 1, get 2, get 3   (update = use)
 *     -> [null,null,null,null,null,10,-1,3]
 *
 * Approaches:
 *   1. Ordered list, linear search    O(cap) per op, O(cap) space
 *   2. Hashmap + DLL  ⭐               O(1) per op, O(cap) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
	"strconv"
	"strings"
)

// ---------- Approach 1: Ordered List, Linear Search ----------
type LRUCacheBrute struct {
	cap   int
	items [][2]int // {key, value}; last = most recent
}

func (c *LRUCacheBrute) Get(key int) int {
	for i, kv := range c.items {
		if kv[0] == key {
			c.items = append(slices.Delete(c.items, i, i+1), kv) // mark as most recent
			return kv[1]
		}
	}
	return -1
}

func (c *LRUCacheBrute) Put(key, value int) {
	c.items = slices.DeleteFunc(c.items, func(kv [2]int) bool { return kv[0] == key })
	if len(c.items) == c.cap {
		c.items = c.items[1:] // evict least recent
	}
	c.items = append(c.items, [2]int{key, value})
}

// ---------- Approach 2: Hashmap + Doubly Linked List ⭐ ----------
type node struct {
	key, val   int // key stored so eviction can delete it from the map
	prev, next *node
}

type LRUCache struct {
	cap        int
	m          map[int]*node
	head, tail *node // sentinels: head.next = MRU, tail.prev = LRU
}

func Constructor(capacity int) LRUCache {
	head, tail := &node{}, &node{}
	head.next, tail.prev = tail, head
	return LRUCache{cap: capacity, m: map[int]*node{}, head: head, tail: tail}
}

func (c *LRUCache) unlink(n *node) {
	n.prev.next, n.next.prev = n.next, n.prev
}

func (c *LRUCache) pushFront(n *node) {
	n.prev, n.next = c.head, c.head.next
	c.head.next.prev = n
	c.head.next = n
}

func (c *LRUCache) Get(key int) int {
	n, ok := c.m[key]
	if !ok {
		return -1
	}
	c.unlink(n)
	c.pushFront(n)
	return n.val
}

func (c *LRUCache) Put(key, value int) {
	if n, ok := c.m[key]; ok { // update: no eviction
		n.val = value
		c.unlink(n)
		c.pushFront(n)
		return
	}
	if len(c.m) == c.cap {
		lru := c.tail.prev
		c.unlink(lru)
		delete(c.m, lru.key)
	}
	n := &node{key: key, val: value}
	c.m[key] = n
	c.pushFront(n)
}

// ---------- Driver ----------
type cache interface {
	Get(key int) int
	Put(key, value int)
}

func run(c cache, ops []string, args [][]int) string {
	out := []string{"null"}
	for i := 1; i < len(ops); i++ {
		if ops[i] == "put" {
			c.Put(args[i][0], args[i][1])
			out = append(out, "null")
		} else {
			out = append(out, strconv.Itoa(c.Get(args[i][0])))
		}
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := []struct {
		ops  []string
		args [][]int
	}{
		{[]string{"LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"},
			[][]int{{2}, {1, 1}, {2, 2}, {1}, {3, 3}, {2}, {4, 4}, {1}, {3}, {4}}},
		{[]string{"LRUCache", "put", "get", "put", "get", "get"},
			[][]int{{1}, {2, 1}, {2}, {3, 2}, {2}, {3}}},
		{[]string{"LRUCache", "put", "put", "put", "put", "get", "get", "get"},
			[][]int{{2}, {1, 1}, {2, 2}, {1, 10}, {3, 3}, {1}, {2}, {3}}},
	}
	for _, t := range tests {
		lru := Constructor(t.args[0][0])
		fmt.Println("brute:", run(&LRUCacheBrute{cap: t.args[0][0]}, t.ops, t.args))
		fmt.Println("dll  :", run(&lru, t.ops, t.args))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Library variant: container/list (doubly linked) with MoveToFront,
 *   PushFront, Back and Remove, plus map[int]*list.Element.
 * - slices.Delete(s, i, i+1) removes one element; slices.DeleteFunc removes
 *   all matches (Go 1.21+).
 * - Struct fields of the same type can share a line: prev, next *node.
 * - Comma-ok `n, ok := m[key]` separates "missing" from a stored value.
 */
