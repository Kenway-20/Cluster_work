//
// Created by LENOVO on 2021/11/25.
//

#ifndef NEW_CLUSTER_KMEANS_PLUS3_H
#define NEW_CLUSTER_KMEANS_PLUS3_H
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
#include "KmPoint3.h"
#define PI 3.14159265358979323846
template<typename Real = double, int Dim3 = 178>
class KM_API KMeans_plus3{
        public:
        typedef KmPoint3<Real, Dim3> KmPoint3;
        public:
        vector<int> data_cluster;
        vector<vector<double>> data_content;
        KMeans_plus3(){ srand((unsigned)time(0)); }
        Real randf(Real m){
            return m * rand() / (RAND_MAX - 1.);
        }

        Real dist(KmPoint3 &a, KmPoint3 &b){
            Real len = 0;
            for(int i = 0; i < Dim3; ++i){
                len += (a[i] - b[i]) * (a[i] - b[i]);
            }
            return len;
        }

        void dataGenerator(string filename, Real radius, vector<KmPoint3> &pts);
        int nearest(KmPoint3 &pt, vector<KmPoint3> &cents, Real &d);
        void kpp(vector<KmPoint3> &pts, vector<KmPoint3> &cents);
        void kmcluster(vector<KmPoint3> &pts, int k, vector<KmPoint3> &outCents, vector<vector<KmPoint3>> &outPts);
        void serialize(vector<vector<KmPoint3>> &outPts);
};
#endif //NEW_CLUSTER_KMEANS_PLUS3_H
