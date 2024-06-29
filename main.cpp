#include<bits/stdc++.h>
using namespace std;
typedef long double ld;

vector<ld> PageRank(unordered_map<ld, vector<int>> &links,vector<int> val, unordered_map<int,int> &ind,vector<int> &idx) {
    ld a = 0.85;
    ld maxerror = 1e-5; 
    int n = idx.size();

    vector<ld> I(n, 1.0 / n);

    while (true) {
        vector<ld> Iplus(n, ((1.0 - a) / n));

        for (const auto& link : links){
            ld from = link.first;
            for (ld to : link.second){
                Iplus[ind[to]] += a * I[ind[from]] / val[from];
            }
        }
        ld count = 0;
        for(int i = 0; i < n; i++){
            if(val[idx[i]] == 0){
                count+=I[i];
            }
        }
        for(int i = 0; i < n; i++){
            Iplus[i] += a * count / n;
        }
        bool converged = true;
        for (int i = 0; i < n; ++i) {
            if (abs(Iplus[i] - I[i]) > maxerror) {
                converged = false;
                break;
            }
        }
        if (converged) {
            break;
        }
        I = move(Iplus);
    }
    return I;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int p, q;

    unordered_map<ld, vector<int>> links;
    vector<int> v(1e6 +1,-1);
    vector<int> idx;

    while (cin >>p>>q){
        if(v[p] == -1) v[p]++;
        links[p].push_back(q);
        v[p]++;
        if(v[q] == -1) v[q] = 0;
    }
    unordered_map<int,int> ind;

    for(int i = 0; i < 1e6; i++){
        if(v[i] != -1){
            ind[i] = idx.size();
            idx.push_back(i);
        }
    }
    
    vector<ld> Ranks = PageRank(links,v,ind,idx);
    ld Tprob = 0.0;

    for(int i = 0; i < idx.size(); i++){
        cout<<idx[i] << " = " << fixed << setprecision(5) << Ranks[i] << endl;

        Tprob+=Ranks[i];
    }

    cout<<"s = " << fixed << setprecision(1) << Tprob << endl;
    return 0;
}