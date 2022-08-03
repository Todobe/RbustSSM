
#include "./include/clipp.h"
#include "./Graph.h"
#include "./Functions.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <ctime>

using namespace clipp;
using namespace std;

void calcFunctionValue(vector<double> &functionValue, Graph *G, const vector<int> &sigma, int g,int k, int tau){
    int shuffle_count = 100;
    vector<bool> del=vector<bool>(k);
    vector<int> seq;
    for(int K=0;K<k-g;K++) {
        seq.push_back(K+g);
        double ans=0;
        for(int l=0;l<shuffle_count;l++) {
            //random_shuffle(seq.begin(),seq.end());
            for (int i = 0; i < k; i++) del[i] = false;
            for (int i = 0; i < min(tau,int(seq.size())); i++) del[seq[i]] = true;
            for (int i = g; i <= K+g; i++) {
                double cnt = 1;
                for (int j = 0; j <= i; j++) {
                    if (del[i] || del[j]) continue;
                    pair<int, int> tmpe = make_pair(sigma[j], sigma[i]);
                    if (G->Weight.find(tmpe) != G->Weight.end()) {
                        cnt *= 1 - G->Weight[tmpe];
                    }
                }
                ans += 1 - cnt;
            }
        }
        functionValue[K] += ans / shuffle_count;
    }
}

void calcAccuracyScore(vector<double> &accuracyScore, const vector<int> &sigma, const vector<int> &realSigma, int g, int k, int tau){
    int count = 0;
    for (int i = 0; i < k - g; i++) {
        //if (find(realSigma.begin(), realSigma.end(), sigma[g + i]) != realSigma.end()) count++;
        //if (count > tau) accuracyScore[i] += count - tau;
        if(i>=tau && find(realSigma.begin(), realSigma.end(), sigma[g + i]) != realSigma.end()) count++;
        accuracyScore[i] += count;
    }
}

void calcSequenceScore(vector<double> &sequenceScore, const vector<int> &sigma, const vector<int> &realSigma, int g, int k, int tau){
    map<pair<int,int>,bool> M;
    for(int i=g;i<realSigma.size();i++){
        for(int j=0;j<=i;j++){
            M[make_pair(realSigma[j],realSigma[i])]=true;
        }
    }
    vector<pair<int,int> > degree;
    int count=0;
    for(int i=0;i<k-g;i++){
        int cur=i+g;
        int cnt=0;
        for(int j=0;j<=cur;j++){
            if(M.find(make_pair(sigma[j],sigma[cur]))!=M.end()){
                cnt++;
                if(j>=g) {
                    if(j!=cur) degree[j-g].first++;
                }
            }
        }
        degree.emplace_back(cnt,i);
        count+=cnt;
        int tempCount=count;
        vector<pair<int,int> > temp=degree;
        //sort(temp.begin(),temp.end(),greater<pair<int,int> >());
        for(int j=0;j<min(i+1,tau);j++){
            tempCount-=temp[j].first;
            int item=temp[j].second+g;
            for(int l=0;l<j;l++){
                int t1 = item;
                int t2=temp[l].second+g;
                if(t1>t2) swap(t1,t2);
                if(M.find(make_pair(sigma[t1],sigma[t2]))!=M.end()){
                    tempCount++;
                }
            }
        }
        if(i<tau && tempCount!=0){
            cout<<"real: ";
            for(auto it: realSigma) cout<<it<<" ";
            cout<<endl;
            cout<<"Sigma: ";
            for(auto it: sigma) cout<<it<<" ";
            cout<<endl;
            cout<<"degree: ";
            for(auto it: degree) cout<<"("<<it.first<<" "<<it.second<<") ";
            cout<<endl;
            cout<<"temp: ";
            for(auto it:temp) cout<<"("<<it.first<<" "<<it.second<<") ";
            cout<<endl;
            cout<<count<<" "<<tempCount<<endl;
            exit(0);
        }
        sequenceScore[i]+=tempCount;
    }
}

