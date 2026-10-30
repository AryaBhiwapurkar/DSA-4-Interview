/*
 * 0117. Populating Next Right Pointers in Each Node II  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
 *
 * Problem: Point each node's next to its right neighbour on the same level
 *          (nil at the end). Any binary tree.
 *
 * Examples (output: each level via next pointers, # ends a level):
 *   [1,2,3,4,5,null,7]     -> [1,#,2,3,#,4,5,7,#]
 *   []                     -> []
 *   [1,2,3,4,null,null,5]  -> [1,#,2,3,#,4,5,#]
 *
 * Approaches:
 *   1. BFS queue                  O(n) time, O(w) space
 *   2. Dummy-node level linking ⭐ O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

type Node struct {
	Val               int
	Left, Right, Next *Node
}

type TreeNode = Node // alias: the shared level-order builder creates Nodes

// ---------- Approach 1: BFS Queue ----------
func connectBFS(root *Node) *Node {
	q := []*Node{}
	if root != nil {
		q = append(q, root)
	}
	for len(q) > 0 {
		sz := len(q)
		for i := 0; i < sz; i++ {
			n := q[0]
			q = q[1:]
			if i < sz-1 { // not across levels
				n.Next = q[0]
			}
			if n.Left != nil {
				q = append(q, n.Left)
			}
			if n.Right != nil {
				q = append(q, n.Right)
			}
		}
	}
	return root
}

// ---------- Approach 2: Dummy-Node Level Linking ⭐ ----------
func connect(root *Node) *Node {
	cur := root // walks the current (already linked) level
	for cur != nil {
		dummy := &Node{}
		tail := dummy // builds the next level's chain
		for ; cur != nil; cur = cur.Next {
			if cur.Left != nil {
				tail.Next = cur.Left
				tail = tail.Next
			}
			if cur.Right != nil {
				tail.Next = cur.Right
				tail = tail.Next
			}
		}
		cur = dummy.Next // first node of the next level
	}
	return root
}

// ---------- Driver ----------
const null = math.MinInt // marks a missing node in level-order input

func build(vals []int) *TreeNode { // LeetCode level order
	if len(vals) == 0 || vals[0] == null {
		return nil
	}
	root := &TreeNode{Val: vals[0]}
	q := []*TreeNode{root}
	for i := 1; i < len(vals); i += 2 {
		n := q[0]
		q = q[1:]
		if vals[i] != null {
			n.Left = &TreeNode{Val: vals[i]}
			q = append(q, n.Left)
		}
		if i+1 < len(vals) && vals[i+1] != null {
			n.Right = &TreeNode{Val: vals[i+1]}
			q = append(q, n.Right)
		}
	}
	return root
}

func serialize(root *TreeNode) string { // level order, trailing nulls trimmed
	out := []string{}
	q := []*TreeNode{root}
	for len(q) > 0 {
		n := q[0]
		q = q[1:]
		if n == nil {
			out = append(out, "null")
			continue
		}
		out = append(out, strconv.Itoa(n.Val))
		q = append(q, n.Left, n.Right)
	}
	for len(out) > 0 && out[len(out)-1] == "null" {
		out = out[:len(out)-1]
	}
	return "[" + strings.Join(out, ",") + "]"
}

func levels(root *Node) string { // follow next pointers level by level
	out := []string{}
	for start := root; start != nil; {
		var nxt *Node
		for p := start; p != nil; p = p.Next {
			out = append(out, strconv.Itoa(p.Val))
			if nxt == nil {
				if p.Left != nil {
					nxt = p.Left
				} else {
					nxt = p.Right
				}
			}
		}
		out = append(out, "#")
		start = nxt
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	for _, v := range [][]int{{1, 2, 3, 4, 5, null, 7}, {}, {1, 2, 3, 4, null, null, 5}} {
		fmt.Println("bfs  :", levels(connectBFS(build(v))))
		fmt.Println("dummy:", levels(connect(build(v))))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - `type TreeNode = Node` is an alias (same type), not a new type.
 * - `for start := root; start != nil; {` is a for loop with no post statement.
 */
