#ifndef COPY_SILHOUETTE_H
#define COPY_SILHOUETTE_H

#include <iostream>
#include <cmath>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
using namespace std;


class Silhouette{
public:
    Silhouette(int cluster_num,int dim,int size);
    ~Silhouette();
    bool addClusterData(int _cluster_index, double* _data,int _data_index);
    double showCluster();
    double showClusterForCount();
    double calSilhouette();
private:
    int cluster_num;
    int dim;
    int size;
    vector<vector<vector<double> > > o_clustor;
    vector<vector<int> > index_cluster;

    double dist(const vector<double> x, const vector<double> u);
};

#endif //COPY_SILHOUETTE_H
