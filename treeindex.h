#include "VectorDataset.h"
using namespace std;
#define BASE 100
class Tree;
class TreeIndex;
class KDTreeIndex;
class RPTreeIndex;
class Tree
{
    Tree *left;
    Tree *right;
    content *c;
    int type; // 0 for KD, 1 for RP
    friend class TreeIndex;
    public:
    DataVector KDRule(int , int );
    DataVector RPRule(int );
    Tree(int, int , vector<int> );
    void MakeTree();
    VectorDataset search(DataVector *, int );
    void inside_search(DataVector *, int , priority_queue<pair<double, int> > &);
    void find_knear(DataVector &, int, priority_queue<pair<double, int> > &);
    void ShowTree();
    ~Tree();
};
class TreeIndex 
{
    Tree *root;
    protected:
        TreeIndex(int , int );
    public:
        static int type;
        static TreeIndex& GetInstance(int i, int t)
        {
            static TreeIndex instance(i, t);
            return instance;
        }
        ~TreeIndex();
        void ShowTreeIndex();
        VectorDataset find_knn(DataVector *, int );
};
class KDTreeIndex : public TreeIndex 
{
    private:
        KDTreeIndex(int );
        ~KDTreeIndex();
    public:
        static KDTreeIndex& GetInstance(int random){
            static KDTreeIndex instance(0);
            type = 0;
            return instance;
        }
};
class RPTreeIndex : public TreeIndex 
{
    private:
        RPTreeIndex(int );
        ~RPTreeIndex();
    public:
       static RPTreeIndex& GetInstance(int random){
            static RPTreeIndex instance(0);
            type = 1;
            return instance;
        }
};
int TreeIndex::type = -1;