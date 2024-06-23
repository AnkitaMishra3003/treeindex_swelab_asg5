#include"datavector.h"
using namespace std;
DataVector::DataVector (int dimension) : v(dimension,0.0){}
DataVector::DataVector(vector<double> vec) : v(vec){}
DataVector::~DataVector(){}
void DataVector::set(int idx){v[idx] = 1; return;}
DataVector::DataVector(const DataVector& other) : v(other.v) {}
double DataVector::getvalue_datavector(int index){return v[index];}
DataVector& DataVector::operator=(const DataVector &other)
{
    if(v!=other.v)
    {v=other.v;}
    return(*this);
}
DataVector & DataVector::operator=(const std::vector<double> & vec)  {v=vec;}
void DataVector::append(double value){v.push_back(value);}
void DataVector::setDimension(int dimension){v.clear(); v.resize(dimension,0.0);}
int DataVector::getDimension() {return v.size();}
void DataVector::showDataVector()
{
    for(double value : v)
    {
        cout<<value<<" ";
    } 
    cout<<endl;
}
int DataVector::get_size()
{
    return(v.size());
}
DataVector DataVector::operator+(const DataVector &other)
{
    int n=v.size();
    if(other.v.size()!=n)
    {
        printf("Error. Dimension not same.\n");
        return *this;
    }
    DataVector res; res.v.resize(n);
    for(int i=0;i<n;i++)
    {
        res.v[i]=v[i]+other.v[i];
    }
    return res;
}
DataVector DataVector::operator-(const DataVector &other)
{
    int n=v.size();
    if(other.v.size()!=n)
    {
        printf("Error. Dimension not same.\n");
        return *this;
    }
    DataVector res; res.v.resize(n);
    for(int i=0;i<n;i++)
    {
        res.v[i]=v[i]-other.v[i];
    }
    return res;
}
double const DataVector::operator*(const DataVector &other)
{
    int n=v.size();
    if(other.v.size()!=n)
    {
        printf("Error. Dimension not same.\n");
        return 0.0;
    }
    float res=0;
    for(int i=0;i<n;i++)
    {
        res+=v[i]*other.v[i];
    }
    return res;
}
bool DataVector::comparator(DataVector &other, DataVector &rule) {return (*this)*rule<other*rule;}
double const DataVector::norm()
{
    float nor=sqrt((*this)*(*this));
    return(nor);
}
double const DataVector ::dist(const DataVector &other)
{
    float dista=(*this-other).norm();
    return dista;
}
void DataVector::random_unit(int size)
{
    srand (time(NULL));
    v.clear();
    v.resize(size);
    double sum=0;
    for(int i=0;i<size;i++){
        v[i]=(float)rand()/RAND_MAX;
        sum += v[i]*v[i];
    }
    sum = sqrt(sum);
    for(int i=0;i<size;i++){
        v[i]/=sum*1.0;
        // cout<<v[i]<<" ";
    }
    // cout<<endl;
    return;
}