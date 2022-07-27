
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

void calcAccuracyScore(vector<double> &accuracyScore, const vector<int> &sigma, const vector<int> &realSigma, int g, int k, int tau){
    int count=0;
    for(int i=0;i<k-g;i++){
        if(find(realSigma.begin(),realSigma.end(),sigma[g+i])!=realSigma.end()) count++;
        if(count>tau) accuracyScore[i] += count-tau;
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
                    else cnt++;
                }
            }
        }
        degree.emplace_back(cnt,i);
        count+=cnt;
        int tempCount=count;
        vector<pair<int,int> > temp=degree;
        sort(temp.begin(),temp.end(),greater<pair<int,int> >());
        for(int j=0;j<tau;j++){
            tempCount-=temp[j].first;
            int item=sigma[temp[j].second+g];
            for(int l=0;l<=j;l++){
                if(M.find(make_pair(sigma[temp[l].second+g],item))!=M.end()
                    || M.find(make_pair(item,sigma[temp[l].second+g]))!=M.end()){
                    tempCount++;
                }
            }
        }
        sequenceScore[i]+=tempCount;
    }
}

void Run(Graph *G, string task_file, string output_file, string result_file, int tau, int g, int k, string func){
    ifstream taskFile;
    taskFile.open(task_file, ios::in);
    if(!taskFile.is_open()){
        cout << "No such file: " << task_file << " or permission denied." << endl;
        exit(0);
    }

    ofstream outputFile, resultFile;
    outputFile.open(output_file,ios::out);
    if(!outputFile.is_open()){
        cout<<"Can't open or create file: "<<output_file<<" or permission denied."<<endl;
        exit(0);
    }

    resultFile.open(result_file,ios::out);
    if(!resultFile.is_open()){
        cout<<"Can't open or create file: "<<result_file<<" or permission denied."<<endl;
        exit(0);
    }

    clock_t start_time=clock();
    vector<double> accuracyScore=vector<double>(k-g);
    vector<double> sequenceScore=vector<double>(k-g);

    int taskNum;
    taskFile>>taskNum;
    outputFile<<taskNum<<endl;
    for(int taskID=0;taskID<taskNum;taskID++){
        cout<<taskID<<endl;
        int totalNodeNum;
        taskFile>>totalNodeNum;
        vector<int> sigma, realSigma;
        for(int i=0,realSelectedNode;i<totalNodeNum;i++){
            taskFile>>realSelectedNode;
            realSigma.push_back(realSelectedNode);
        }
        if(func=="RoseNet") RoseNetAlgorithm(G, sigma, realSigma, tau, g, k);
        else if(func=="Frequency") Frequency(G, sigma, realSigma, tau, g, k);
        else if(func=="OMegA") OMegA(G, sigma, realSigma, tau, g, k);
        else RoseNetAlgorithm(G, sigma, realSigma, tau, g, k);

        outputFile<<k<<" ";
        for(int i=0;i<sigma.size() && i<k; i++) outputFile<<sigma[i]<<" ";
        outputFile<<endl;
        calcAccuracyScore(accuracyScore, sigma, realSigma, g, k, tau);
        calcSequenceScore(sequenceScore, sigma, realSigma, g, k, tau);
    }

    for(int i=0;i<k-g;i++){
        accuracyScore[i] /= taskNum;
        sequenceScore[i] /= taskNum;
    }

    clock_t end_time = clock();
    double total_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    resultFile<<"Run Algorithm "<<func<<endl;
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

    Run(G, task_file, output_file, result_file, tau, g, k, func);

    return 0;
}