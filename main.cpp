#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left, *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Global structures to store depth and parent info
unordered_map<int, int> depthMap;   // node value -> depth
unordered_map<int, int> parentMap;  // node value -> parent value (or -1 for root)

// Recursive builder using preorder sequence with -1 as null marker
Node* build(const vector<int>& pre, size_t& idx, int curDepth, int parentVal) {
    if (idx >= pre.size()) return nullptr;
    int v = pre[idx++];
    if (v == -1) return nullptr;
    // Record depth and parent
    depthMap[v] = curDepth;
    parentMap[v] = parentVal;
    Node* node = new Node(v);
    node->left = build(pre, idx, curDepth + 1, v);
    node->right = build(pre, idx, curDepth + 1, v);
    return node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    if (!(cin >> Q)) return 0;
    vector<pair<int,int>> queries(Q);
    for (int i = 0; i < Q; ++i) {
        int x, y;
        cin >> x >> y;
        queries[i] = {x, y};
    }
    // Read remaining integers as preorder traversal
    vector<int> preorder;
    int val;
    while (cin >> val) {
        preorder.push_back(val);
    }
    size_t idx = 0;
    Node* root = build(preorder, idx, 0, -1);
    // Answer queries
    for (auto &q : queries) {
        int x = q.first, y = q.second;
        if (depthMap.find(x) == depthMap.end() || depthMap.find(y) == depthMap.end()) {
            cout << 0 << '\n';
            continue;
        }
        if (depthMap[x] == depthMap[y] && parentMap[x] != parentMap[y])
            cout << 1 << '\n';
        else
            cout << 0 << '\n';
    }
    return 0;
}

