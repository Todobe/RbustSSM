
#include "./include/clipp.h"
#include "./graph.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace clipp;
using namespace std;


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

void RoseNetsAlgorithm(Graph *G, string task_file, string output_file, int tau){
    ifstream taskFile;
    taskFile.open(task_file, ios::in);
    if(!taskFile.is_open()){
        cout << "No such file: " << task_file << " or permission denied." << endl;
        exit(0);
    }

    ofstream outputFile;
    outputFile.open(output_file,ios::out);
    if(!outputFile.is_open()){
        cout<<"Can't open or create file: "<<output_file<<" or permission denied."<<endl;
        exit(0);
    }

    int taskNum;
    taskFile>>taskNum;
    outputFile<<taskNum<<endl;
    for(int taskID=0;taskID<taskNum;taskID++){
        cout<<taskID<<endl;
        int k, g;
        taskFile>>k>>g;
        vector<int> sigma, sigma1, sigma2;
        for(int i=0,realSelectedNode;i<k;i++){
            taskFile>>realSelectedNode;
            if(i<g){
                if(sigma1.size()<tau){
                    sigma1.push_back(realSelectedNode);
                }else{
                    sigma2.push_back(realSelectedNode);
                }
            }
        }

        //RoseNet Algorithm
        while(sigma1.size() < tau){
            pair<int, int> e=make_pair(-1, -1);
            double maxh=0;
            for(auto edge:G->Edges){
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
            if(e.first==e.second || find(sigma1.begin(), sigma1.end(), e.first)!=sigma1.end()){
                sigma1.push_back(e.second);
            }else{
                sigma1.push_back(e.first);
                sigma1.push_back(e.second);
            }
        }
        while(sigma2.size() < k - tau){
            pair<int,int> e=make_pair(-1,-1);
            double maxh=0;
            for(auto edge:G->Edges){
                if(find(sigma1.begin(), sigma1.end(), edge.second)!=sigma1.end()) continue;
                if(find(sigma1.begin(), sigma2.end(), edge.second)!=sigma2.end()) continue;
                if(sigma2.size()==k-tau-1 && edge.first!=edge.second) continue;
                double h=calcFunction(G, edge, sigma2);
                if(h > maxh){
                    maxh=h;
                    e=edge;
                }
            }
            if(e.first==-1 || e.second==-1) {
                break;
            }
            if(e.first==e.second || find(sigma1.begin(), sigma1.end(), e.first)!=sigma1.end() ||
                find(sigma2.begin(),sigma2.end(), e.first)!=sigma2.end()){
                sigma2.push_back(e.second);
            }else{
                sigma2.push_back(e.first);
                sigma2.push_back(e.second);
            }
        }

        for(auto it:sigma1) sigma.push_back(it);
        for(auto it:sigma2) sigma.push_back(it);

        outputFile<<k<<" "<<g<<" ";
        for(int i=0;i<sigma.size() && i<k; i++) outputFile<<sigma[i]<<" ";
        outputFile<<endl;
    }

    taskFile.close();
    outputFile.close();
}

void check(string task_file, string output_file, string result_file, int tau){
    ifstream taskFile;
    taskFile.open(task_file, ios::in);
    if(!taskFile.is_open()){
        cout << "No such file: " << task_file << " or permission denied." << endl;
        exit(0);
    }

    ifstream outputFile;
    outputFile.open(output_file,ios::in);
    if(!outputFile.is_open()){
        cout<<"No such file: "<<output_file<<" or permission denied."<<endl;
        exit(0);
    }

    ofstream resultFile;
    resultFile.open(result_file,ios::out);
    if(!resultFile.is_open()){
        cout<<"Can't open or create file: "<<result_file<<" or permission denied."<<endl;
        exit(0);
    }

    int taskNum, temp;
    taskFile>>taskNum;
    outputFile>>temp;
    int accuracyCount=0, totalCount=0;
    int SequenceCount=0, totalSequence=0;
    for(int taskID=0;taskID<taskNum;taskID++){
        int k1,g,k2;
        taskFile>>k1>>g;
        outputFile>>k2>>temp;
        totalCount += k1 - g;

        vector<int> realSeq;
        vector<int> Sigma;
        map<pair<int,int>, bool> M;
        for(int i=0,item;i<k1;i++){
            taskFile>>item;
            realSeq.push_back(item);
            for(int j=0;j<=i;j++){
                M[make_pair(realSeq[j],realSeq[i])] = true;
                totalSequence++;
            }
        }
        for(int i=0,item;i<k2;i++){
            outputFile>>item;
            Sigma.push_back(item);
            if(i>=g && find(realSeq.begin(),realSeq.end(),item)!=realSeq.end()){
                accuracyCount++;
            }
            for(int j=0;j<=i;j++){
                if(M.find(make_pair(Sigma[j],Sigma[i]))!=M.end())  SequenceCount++;
            }
        }
    }

    double accuracy = 1.0 * accuracyCount / totalCount;
    double sequenceScore = 1.0 * SequenceCount /totalSequence;

    resultFile<<"Accuracy: "<<accuracy<<endl;
    resultFile<<"Sequence Score:"<<sequenceScore<<endl;

    taskFile.close();
    outputFile.close();
    resultFile.close();
}


int main(int argc, char* argv[]){
    string network_file, task_file, output_file="output.txt", result_file="result.txt";
    int tau=5;
    auto cli = (
            value("network file", network_file),
            value("task file", task_file),
            option("-o") & value("output filename", output_file),
            option("-result") & value("result filename", result_file),
            //option("-k") & value("budget k(default: 10)", k),
            option("-tau") & value("tau(default:5)", tau)
            );

    if(!parse(argc, argv, cli)){
        cout<< make_man_page(cli, argv[0]);
        return 0;
    }

    Graph *G=new Graph(network_file);

    RoseNetsAlgorithm(G,task_file,output_file,tau);

    check(task_file,output_file, result_file, tau);

    return 0;
}