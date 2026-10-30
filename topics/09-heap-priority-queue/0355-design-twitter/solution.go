/*
 * 0355. Design Twitter  |  Medium  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/design-twitter/
 *
 * Problem: postTweet, getNewsFeed (10 most recent from self + followees),
 *          follow, unfollow.
 *
 * Examples:
 *   post(1,5), feed(1), follow(1,2), post(2,6), feed(1), unfollow(1,2), feed(1)
 *     -> [null,null,[5],null,null,[6,5],null,[5]]
 *   post(1,1)..post(1,11), feed(1), unfollow(1,3)   (more than 10; unfollow a stranger)
 *     -> [null x11, [11,10,9,8,7,6,5,4,3,2], null]
 *
 * Approaches:
 *   1. Global tweet list, scan newest first     O(total tweets) per feed
 *   2. Per-user lists + heap merge  ⭐           O(F log F + 10 log F) per feed   <- go-to
 */

package main

import (
	"container/heap"
	"fmt"
	"strconv"
	"strings"
)

// ---------- Approach 1: Global Tweet List ----------
type TwitterScan struct {
	tweets  [][2]int // {user, tweetId} in time order
	follows map[int]map[int]bool
}

func newTwitterScan() *TwitterScan { return &TwitterScan{follows: map[int]map[int]bool{}} }

func (t *TwitterScan) PostTweet(u, id int) { t.tweets = append(t.tweets, [2]int{u, id}) }
func (t *TwitterScan) GetNewsFeed(u int) []int {
	res := []int{}
	for i := len(t.tweets) - 1; i >= 0 && len(res) < 10; i-- {
		author := t.tweets[i][0]
		if author == u || t.follows[u][author] {
			res = append(res, t.tweets[i][1])
		}
	}
	return res
}
func (t *TwitterScan) Follow(a, b int) {
	if a == b {
		return
	}
	if t.follows[a] == nil {
		t.follows[a] = map[int]bool{}
	}
	t.follows[a][b] = true
}
func (t *TwitterScan) Unfollow(a, b int) { delete(t.follows[a], b) }

// ---------- Approach 2: Per-User Lists + Heap Merge ⭐ ----------
type tweet struct{ time, id int }
type cursor struct{ time, user, idx int }
type cursorHeap []cursor

func (h cursorHeap) Len() int           { return len(h) }
func (h cursorHeap) Less(i, j int) bool { return h[i].time > h[j].time } // newest on top
func (h cursorHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *cursorHeap) Push(x any)        { *h = append(*h, x.(cursor)) }
func (h *cursorHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

type Twitter struct {
	clock   int // global time: tweet ids aren't ordered
	tweets  map[int][]tweet
	follows map[int]map[int]bool
}

func Constructor() Twitter {
	return Twitter{tweets: map[int][]tweet{}, follows: map[int]map[int]bool{}}
}

func (t *Twitter) PostTweet(u, id int) {
	t.tweets[u] = append(t.tweets[u], tweet{t.clock, id})
	t.clock++
}

func (t *Twitter) GetNewsFeed(u int) []int {
	h := &cursorHeap{}
	seed := func(v int) {
		if ts := t.tweets[v]; len(ts) > 0 {
			*h = append(*h, cursor{ts[len(ts)-1].time, v, len(ts) - 1})
		}
	}
	seed(u) // own tweets count too
	for v := range t.follows[u] {
		seed(v)
	}
	heap.Init(h)
	res := []int{}
	for h.Len() > 0 && len(res) < 10 {
		c := heap.Pop(h).(cursor)
		res = append(res, t.tweets[c.user][c.idx].id)
		if c.idx > 0 { // that user's next newest
			prev := t.tweets[c.user][c.idx-1]
			heap.Push(h, cursor{prev.time, c.user, c.idx - 1})
		}
	}
	return res
}

func (t *Twitter) Follow(a, b int) {
	if a == b {
		return
	}
	if t.follows[a] == nil {
		t.follows[a] = map[int]bool{}
	}
	t.follows[a][b] = true
}

func (t *Twitter) Unfollow(a, b int) { delete(t.follows[a], b) }

// ---------- Driver ----------
type twitterer interface {
	PostTweet(u, id int)
	GetNewsFeed(u int) []int
	Follow(a, b int)
	Unfollow(a, b int)
}

func run(tw twitterer, ops []string, args [][]int) string {
	out := []string{"null"}
	for i := 1; i < len(ops); i++ {
		a := args[i]
		switch ops[i] {
		case "postTweet":
			tw.PostTweet(a[0], a[1])
			out = append(out, "null")
		case "follow":
			tw.Follow(a[0], a[1])
			out = append(out, "null")
		case "unfollow":
			tw.Unfollow(a[0], a[1])
			out = append(out, "null")
		default:
			f := tw.GetNewsFeed(a[0])
			parts := make([]string, len(f))
			for j, x := range f {
				parts[j] = strconv.Itoa(x)
			}
			out = append(out, "["+strings.Join(parts, ",")+"]")
		}
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	ops2, args2 := []string{"Twitter"}, [][]int{{}}
	for t := 1; t <= 11; t++ {
		ops2, args2 = append(ops2, "postTweet"), append(args2, []int{1, t})
	}
	ops2, args2 = append(ops2, "getNewsFeed", "unfollow"), append(args2, []int{1}, []int{1, 3})
	tests := []struct {
		ops  []string
		args [][]int
	}{
		{[]string{"Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"},
			[][]int{{}, {1, 5}, {1}, {1, 2}, {2, 6}, {1}, {1, 2}, {1}}},
		{ops2, args2},
	}
	for _, tc := range tests {
		tw := Constructor()
		fmt.Println("scan:", run(newTwitterScan(), tc.ops, tc.args))
		fmt.Println("heap:", run(&tw, tc.ops, tc.args))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Reading a missing key of a nested map (t.follows[u][author]) is safe:
 *   nil map reads return the zero value. Writes need the inner map created.
 * - delete on a nil or missing key is a no-op.
 */
