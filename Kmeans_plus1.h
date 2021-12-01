//
// Created by LENOVO on 2021/11/25.
//

#ifndef TEST_CLUST_KMEANS_PLUS_H
#define TEST_CLUST_KMEANS_PLUS_H
#ifndef KMEANS_H
#define KMEANS_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
#include "KmPoint1.h"
#define PI 3.14159265358979323846
template<typename Real = double, int Dim1 = 128>
class KM_API KMeans_plus1{
public:
    typedef KmPoint1<Real, Dim1> KmPoint1;
public:
    vector<int> data_cluster;
    vector<vector<double>> data_content;
    KMeans_plus1(){ srand((unsigned)time(0)); }
    Real randf(Real m){
        return m * rand() / (RAND_MAX - 1.);
    }

    Real dist(KmPoint1 &a, KmPoint1 &b){
        Real len = 0;
        for(int i = 0; i < Dim1; ++i){
            len += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return len;
    }

    void dataGenerator(string filename, Real radius, vector<KmPoint1> &pts);
    int nearest(KmPoint1 &pt, vector<KmPoint1> &cents, Real &d);
    void kpp(vector<KmPoint1> &pts, vector<KmPoint1> &cents);
    void kmcluster(vector<KmPoint1> &pts, int k, vector<KmPoint1> &outCents, vector<vector<KmPoint1>> &outPts);
    void serialize(vector<vector<KmPoint1>> &outPts);
};

#endif
#endif //TEST_CLUST_KMEANS_PLUS_H