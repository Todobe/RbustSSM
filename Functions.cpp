#include "Graph.h"
#include "Functions.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

double calcFunction(Graph *G, const vector<int> &sigma){
    double ans=0;
    for(int i=0;i<sigma.size();i++){
        double cnt=1;
        for(int j=0;j<=i;j++){
            pair<int,int> tmpe=make_pair(sigma[j],sigma[i]);
            if(G->Weight.find(tmpe)!=G->Weight.end()){
                cnt*=1-G->Weight[tmpe];
            }
        }
        ans += 1-cnt;
    }
    return ans;
}

double calcFunction(Graph *G, pair<int, int> edge, const vector<int>& sigma){
    for(int i=0;i<sigma.size();i++){
        if(edge.second!=sigma[i]) continue;
        double cnt1=1, cnt2=1;
        for(int j=0;j<=i;j++){
            pair<int,int> tmpe=make_pair(sigma[j],sigma[i]);
            if(G->Weight.find(tmpe)!=G->Weight.end()){
                cnt1*=1-G->Weight[tmpe];
            }
        }
        cnt2=cnt1*(1-G->Weight[edge]);
        return cnt1-cnt2;
    }
    return G->Weight[edge];
}

void RoseNetAlgorithm(Graph *G, vector<int> &sigma, const vector<int> realSigma, int tau, int g,int k){
    //RoseNet Algorithm
    vector<int> sigma1, sigma2;
    vector<int> given;
    for(int i=0;i<g;i++){
        given.push_back(realSigma[i]);
//        if(sigma1.size()<tau){
//            sigma1.push_back(realSigma[i]);
//        }else{
//            sigma2.push_back(realSigma[i]);
//        }
    }

    while(sigma1.size() < min(tau,k-g)){
        pair<int, int> e=make_pair(-1, -1);
        double maxh=0;
        for(auto edge:G->Edges){
            //===
            if(edge.first!=edge.second && find(sigma1.begin(),sigma1.end(),edge.first)==sigma1.end()
                                          && find(given.begin(), given.end() ,edge.first)==given.end()) continue;
            //===
            if(find(given.begin(), given.end(), edge.second)!=given.end()) continue;
            if(find(sigma1.begin(), sigma1.end(), edge.second)!=sigma1.end()) continue;
            if(sigma1.size()==tau-1 && edge.first!=edge.second) continue;
            double h = calcFunction(G, edge, sigma1);
            if(h > maxh){
                maxh=h;
                e=edge;
            }
        }
        if(e.first==-1 || e.second==-1){
            break;
        }
        if(e.first==e.second || find(sigma1.begin(), sigma1.end(), e.first)!=sigma1.end()
        || find(given.begin(), given.end(), e.first)!=given.end()){
            sigma1.push_back(e.second);
        }else{
            sigma1.push_back(e.first);
            sigma1.push_back(e.second);
        }
    }
    while(sigma2.size() < k - tau -g){
        pair<int,int> e=make_pair(-1,-1);
        double maxh=0;
        for(auto edge:G->Edges){
            //====
            if(edge.first!=edge.second && find(sigma2.begin(),sigma2.end(),edge.first)==sigma2.end()
               && find(given.begin(), given.end() ,edge.first)==given.end()) continue;
            //====
            if(find(given.begin(), given.end(), edge.second)!=given.end()) continue;
            if(find(sigma1.begin(), sigma1.end(), edge.second)!=sigma1.end()) continue;
            if(find(sigma2.begin(), sigma2.end(), edge.second)!=sigma2.end()) continue;
            if(sigma2.size()==k-tau-g-1 && edge.first!=edge.second) continue;
            double h=calcFunction(G, edge, sigma2);
            if(h > maxh){
                maxh=h;
                e=edge;
            }
        }
        if(e.first==-1 || e.second==-1) {
            break;
        }
        if(e.first==e.second || find(sigma1.begin(), sigma1.end(), e.first)!=sigma1.end()
            ||find(sigma2.begin(),sigma2.end(), e.first)!=sigma2.end()
            || find(given.begin(), given.end(), e.first)!=given.end()){
            sigma2.push_back(e.second);
        }else{
            sigma2.push_back(e.first);
            sigma2.push_back(e.second);
        }
    }

    for(auto it:given) sigma.push_back(it);
    for(auto it:sigma1) sigma.push_back(it);
    for(auto it:sigma2) sigma.push_back(it);
}

void Frequency(Graph *G, vector<int> &sigma, const vector<int> realSigma, int tau, int g,int k){
    static vector<pair<double,int> > nodes;
    if(nodes.empty()){
        for(int i=0;i<G->nodeNum;i++){
            nodes.emplace_back(G->Weight[make_pair(i,i)],i);
        }
        sort(nodes.begin(),nodes.end(),greater<pair<double,int> >());
    }
    int cur=0;
    for(int i=0;i<k;i++){
        if(i<g) sigma.push_back(realSigma[i]);
        else {
            while (cur < nodes.size()) {
                if (find(sigma.begin(), sigma.end(), nodes[cur].second) == sigma.end()) {
                    sigma.push_back(nodes[cur].second);
                    cur++;
                    break;
                }
                cur++;
            }
        }
    }
}

void reorder(Graph *G, vector<int> &sigma, const vector<pair<int,int> >& edges){
    static vector<int> in=vector<int>(G->nodeNum);
    for(auto edge:edges) in[edge.first]=0,in[edge.second]=0;
    vector<int> tmp;
    for(auto edge:edges) {
        in[edge.second]++;
        if(find(tmp.begin(),tmp.end(),edge.first)==tmp.end()) tmp.push_back(edge.first);
        if(find(tmp.begin(),tmp.end(),edge.second)==tmp.end()) tmp.push_back(edge.second);
    }
    queue<int> q;
    for(auto it: tmp){
        if(in[it]==0) q.push(it);
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        sigma.push_back(cur);
        for(auto edge:edges){
            if(cur!=edge.first) continue;
            in[edge.second]--;
            if(in[edge.second]==0){
                q.push(edge.second);
            }
        }
    }
    for(auto it: tmp){
        if(find(sigma.begin(),sigma.end(),it)==sigma.end()) sigma.push_back(it);
    }
}

void OMegA(Graph *G, vector<int> &sigma, const vector<int> realSigma, int tau, int g,int k){
    vector<pair<int,int> > edges;
    for(int i=0;i<g;i++){
        sigma.push_back(realSigma[i]);
    }
    vector<int> sgm;

    while(sgm.size()<k){
        pair<int,int> e=make_pair(-1,-1);
        double maxf = 0;
        for(auto edge: G->Edges){
            //if(find(sigma.begin(),sigma.end(),edge.first)!=sigma.end()) continue;
            if(find(sigma.begin(),sigma.end(),edge.second)!=sigma.end()) continue;
            int cnt=0;
            if(find(sgm.begin(),sgm.end(),edge.first)!=sgm.end()) cnt++;
            if(find(sgm.begin(),sgm.end(),edge.second)!=sgm.end()) cnt++;
            if(sgm.size()+cnt>k) continue;
            edges.push_back(edge);
            sgm=sigma;
            reorder(G, sgm,edges);
            double f=calcFunction(G,sgm);
            if(f>maxf){
                maxf=f;
                e=edge;
            }
            edges.pop_back();
        }
        if(e.first==-1 || e.second==-1){
            break;
        }
        edges.push_back(e);
        sgm=sigma;
        reorder(G, sgm,edges);
    }
    sigma = sgm;

}