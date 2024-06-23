#include "treeindex.h"
using namespace std;
VectorDataset *vecdatset = new VectorDataset;

Tree::Tree(int axis, int t, vector<int> ex):type(t), left(NULL), right(NULL)
{
    c = new content;
    c->indices = ex; // Gives indices=vector of indices contained in node
    c->delta.resize(c->indices.size(), 0); // Initialises delta vector to size of node and values=0
    c->median = -1; 
    c->med_axis = axis; //Sets med_axis=axis 
}
Tree::~Tree() { delete left; delete right; delete c; }

DataVector Tree::KDRule(int dim, int idx)
{
    DataVector result(dim); //Creates Datavector of size dim
    result.set(idx); //Sets index idx to 1
    return result;
}

DataVector Tree::RPRule(int dim)
{
    DataVector result(dim); 
    srand(time(NULL));
    result.random_unit(dim); //Makes result into a random unit vector
    return result;
}

void Tree::MakeTree()
{
    int dim = vecdatset->getdimension(); //Dimension of VectorDataset to be used
    int size = c->indices.size(); //Total number of indices stored in one node
    c->delta.resize(size, 0); //Delta vector of the same size as indices vector
    if(size<=BASE) return;
    c->rule_datavec = (type==0)?KDRule(dim, c->med_axis):RPRule(dim); // Returns datavector according to rule
    sort(c->indices.begin(), c->indices.end(), [this](int i, int j){return vecdatset->operator[](i).comparator(vecdatset->operator[](j), c->rule_datavec);});
    // Sorts indices onthe basis of rule
    c->median = vecdatset->operator[](c->indices[size/2])*c->rule_datavec;
    // Make Median Datavector 
    vector<int> l;
    vector<int> r;

    for(int i=0;i<size;++i)
        {
            srand(time(0));
            if(type==1) c->delta[i]=(((float)rand()/RAND_MAX)*2-1)*6*vecdatset->farthest_distance(vecdatset->operator[](c->indices[i]))/sqrt(dim);
            // if RP make delta = (rand num b/w [-1,1])
            if(vecdatset->operator[](c->indices[i])*c->rule_datavec<c->median+c->delta[i]) //(Check) Dot product + delta 
            {
                l.push_back(c->indices[i]);
            }
            else
            {
                r.push_back(c->indices[i]);
            }
        }
        left = new Tree((c->med_axis+1)%dim, type, l);
        right = new Tree((c->med_axis+1)%dim, type, r);
        left->MakeTree(); right->MakeTree(); //Make Left and Right Trees
}

VectorDataset Tree::search(DataVector *d, int k)
{
    priority_queue<pair<double, int>> maxheap; //Make a MaxHeap of Distance and index of Datavector
    inside_search(d, k, maxheap); // maxheap=heap of k datavector nearest to vectordataset
    VectorDataset result; // Result will store all the k nearest Datavectors indices and Distances
    while(!maxheap.empty()){
        result.AddDataVector(vecdatset->operator[](maxheap.top().second));
        maxheap.pop();
    }
    return result;
}

void Tree::inside_search(DataVector *d, int k, priority_queue<pair<double, int> > &heap)
{
    if(left == NULL && right == NULL) {find_knear(*d, k, heap);  return;}
    double dis = (*d)*c->rule_datavec;
    double del = (type==1)?(((float)rand()/RAND_MAX)*2-1)*6*vecdatset->farthest_distance(*d)/sqrt(d->getDimension()):0;
    if((*d)*c->rule_datavec<c->median+del)
    {
        left->inside_search(d, k, heap); //If Maxheap is enough or boundary condition is not crossed, go further
        // else search the other half and return
        if(heap.size()<k || dis<heap.top().first) right->inside_search(d, k, heap);
    }
    else
    {
        right->inside_search(d, k, heap);
        if(heap.size()<k || dis<=heap.top().first) left->inside_search(d, k, heap);
    }
}

void Tree::find_knear(DataVector &data, int k, priority_queue<pair<double, int> > &heap)
{            
    vector<double> distances;
    //calculate the distance between the query and each data point in the dataset
    for(int i=0;i<c->indices.size();i++) { distances.push_back(vecdatset->operator[](c->indices[i]).dist(data));}

    //keep track of k nearest neighbours with max heap
    for(int i=0;i<c->indices.size();i++){
        if(heap.size()<k){
            heap.push({distances[i], c->indices[i]});
        }
        else{
            if(heap.top().first>distances[i]){
                heap.pop();
                heap.push({distances[i], c->indices[i]});
            }
        }
    }
}

void Tree::ShowTree()
{
    if(c==NULL) return;
    for(int i = 0; i<c->indices.size(); i++) {cout<<c->indices[i]<<" ";} cout<<endl;
    if(left != NULL) left->ShowTree();
    if(right != NULL) right->ShowTree();
    return;
}


TreeIndex::TreeIndex(int i, int t): root(new Tree(i, t, vector<int>(vecdatset->getsize(), 0)))
{
    for(int i=0;i<vecdatset->getsize();++i) root->c->indices[i] = i;
    root->MakeTree();
};

TreeIndex::~TreeIndex() {delete root;}
void TreeIndex::ShowTreeIndex() {root->ShowTree();}
VectorDataset TreeIndex::find_knn(DataVector *v, int k) {return root->search(v, k);}

KDTreeIndex::KDTreeIndex(int random): TreeIndex(vecdatset->getsize()/2, 0){}
KDTreeIndex::~KDTreeIndex() {}

RPTreeIndex::RPTreeIndex(int random): TreeIndex(-1, 1){}
RPTreeIndex::~RPTreeIndex() {}

int main()
{
    vecdatset->ReadVectorDataset("small.csv");
    VectorDataset testdataset;
    testdataset.ReadVectorDataset("small.csv");
    int type_,k;
    cout << "Finding k nearest neighbour by RP or KD tree indexing\n" << endl;
    cout << "Enter 0 for KD tree indexing or 1 for RP tree indexing: "; cin >> type_;
    cout << "Enter the value of k: "; cin>>k;
    if (type_ == 0) {
        for(int i=1;i<testdataset.getsize();i++){
            cout<<k<<" Nearest Datavectors "<<" WRT Datavector at index "<<i<<" : \n";
            KDTreeIndex::GetInstance(0).find_knn(&testdataset.operator[](i),k).ShowVectorDataset(); cout<<endl;
        }
    }
    else{
        for(int i=1;i<testdataset.getsize();i++){
            cout<<k<<" Nearest Datavectors "<<" WRT Datavector at index "<<i<<" : \n";
            RPTreeIndex::GetInstance(1).find_knn(&testdataset.operator[](i),k).ShowVectorDataset(); cout<<endl;
        }
    }
    return 0;
}