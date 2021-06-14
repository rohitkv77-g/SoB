#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll block = 4000000;

map<string, int> txId;
vector<ll> fee, weight;
vector<vector<int>> par;

string trim(string st){
    while(st.back()==' ')
        st.pop_back();

    reverse(st.begin(), st.end());

    while(st.back()==' ')
        st.pop_back();

    reverse(st.begin(), st.end());
    return st;
}

vector<string> split(string st, string tok){
    vector<string> parts;
        
    int start=0;
    int end=st.find(tok);

    while(end!=-1){
        parts.push_back(st.substr(start, end-start));
        start=end+1;
        end=st.find(tok, start);
    }

    parts.push_back(st.substr(start));

    return parts;
}

void input(){
    string st;
    int id=0;

    cin>>st;

    while(cin>>st){

        vector<string> parts = split(st, ",");

        for(int la=0;la<parts.size();la++)
            parts[la]=trim(parts[la]);

        vector<string> parent;
        if(parts.size()==4){
            parent = split(parts[3], ";");
        }

        txId[parts[0]]=id;
        fee.push_back(stoi(parts[1]));
        weight.push_back(stoi(parts[2]));


        vector<int> p;
        for(auto it: parent){
            string s=trim(it);
            if(s.empty())
                break;
            p.push_back(txId[it]);
        }

        par.push_back(p);

        id++;
    }
}

int main(int arg, char *args[]) {
    if(arg<=1){
        cout<<"No input file"<<endl;
        return 0;
    }
    freopen(args[1], "r", stdin);

    input();

    int n=fee.size();
    // for(int la=0;la<n;la++){
    //     cout<<la<<' '<<fee[la]<<' '<<weight[la]<<' ';
    //     for(auto it: par[la])
    //         cout<<it<<' ';
    //     cout<<endl;
    // }

    priority_queue<pair<double, int>> q;
    vector<bool> txTaken(n, false);

    int la, lb;

    auto find_wt_fee = [&](int idx){
        double f=0, w=0;

        if(!txTaken[idx]){
            f+=fee[idx];
            w+=weight[idx];
        }

        for(auto it: par[idx]){
            if(!txTaken[it]){
                f+=fee[it];
                w+=weight[it];
            }
        }

        return make_pair(f, w);
    };

    for(la=0;la<n;la++){
        pair<double, double> data = find_wt_fee(la);
        q.push({data.first/data.second, la});
    }

    ll left = block, totfee=0;

    while(!q.empty()){
        auto d = q.top();   q.pop();
        // cout<<d.first<<' '<<d.second<<endl;
        int tx = d.second;
        pair<double, double> data = find_wt_fee(tx);
        double f=data.first, w=data.second;

        // if(f/w < d.second)
        //     continue;

        if(w<=left){
            left-=w;
            totfee+=f;
            txTaken[tx]=true;
            for(auto it: par[tx]){
                txTaken[it]=true;
            }
        }
    }

    vector<string> validTx;

    for(auto it: txId){
        if(txTaken[it.second])
            validTx.push_back(it.first);
    }

    sort(validTx.begin(), validTx.end(), [](string &a, string &b){
        return txId[a]<txId[b];
    });

    for(auto it: validTx)
        cout<<it<<endl;

    return 0;
}