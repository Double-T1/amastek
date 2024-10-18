#include <iostream>
#include <string>
#include <map>
#include <array>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

class Grid {
private:
    static constexpr int getIndex(char step) {
        switch (step) {
            case 'N': return 0;
            case 'S': return 1;
            case 'E': return 2;
            case 'W': return 3;
            default: return -1;
        }
    }
    
    static constexpr array<pii,4> dir = {
        make_pair(-1,0),
        make_pair(1,0),
        make_pair(0,1),
        make_pair(0,-1)
    };
    
public:
    Grid* adj[4];
    int row, col;
    bool taken;
    
    Grid(int Sr, int Sc) {
        this->row = Sr;
        this->col = Sc;
        this->taken = false;
        for (int i=0; i<4; ++i) {
            this->adj[i] = nullptr;
        }
    }
    
    Grid* update(char step, map<pii, Grid*>& allGrids) {
        int index = this->getIndex(step);
        this->taken = true;
        return this->find(index,allGrids);
    }
    
    Grid* find(int index, map<pii, Grid*>& allGrids) {
        if (!this->taken) {
            return this;
        }
        if (this->adj[index] == nullptr) {
            pii newP = this->generateNext(index);
            if (allGrids.find(newP) == allGrids.end()) {
                allGrids[newP] = new Grid(newP.first, newP.second);
            }
            this->adj[index] = allGrids[newP];
        }
        
        Grid* next = this->adj[index];
        return this->adj[index] = next->find(index, allGrids);
    }
    
private:
    pii generateNext(int index) {
        auto[rd, rc] = this->dir[index];
        return {row+rd, col+rc};
    }
};

void clearAll(map<pii, Grid*>& allGrids) {
    for (auto[p, g]: allGrids) {
        delete g;
    }
    return;
}

string solve() {
    int N, R, C, Sr, Sc;
    cin >> N >> R >> C >> Sr >> Sc;
    string s;
    cin >> s;
    map<pii, Grid*> allGrids;
    Grid* cur = new Grid(Sr,Sc);
    allGrids[make_pair(Sr,Sc)] = cur;
    for (char step: s) {
        //update the old spot status and move to the new spot
        cur = cur->update(step, allGrids);
    }
    
    string ans = to_string(cur->row) + " " + to_string(cur->col);
    clearAll(allGrids);
    return ans;
}

int main() {
    int T;
    cin >> T;
    int t = 1;
    string ret = "Case #";
    while (T--) {
        string ans = solve();
        cout << ret << t << ": " << ans << '\n';
        t += 1;
    }
}

/**
brute force: O(T*(R*C+N*max(R,C)))

union find => but for four sides => update once we leave the current grid
lazy evaluation, not need to build the connection until it is queried => or else TLE and MLE
O(T*N)
*/
