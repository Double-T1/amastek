/* 
主程式呼叫 main 開始， main 在最底部

思考邏輯
T: test case numbers
N: actions per test case
R: row count
C: column count
Sr: current row
Sc: current column

brute force:
每個案例都建立完整個網格，並模擬所有過程
time complexity: O(T*(R*C + N*max(R,C)))
space complexity: O(R*C)

optimization:
1. 不需要建立實際網格，紀錄現在網格位置就好了。也不需擔心超出邊界，因為題目確保此情形不會發生。
=> 節省空間與時間
2. 避免反覆走過一樣的格子，利用 disjointed union set 的 path compression 壓縮 parent 指針的辦法，縮減外連的格子。
=> max(R,C) 節省為 max(logR, logC)
3. lazy evaluation，需要時再創建相關網格。
=> 同時將已建立的格子用 map 記錄下來，查詢和插入時間皆為 logn
=> 用 hashmap 應該可以再節省時間
time complexity: O(T*N*max(logR,logC)*logN)
space complexity: O(N)

執行大綱：
- 用 class Grid 代表網格格子，將關於格子的計算（往東南西北），以及其相鄰網格狀態，封裝在其中。
- main 每個 test case 呼叫 solve 一次。
- solve 根據每個指令（往東南西北），更新一次所在格子的狀態，並找尋下一個格子。
*/

#include <iostream>
#include <string>
#include <map>
#include <array>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

// a class that represents the grids on the board
// also, 0 rep N, 1 rep S, 2 rep E, 3 rep W
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
    
    // update the status of the current grid
    Grid* update(char step, map<pii, Grid*>& allGrids) {
        int index = this->getIndex(step);
        this->taken = true;
        return this->findNext(index,allGrids);
    }
    
    // find the next valid grid
    Grid* findNext(int index, map<pii, Grid*>& allGrids) {
        if (!this->taken) {
            return this;
        }
        // if the next grid of this direction(index) isn't registered
        // see if it is registered elsewhere
        if (this->adj[index] == nullptr) {
            pii newP = this->generateNext(index);
            // check if the next grid is traversed by other direction(index) before
            if (allGrids.find(newP) == allGrids.end()) {
                allGrids[newP] = new Grid(newP.first, newP.second);
            }
            // update to point to the next grid
            this->adj[index] = allGrids[newP];
        }
        
        Grid* next = this->adj[index];
        return this->adj[index] = next->findNext(index, allGrids);
    }
    
private:
    pii generateNext(int index) {
        auto[rd, rc] = this->dir[index];
        return {row+rd, col+rc};
    }
};

// for clearing memory space after every test case
void clearAll(map<pii, Grid*>& allGrids) {
    for (auto[p, g]: allGrids) {
        delete g;
    }
    return;
}

// general function for each test case
// includes intaking relevant variables, setting up necessary objects
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

// the invoked function for the whole program
// takes in the tests cases, and prints out the result
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

