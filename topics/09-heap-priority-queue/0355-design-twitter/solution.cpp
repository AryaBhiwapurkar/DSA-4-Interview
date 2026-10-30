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

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Global Tweet List ----------
class TwitterScan {
    vector<pair<int, int>> tweets;         // (user, tweetId) in time order
    unordered_map<int, unordered_set<int>> follows;
public:
    void postTweet(int u, int t) { tweets.push_back({u, t}); }
    vector<int> getNewsFeed(int u) {
        vector<int> res;
        for (int i = tweets.size() - 1; i >= 0 && res.size() < 10; i--) {
            auto [author, id] = tweets[i];
            if (author == u || follows[u].count(author)) res.push_back(id);
        }
        return res;
    }
    void follow(int a, int b) { if (a != b) follows[a].insert(b); }
    void unfollow(int a, int b) { follows[a].erase(b); }
};

// ---------- Approach 2: Per-User Lists + Heap Merge ⭐ ----------
class Twitter {
    int clock = 0;                         // global time: tweet ids aren't ordered
    unordered_map<int, vector<pair<int, int>>> tweets;   // user -> (time, id), oldest first
    unordered_map<int, unordered_set<int>> follows;
public:
    void postTweet(int u, int t) { tweets[u].push_back({clock++, t}); }
    vector<int> getNewsFeed(int u) {
        priority_queue<tuple<int, int, int>> pq;          // (time, user, index), newest on top
        auto seed = [&](int v) {
            auto it = tweets.find(v);
            if (it != tweets.end() && !it->second.empty())
                pq.push({it->second.back().first, v, (int)it->second.size() - 1});
        };
        seed(u);                           // own tweets count too
        for (int v : follows[u]) seed(v);
        vector<int> res;
        while (!pq.empty() && res.size() < 10) {
            auto [time, v, i] = pq.top();
            pq.pop();
            res.push_back(tweets[v][i].second);
            if (i > 0) pq.push({tweets[v][i - 1].first, v, i - 1});   // that user's next newest
        }
        return res;
    }
    void follow(int a, int b) { if (a != b) follows[a].insert(b); }
    void unfollow(int a, int b) { follows[a].erase(b); }
};

// ---------- Driver ----------
template <class T>
void run(const string& label, const vector<string>& ops, const vector<vector<int>>& args) {
    T tw;
    cout << label << ": [null";
    for (size_t i = 1; i < ops.size(); i++) {
        auto& a = args[i];
        if (ops[i] == "postTweet") { tw.postTweet(a[0], a[1]); cout << ",null"; }
        else if (ops[i] == "follow") { tw.follow(a[0], a[1]); cout << ",null"; }
        else if (ops[i] == "unfollow") { tw.unfollow(a[0], a[1]); cout << ",null"; }
        else {
            vector<int> f = tw.getNewsFeed(a[0]);
            cout << ",[";
            for (size_t j = 0; j < f.size(); j++) cout << (j ? "," : "") << f[j];
            cout << "]";
        }
    }
    cout << "]\n";
}

int main() {
    vector<string> ops2 = {"Twitter"};
    vector<vector<int>> args2 = {{}};
    for (int t = 1; t <= 11; t++) { ops2.push_back("postTweet"); args2.push_back({1, t}); }
    ops2.push_back("getNewsFeed"); args2.push_back({1});
    ops2.push_back("unfollow"); args2.push_back({1, 3});
    vector<pair<vector<string>, vector<vector<int>>>> tests = {
        {{"Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"},
         {{}, {1, 5}, {1}, {1, 2}, {2, 6}, {1}, {1, 2}, {1}}},
        {ops2, args2},
    };
    for (auto& [ops, args] : tests) {
        run<TwitterScan>("scan", ops, args);
        run<Twitter>("heap", ops, args);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - priority_queue<tuple<...>> orders lexicographically: time first.
 * - A capturing lambda (seed) reuses the "push this user's newest" step.
 * - unordered_set::erase on a missing key is a harmless no-op.
 */
