#include <bits/stdc++.h>

class TreeIndex;
class KDTreeIndex;
class RPTreeIndex;
class DataVector {
    std::vector<double> v;
    public:
    DataVector(int dimension=0);
    void set(int idx);
    DataVector(std::vector<double>);
    ~DataVector();
    DataVector(const DataVector&);
    DataVector & operator=(const DataVector &);
    DataVector & operator=(const std::vector<double> &);
    void append(double value);
    void setDimension(int dimension=0);
    int getDimension();
    void showDataVector();
    int get_size();
    double getvalue_datavector(int);
    DataVector operator+(const DataVector &);
    DataVector operator-(const DataVector &);
    double const operator*(const DataVector &);
    double const norm();
    double const dist(const DataVector &);
     bool comparator(DataVector &other, DataVector &rule);
    void random_unit(int);
};
typedef struct q1q1{
    std::vector<int> indices;
    int med_axis;
    DataVector rule_datavec; //Stores Datavector with only one 1(KD Tree) or random unit vector(RP Tree)
    std::vector<double> delta;
    double median;
}content;