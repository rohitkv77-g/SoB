#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
        id++;
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
    }

    // for(int la=0;la<fee.size();la++){
    //     cout<<la+1<<' '<<fee[la]<<' '<<weight[la]<<' ';
    //     for(auto it: par[la])
    //         cout<<it<<' ';
    //     cout<<endl;
    // }
}

int main(int arg, char *args[]) {
    if(arg<=1){
        cout<<"No input file"<<endl;
        return 0;
    }
    freopen(args[1], "r", stdin);

    input();



    return 0;
}