#include"datavector.h"
class TreeIndex;
class VectorDataset{
    std::vector<DataVector> datv;
    public:
    VectorDataset();
    ~VectorDataset();
    DataVector & operator[](int ) ;
    void AddDataVector(const DataVector&);
    void RemoveDataVector(const DataVector&);
    double getvalue(int , int );
    void printindex(int);
    DataVector& getvalue(int);
    int getsize();
    int getdimension();
    int get_median(content *, int);
    double get_median(content *, std::vector<double> &);
    void const ShowVectorDataset();
    double farthest_distance(DataVector &);
    void ReadVectorDataset(std::string );
};