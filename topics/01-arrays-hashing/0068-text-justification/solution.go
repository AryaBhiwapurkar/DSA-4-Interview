/*
 * 0068. Text Justification  |  Hard  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/text-justification/
 *
 * Problem: Greedily pack words into lines of exactly maxWidth chars and
 *          fully justify them (extra spaces go to the left gaps). The last
 *          line and single-word lines are left-justified, padded right.
 *
 * Examples:
 *   ["This","is","an","example","of","text","justification."], 16
 *     -> ["This    is    an","example  of text","justification.  "]
 *   ["What","must","be","acknowledgment","shall","be"], 16
 *     -> ["What   must   be","acknowledgment  ","shall be        "]
 *   ["Science","is","what",...,"we","do"], 20
 *     -> ["Science  is  what we","understand      well","enough to explain to",
 *         "a  computer.  Art is","everything  else  we","do                  "]
 *
 * Approaches:
 *   1. Greedy packing + space distribution  ⭐  O(N) time   <- go-to
 */

package main

import (
	"fmt"
	"strings"
)

// ---------- Approach 1: Greedy Packing + Space Distribution ⭐ ----------
func fullJustify(words []string, maxWidth int) []string {
	var res []string
	n := len(words)
	for i := 0; i < n; {
		j, letters := i, 0
		for j < n && letters+(j-i)+len(words[j]) <= maxWidth { // (j - i) separating spaces
			letters += len(words[j])
			j++
		}
		gaps := j - i - 1
		var sb strings.Builder
		if j == n || gaps == 0 { // last line or single word: left-justify
			sb.WriteString(strings.Join(words[i:j], " "))
			sb.WriteString(strings.Repeat(" ", maxWidth-sb.Len()))
		} else {
			spaces := maxWidth - letters
			sb.WriteString(words[i])
			for k := i + 1; k < j; k++ {
				g := k - i - 1 // gap index 0..gaps-1
				pad := spaces / gaps
				if g < spaces%gaps {
					pad++ // extras go left
				}
				sb.WriteString(strings.Repeat(" ", pad))
				sb.WriteString(words[k])
			}
		}
		res = append(res, sb.String())
		i = j
	}
	return res
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		words []string
		w     int
	}{
		{[]string{"This", "is", "an", "example", "of", "text", "justification."}, 16},
		{[]string{"What", "must", "be", "acknowledgment", "shall", "be"}, 16},
		{[]string{"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain",
			"to", "a", "computer.", "Art", "is", "everything", "else", "we", "do"}, 20},
	}
	for _, t := range tests {
		for _, line := range fullJustify(t.words, t.w) {
			fmt.Printf("%q\n", line)
		}
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - strings.Repeat(" ", k) builds k spaces.
 * - strings.Builder.Len() reports bytes written so far.
 * - strings.Join(words[i:j], " ") joins a sub-slice.
 */
