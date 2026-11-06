# Backlog: Ideas for Later

Parked ideas, not started. The current work plan is [PLAN-wave2.md](PLAN-wave2.md).

## 1. Learning path per topic ("the journey")
**Who it's for:** someone who knows a topic's basics and now wants to master its folder.
**Problem:** each topic's problem table is sorted Easy → Medium → Hard, then by number. Inside "Medium" the actual difficulty varies a lot, so number order isn't a good study order.

**Idea:** give each topic README a recommended solve order that builds confidence and then difficulty:
1. **Easy problems first**, for confidence.
2. **Mediums from genuinely easier to genuinely harder.** Problems of about the same difficulty sit together as one step, in any order.
3. **Hard problems last**, the "boss" problems of the topic.

Ordering rules:
- Prefer an order where each problem reuses an idea from the one before it (e.g. 0167 Two Sum II → 0015 3Sum → 0018 4Sum). Use `followup_of` / `related` as a guide.
- Order by real difficulty for someone learning the topic, not by LeetCode's label.

Possible shape: a `## Learning Path` section in each topic README, with numbered steps of one or more problems, each with a one-line "what this step teaches".

## 2. Spaced-repetition tracker
`progress.json` with, for each problem, the last attempt date, time taken and confidence (1–5), plus `scripts/today.py` to suggest what to revise today (weak + stale first).

## 3. Pattern-recognition drills
Quiz mode built from `cheatsheets/patterns.md` and the 30-second summaries: show a problem statement and name the pattern within 60 seconds.

## 4. Mock interview command (`/mock`)
Show only the problem and examples. Answer clarifying questions, give hints 1 → 3 only on request, ask the README's follow-ups, then review the final code.

## Dropped / not needed
- **Own test runner:** use LeetCode (or another judge) directly instead; every problem folder has its LeetCode link.
- **CI that runs all solutions on push:** not needed for now.