void Run(Graph *G, string task_file, string output_file, string result_file, int tau, int g, int k, string func, bool eval_del=true){
    ifstream taskFile;
    taskFile.open(task_file, ios::in);
    if(!taskFile.is_open()){
        cout << "No such file: " << task_file << " or permission denied." << endl;
        exit(0);
    }

    ofstream outputFile, resultFile;
    ifstream inputFile;
    if(func=="check"){
        inputFile.open(output_file, ios::in);
        if(!taskFile.is_open()){
            cout << "No such file: " << output_file << " or permission denied." << endl;
            exit(0);
        }
    }else {
        outputFile.open(output_file, ios::out);
        if (!outputFile.is_open()) {
            cout << "Can't open or create file: " << output_file << " or permission denied." << endl;
            exit(0);
        }
    }

    resultFile.open(result_file,ios::out | ios::app);
    if(!resultFile.is_open()){
        cout<<"Can't open or create file: "<<result_file<<" or permission denied."<<endl;
        exit(0);
    }

    clock_t start_time=clock();
    vector<double> accuracyScore=vector<double>(k-g,0);
    vector<double> sequenceScore=vector<double>(k-g,0);
    vector<double> functionValue=vector<double>(k-g,0);

    int tmp;
    int taskNum, totalTask = 0;
    taskFile>>taskNum;
    if(func=="check"){
        inputFile>>tmp;
    }else {
        outputFile << taskNum << endl;
    }
    for(int taskID=0;taskID<taskNum;taskID++){
        if(taskID%1000==0) cout<<func<<": "<<taskID<<"/"<<taskNum<<endl;
        int totalNodeNum;
        taskFile>>totalNodeNum;
        vector<int> sigma, realSigma;
        for(int i=0,realSelectedNode;i<totalNodeNum;i++){
            taskFile>>realSelectedNode;
            realSigma.push_back(realSelectedNode);
        }

        if(totalNodeNum < k) continue;
        totalTask ++ ;

        if(func=="RoseNet") RoseNetAlgorithm(G, sigma, realSigma, tau, g, k);
        else if(func=="Frequency") Frequency(G, sigma, realSigma, tau, g, k);
        else if(func=="OMegA") OMegA(G, sigma, realSigma, tau, g, k);
        else if(func=="Sequence") RoseNetAlgorithm(G, sigma, realSigma, 0, g, k);
        else if(func=="check"){
            inputFile>>tmp;
            for(int i=0,node;i<tmp;i++){
                inputFile>>node;
                sigma.push_back(node);
            }
        }
        else RoseNetAlgorithm(G, sigma, realSigma, tau, g, k);

        if(func!="check") {
            outputFile << k << " ";
            for (int i = 0; i < sigma.size() && i < k; i++) outputFile << sigma[i] << " ";
            outputFile << endl;
        }
        if(eval_del) {
            calcAccuracyScore(accuracyScore, sigma, realSigma, g, k, tau);
            calcSequenceScore(sequenceScore, sigma, realSigma, g, k, tau);
            calcFunctionValue(functionValue, G, sigma, g, k, tau);
        }else{
            calcAccuracyScore(accuracyScore, sigma, realSigma, g, k, 0);
            calcSequenceScore(sequenceScore, sigma, realSigma, g, k, 0);
            calcFunctionValue(functionValue, G, sigma, g, k, 0);
        }
    }

    if(totalTask==0){
        resultFile<<"No valid Task";
        return;
    }
    for(int i=0;i<k-g;i++){
        accuracyScore[i] /= totalTask;
        sequenceScore[i] /= totalTask;
        functionValue[i] /= totalTask;
    }

    clock_t end_time = clock();
    double total_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    resultFile<<"Run Algorithm "<<func<<endl;
    resultFile<<"Nodes Number: "<<G->nodeNum<<" Edges Number: "<<G->edgeNum<<endl;
    resultFile<<"k: "<<k<<" g: "<<g<<" tau: "<<tau<<" delete: "<<eval_del<<endl;
    resultFile<<"Total Task Number: "<<taskNum<<endl;
    resultFile<<"Total Valid Task: "<<totalTask<<endl;
    resultFile<<"Time: "<<total_time<<" seconds."<<endl;

    resultFile<<"Accuracy Score:"<<endl;
    for(int i=0;i<k-g;i++){
        resultFile<<accuracyScore[i]<<" ";
    }
    resultFile<<endl;
    resultFile<<"Sequence Score:"<<endl;
    for(int i=0;i<k-g;i++){
        resultFile<<sequenceScore[i]<<" ";
    }
    resultFile<<endl;
    resultFile<<"Function Value:"<<endl;
    for(int i=0;i<k-g;i++){
        resultFile<<functionValue[i]<<" ";
    }
    resultFile<<endl;
    resultFile<<endl;

    taskFile.close();
    outputFile.close();
    resultFile.close();
}


int main(int argc, char* argv[]){
    string network_file, task_file, output_file="output.txt", result_file="result.txt", func="RoseNet";
    int tau=5, g=4, k=10;
    auto cli = (
            value("network file", network_file),
            value("task file", task_file),
            option("-o") & value("output filename", output_file),
            option("-result") & value("result filename", result_file),
            option("-k") & value("budget k(default: 10)", k),
            option("-g") & value("given g(default: 4)", g),
            option("-tau") & value("tau(default:5)", tau),
            option("-alg") & value("algorithm(default:RoseNet", func)
            );

    if(!parse(argc, argv, cli)){
        cout<< make_man_page(cli, argv[0]);
        return 0;
    }
    Graph *G=new Graph(network_file);
    if(tau==-1){
        for(int t=0;t<=10;t++){
            Run(G,task_file, output_file, result_file, t, g, k, func);
            if(func=="RoseNet" || func=="Sequence")
            Run(G,task_file, output_file, result_file, t, g, k, func, false);
        }
    }else {
        Run(G, task_file, output_file, result_file, tau, g, k, func);
    }
    return 0;
}