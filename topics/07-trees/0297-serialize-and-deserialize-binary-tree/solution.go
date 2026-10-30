/*
 * 0297. Serialize and Deserialize Binary Tree  |  Hard  |  Trees
 * Link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 *
 * Problem: Encode a binary tree to a string and decode it back exactly.
 *
 * Examples (round trip shown in level order, plus each codec's encoding):
 *   [1,2,3,null,null,4,5]  -> [1,2,3,null,null,4,5]
 *   []                     -> []
 *   [1]                    -> [1]
 *   [1,-2,3,null,40]       -> [1,-2,3,null,40]   (negative, multi-digit)
 *
 * Approaches:
 *   1. Preorder with null markers  ⭐   O(n) time, O(n) space   <- go-to
 *   2. BFS level order with markers    O(n) time, O(n) space
 */

package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

type TreeNode struct {
	Val         int
	Left, Right *TreeNode
}

// ---------- Approach 1: Preorder With Null Markers ⭐ ----------
type Codec struct{}

func (c *Codec) serialize(root *TreeNode) string {
	out := []string{}
	var enc func(n *TreeNode)
	enc = func(n *TreeNode) {
		if n == nil {
			out = append(out, "#") // null marker fixes the shape
			return
		}
		out = append(out, strconv.Itoa(n.Val))
		enc(n.Left)
		enc(n.Right)
	}
	enc(root)
	return strings.Join(out, ",") // delimiter: "12" vs "1","2"
}

func (c *Codec) deserialize(data string) *TreeNode {
	t := strings.Split(data, ",")
	i := 0 // local index: codec stays stateless
	var dec func() *TreeNode
	dec = func() *TreeNode {
		tok := t[i]
		i++
		if tok == "#" {
			return nil
		}
		v, _ := strconv.Atoi(tok)
		n := &TreeNode{Val: v}
		n.Left = dec() // same order as encoding: left, then right
		n.Right = dec()
		return n
	}
	return dec()
}

// ---------- Approach 2: BFS Level Order With Markers ----------
type CodecBFS struct{}

func (c *CodecBFS) serialize(root *TreeNode) string {
	out := []string{}
	q := []*TreeNode{root}
	for len(q) > 0 {
		n := q[0]
		q = q[1:]
		if n == nil {
			out = append(out, "#")
			continue
		}
		out = append(out, strconv.Itoa(n.Val))
		q = append(q, n.Left, n.Right)
	}
	return strings.Join(out, ",")
}

func (c *CodecBFS) deserialize(data string) *TreeNode {
	t := strings.Split(data, ",")
	if t[0] == "#" {
		return nil
	}
	v, _ := strconv.Atoi(t[0])
	root := &TreeNode{Val: v}
	q := []*TreeNode{root}
	for i := 1; i < len(t); i += 2 { // each queued node owns the next two tokens
		n := q[0]
		q = q[1:]
		if t[i] != "#" {
			x, _ := strconv.Atoi(t[i])
			n.Left = &TreeNode{Val: x}
			q = append(q, n.Left)
		}
		if t[i+1] != "#" {
			x, _ := strconv.Atoi(t[i+1])
			n.Right = &TreeNode{Val: x}
			q = append(q, n.Right)
		}
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

func main() {
	for _, v := range [][]int{{1, 2, 3, null, null, 4, 5}, {}, {1}, {1, -2, 3, null, 40}} {
		root := build(v)
		a, b := &Codec{}, &CodecBFS{}
		ea, eb := a.serialize(root), b.serialize(root)
		fmt.Printf("preorder: %s -> %s\n", ea, serialize(a.deserialize(ea)))
		fmt.Printf("bfs     : %s -> %s\n", eb, serialize(b.deserialize(eb)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Methods and package-level functions live in different namespaces, so
 *   (*Codec).serialize doesn't clash with the serialize() helper.
 * - strings.Split + strconv.Atoi parse the token stream.
 * - An empty struct type (struct{}) is a zero-size receiver.
 */
