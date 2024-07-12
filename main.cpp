#include "Hyd_graph.hpp"
#define ll long long int
#define INF INT_MAX
#define pp pair<int,int>
using namespace std;

map<int,int> mp;
vector<int> dijk(int src){

    vector<int> via(total_stations);
    priority_queue<pp,vector<pp>, greater<pp>> pq;
    mp.clear();
    set<int> vis;

    for(int i=0; i<total_stations; i++){
        mp[i]= INF;
        via[i]= i;
    }
    mp[src]= 0;
    pq.push({0,src});

    while(!pq.empty()){
        auto curr= pq.top();
        pq.pop();

        if(vis.count(curr.second)) continue;
        vis.insert(curr.second);

        for(int i= 0; i < total_stations; i++){
            if(graph[curr.second][i] == 1 and !vis.count(i) and mp[i] > curr.first + 1){
                int newDist= curr.first + 1;
                mp[i]= newDist;
                pq.push({newDist,i});
                via[i]= curr.second;
            }
        }
    }

    return via;
}

int main(){
    map_code();
    while(true){
        cout<<"\n";
        cout<<"\t\t\t ~ ~ ~ MENU ~ ~ ~\n\n";
        cout<<"1. View list of Stations in Map\n";
        cout<<"2. Get shortest distance from Source station to Destination station\n";
        cout<<"3. Get shortest route from Source station to Destination station\n";
        cout<<"4. Exit Menu\n";
        cout<<"\n";
        int choice;
        cout<<"Enter your choice from above Menu:\n  -->";
        cin>>choice;
        cout<<"\n";
        if(choice == 1){
            for(int i=0; i<total_stations; i +=4){
                cout<<i+1<<". "<<stations[i]<<"\t "<<i+2<<". "<<stations[i+1]<<"\t "<<i+3<<". "<<stations[i+2]<<"\t "<<i+4<<". "<<stations[i+3]<<"\n";
            }
            cout<<"\n";
        }
        else if(choice == 2){
            string ssrc, sdst;
            cout<<"Enter Source Station:\n";
            cin>>ssrc;
            cout<<"\n";
            cout<<"Enter Destination Station:\n";
            cin>>sdst;
            cout<<"\n";
            if(!code.count(ssrc) or !code.count(sdst)){
                choice= 0;
                cout<<"!! stations doesn't exist !!"<<endl;
                continue;
            }

            int src, dst;
            src= code[ssrc];
            dst= code[sdst];

            dijk(src);
            cout<<"** Shortest Distance from "<<ssrc<<" to "<<sdst<<" is "<<mp[dst]<<" units **\n";
            cout<<"\n";
        }
        else if(choice == 3){

            string ssrc, sdst;
            cout<<"Enter Source Station:\n";
            cin>>ssrc;
            cout<<"\n";
            cout<<"Enter Destination Station:\n";
            cin>>sdst;
            cout<<"\n";
            if(!code.count(ssrc) or !code.count(sdst)){
                choice= 0;
                cout<<"!! stations doesn't exist !!"<<endl;
                continue;
            }

            int src, dst;
            src= code[ssrc];
            dst= code[sdst];

            
            vector<int> route= dijk(src);
            stack<string> st;

            int ptr= dst;
            while(ptr >= 0 and ptr < total_stations and ptr != route[ptr]){
                st.push(stations[route[ptr]]);
                ptr= route[ptr];
            }

            cout<<"~~ Path  :\n\n";
            while(st.size()){
                cout<<st.top()<<" --> ";
                st.pop();
            }
            cout<<sdst<<endl;
            cout<<"\n";
        }
        else{ 
            cout<<"** exited ** \n";
            break;
        }
    }

    return 0;
}