/*
 * 0173. Binary Search Tree Iterator  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/binary-search-tree-iterator/
 *
 * Problem: Iterator over a BST in ascending order: next() and hasNext(),
 *          O(1) average time and O(h) memory.
 *
 * Examples:
 *   [7,3,15,null,null,9,20]: next, next, hasNext, next, hasNext, next, hasNext, next, hasNext
 *     -> [null,3,7,true,9,true,15,true,20,false]
 *   [1]: hasNext, next, hasNext
 *     -> [null,true,1,false]
 *
 * Approaches:
 *   1. Flatten to an array      O(n) init, O(1) next, O(n) space
 *   2. Controlled stack  ⭐      O(1) amortized next, O(h) space   <- go-to
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

// ---------- Approach 1: Flatten to an Array ----------
type BSTIteratorArray struct {
	vals []int
	i    int
}

func newBSTIteratorArray(root *TreeNode) *BSTIteratorArray {
	it := &BSTIteratorArray{}
	var inorder func(n *TreeNode)
	inorder = func(n *TreeNode) {
		if n == nil {
			return
		}
		inorder(n.Left)
		it.vals = append(it.vals, n.Val)
		inorder(n.Right)
	}
	inorder(root)
	return it
}

func (it *BSTIteratorArray) Next() int     { it.i++; return it.vals[it.i-1] }
func (it *BSTIteratorArray) HasNext() bool { return it.i < len(it.vals) }

// ---------- Approach 2: Controlled Stack ⭐ ----------
type BSTIterator struct{ st []*TreeNode } // pending left spine: at most h nodes

func Constructor(root *TreeNode) BSTIterator {
	it := BSTIterator{}
	it.pushLeft(root)
	return it
}

func (it *BSTIterator) pushLeft(n *TreeNode) {
	for ; n != nil; n = n.Left {
		it.st = append(it.st, n)
	}
}

func (it *BSTIterator) Next() int {
	n := it.st[len(it.st)-1]
	it.st = it.st[:len(it.st)-1]
	it.pushLeft(n.Right) // successor lives in the right subtree's left spine
	return n.Val
}

func (it *BSTIterator) HasNext() bool { return len(it.st) > 0 }

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

type iterator interface {
	Next() int
	HasNext() bool
}

func run(it iterator, ops []string) string {
	out := []string{"null"}
	for _, op := range ops[1:] {
		if op == "next" {
			out = append(out, strconv.Itoa(it.Next()))
		} else {
			out = append(out, strconv.FormatBool(it.HasNext()))
		}
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := []struct {
		tree []int
		ops  []string
	}{
		{[]int{7, 3, 15, null, null, 9, 20},
			[]string{"BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"}},
		{[]int{1}, []string{"BSTIterator", "hasNext", "next", "hasNext"}},
	}
	for _, t := range tests {
		st := Constructor(build(t.tree))
		fmt.Println("array:", run(newBSTIteratorArray(build(t.tree)), t.ops))
		fmt.Println("stack:", run(&st, t.ops))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - LeetCode's Go template uses Constructor() returning a value and
 *   pointer-receiver Next/HasNext methods; pass &st to the interface.
 * - strconv.FormatBool prints true/false.
 */
