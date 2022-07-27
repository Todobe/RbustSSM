//
// Created by DELL on 2022/7/27.
//

#ifndef ROBUSTSSM_FUNCTIONS_H
#define ROBUSTSSM_FUNCTIONS_H

void RoseNetAlgorithm(Graph *G, vector<int> &sigma, const vector<int> realSigma, int tau, int g,int k);
void Frequency(Graph *G, vector<int> &sigma, const vector<int> realSigma, int tau, int g,int k);
void OMegA(Graph *G, vector<int> &sigma, const vector<int> realSigma, int tau, int g,int k);

#endif //ROBUSTSSM_FUNCTIONS_H
