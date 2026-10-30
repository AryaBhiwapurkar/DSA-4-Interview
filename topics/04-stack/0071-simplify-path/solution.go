/*
 * 0071. Simplify Path  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/simplify-path/
 *
 * Problem: Turn an absolute Unix path into canonical form: single slashes,
 *          no trailing slash, "." and ".." resolved ("..." is a name).
 *
 * Examples:
 *   "/home/"                             -> "/home"
 *   "/home//foo/"                        -> "/home/foo"
 *   "/home/user/Documents/../Pictures"   -> "/home/user/Pictures"
 *   "/../"                               -> "/"
 *   "/.../a/../b/c/../d/./"              -> "/.../b/d"
 *   "/a/./b/../../c/"                    -> "/c"
 *   "/"                                  -> "/"
 *
 * Approaches:
 *   1. Split + stack  ⭐   O(n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"strings"
)

// ---------- Approach 1: Split + Stack ⭐ ----------
func simplifyPath(path string) string {
	st := []string{}
	for _, part := range strings.Split(path, "/") { // "" between repeated slashes
		switch part {
		case "", ".":
		case "..":
			if len(st) > 0 { // ".." at root is a no-op
				st = st[:len(st)-1]
			}
		default:
			st = append(st, part)
		}
	}
	return "/" + strings.Join(st, "/") // empty stack gives "/"
}

// ---------- Driver ----------
func main() {
	tests := []string{"/home/", "/home//foo/", "/home/user/Documents/../Pictures", "/../",
		"/.../a/../b/c/../d/./", "/a/./b/../../c/", "/"}
	for _, p := range tests {
		fmt.Printf("stack: %q\n", simplifyPath(p))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - strings.Split keeps empty parts; strings.FieldsFunc would drop them.
 * - A switch case can list several values (case "", ".":) and can be empty;
 *   Go cases never fall through by default.
 * - %q prints a string with quotes and escapes.
 */
