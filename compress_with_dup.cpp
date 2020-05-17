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
    
    std::vector<std::pair<int,int>> val(n*m);    

    /*build connection from row*/
    for(int i = 0; i < n; ++i){
        std::vector<std::pair<int,int>> tv = w[i];
        std::sort(tv.begin(), tv.end(),cmp);
        for(int j=0; j<m - 1; ++j){
            val[i * m + j] = {v[i][j],1};
            connect[tv[j].second].push_back(tv[j + 1].second);
            ++in[tv[j+1].second];
        }
         val[i * m + m - 1] = {v[i].back(),1};
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

    
    std::queue<int> q;
    for(int i=0; i<n*m; ++i){
        if(in[i] == 0) q.push(i);
    }
    while(!q.empty()){
        int len = q.size();
        for(int j=0; j<len; ++j){
            int cur = q.front();
            q.pop();
            in[cur] = -val[cur].second;
            for(const int& nb: connect[cur]){
                --in[nb];
                if(val[cur].first != val[nb].first) val[nb].second = val[cur].second + 1;
                else val[nb].second = val[cur].second;
                if(in[nb] == 0) q.push(nb);
            }
        }
    }

    
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            v[i][j] = -in[i * m + j];
        }
    }
    
    return;
}

int main(){
    std::vector<std::vector<int>> v({{20,80,60,70},{11,90,22,44},{33,99,49,88}});
 //   std::vector<std::vector<int>> v({{25,74,54},{12,56,83}});
    compress(v);
    for(int i=0; i<v.size(); ++i){
        for(int j=0; j<v[0].size(); ++j){
            std::cout << v[i][j] << " ";
        }
        std::cout  << '\n';
    }
    return 0;
}
 


