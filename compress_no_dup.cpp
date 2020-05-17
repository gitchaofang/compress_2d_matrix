#include<iostream>
#include<vector>
#include<unordered_map>
#include<utility>
#include<queue>
#include<algorithm>
void compress(std::vector<std::vector<int>>& v){
    int n = v.size();
    int m = v[0].size();
    std::vector<std::vector<std::pair<int,int>>> w(n,std::vector<std::pair<int,int>>(m));
    int k = 0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j) w[i][j] = {v[i][j],k++};
    }
    std::unordered_map<int,std::vector<int>> connect;
    
    std::vector<int> in(n*m,0);
    auto cmp = [](const std::pair<int,int>& p1, const std::pair<int,int>& p2){
        return p1.first < p2.first;
    };

    /*build connection from row*/
    for(int i = 0; i < n; ++i){
        std::vector<std::pair<int,int>> tv = w[i];
        std::sort(tv.begin(), tv.end(),cmp);
        for(int j=0; j<m - 1; ++j){
            connect[tv[j].second].push_back(tv[j + 1].second);
            ++in[tv[j+1].second];
        }
    }
    /*build connection from column*/ 
    for(int j = 0; j < m; ++j){
        std::vector<std::pair<int,int>> tv(n);
        for(int i = 0; i < n; ++i) tv[i] = w[i][j];
        std::sort(tv.begin(), tv.end(),cmp);
        for(int i = 0; i < n - 1; ++i){
            connect[tv[i].second].push_back(tv[i + 1].second);
            ++in[tv[i+1].second];
        }
    }

    
    k = 1;
    std::queue<int> q;
    for(int i=0; i<n*m; ++i){
        if(in[i] == 0) q.push(i);
    }
    while(!q.empty()){
        int len = q.size();
        for(int j=0; j<len; ++j){
            int cur = q.front();
            q.pop();
            in[cur] = -k;
            for(const int& nb: connect[cur]){
                --in[nb];
                if(in[nb] == 0) q.push(nb);
            }
        }
        ++k;
    }

    k = 0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            v[i][j] = -in[k++];
        }
    }
    
    return;
}

