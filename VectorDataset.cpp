#include"VectorDataset.h"
using namespace std;
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
VectorDataset::VectorDataset(){}
VectorDataset::~VectorDataset(){}
DataVector & VectorDataset::operator[](int i) {return datv[i];}
void VectorDataset::AddDataVector(const DataVector& other) 
{
    datv.push_back(other);
}
void VectorDataset::RemoveDataVector(const DataVector& other) {datv.push_back(other);}
double VectorDataset::getvalue(int index, int axis) {return datv[index].getvalue_datavector(axis);}

void VectorDataset::printindex(int index){datv[index].showDataVector();}

DataVector& VectorDataset::getvalue(int i) {return datv[i];}

int VectorDataset::getsize() {return(datv.size());}

int VectorDataset::getdimension() {return(datv[0].get_size());}

int VectorDataset::get_median(content* node, int axis) {
    vector<int> sortt;
    for(int i: node->indices)
    {
        sortt.push_back(datv[i].getvalue_datavector(axis));
    } sort(sortt.begin(),sortt.end()); int n=sortt.size();
    return sortt[(n-1)/2];
}
void const VectorDataset::ShowVectorDataset()
{
    for (DataVector vec : datv)
    {
        vec.showDataVector();
    }
    cout<<endl;
}

double VectorDataset::farthest_distance(DataVector &data)
{
        double result=0;
        for(int i=0;i<datv.size();i++){
            result=max(result, datv[i].dist(data));
        }
        return result;
}
void VectorDataset::ReadVectorDataset(string filename)
    {
        ifstream file; vector<double> v;
        file.open(filename,ios::in);
        string line; getline(file, line); 
        while (getline(file, line)) {
            v=getNextLineAndSplitIntoTokens(line);
            DataVector vec(v);
            datv.push_back(vec);
        } 
        file.close();
    }