#include "VectorDataset.h"
using namespace std;
VectorDataset knear(VectorDataset &dataset, DataVector &data, int k)
{
    VectorDataset result;
    
    vector<double> distances;
    //calculate the distance between the query and each data point in the dataset
    for(int i=0;i<dataset.getsize();i++){
        distances.push_back(dataset[i].dist(data));
    }

    //keep track of k nearest neighbours with max heap
    priority_queue<pair<double, int> > maxheap;
    for(int i=0;i<dataset.getsize();i++){
        if(maxheap.size()<k){
            maxheap.push({distances[i], i});
        }
        else{
            if(maxheap.top().first>distances[i]){
                maxheap.pop();
                maxheap.push({distances[i], i});
            }
        }
    }

    //store the k nearest neighbours in the result
    while(!maxheap.empty()){
        result.AddDataVector(dataset[maxheap.top().second]);
        maxheap.pop();
    }

    return result;
}
vector<double> getNextLineAndSplitIntoTokens(const string& line)
{
    vector<double> result; double d;
    stringstream lineStream(line);
    string cell;
    while(std::getline(lineStream,cell, ','))
    {
        d=stod(cell);
        result.push_back(d);
    }
    return result;
}
void ReadVectorDataSet(VectorDataset& vecdat,string filename)
{
    ifstream file; vector<double> v;
    file.open(filename,ios::in);
    string line;
    while (getline(file, line)) {
        v=getNextLineAndSplitIntoTokens(line);
        DataVector vec(v);
        vecdat.AddDataVector(vec);
    } 
    file.close();
}