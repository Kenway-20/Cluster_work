//
// Created by LENOVO on 2021/11/25.
//

#ifndef NEW_CLUSTER_KMEANS_PLUS2_H
#define NEW_CLUSTER_KMEANS_PLUS2_H
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
#include "KmPoint2.h"
#define PI 3.14159265358979323846
template<typename Real = double, int Dim2 = 128>
class KM_API KMeans_plus2{
        public:
        typedef KmPoint2<Real, Dim2> KmPoint2;
        public:
        vector<int> data_cluster;
        vector<vector<double>> data_content;
        KMeans_plus2(){ srand((unsigned)time(0)); }
        Real randf(Real m){
            return m * rand() / (RAND_MAX - 1.);
        }

        Real dist(KmPoint2 &a, KmPoint2 &b){
            Real len = 0;
            for(int i = 0; i < Dim2; ++i){
                len += (a[i] - b[i]) * (a[i] - b[i]);
            }
            return len;
        }

        void dataGenerator(string filename, Real radius, vector<KmPoint2> &pts);
        int nearest(KmPoint2 &pt, vector<KmPoint2> &cents, Real &d);
        void kpp(vector<KmPoint2> &pts, vector<KmPoint2> &cents);
        void kmcluster(vector<KmPoint2> &pts, int k, vector<KmPoint2> &outCents, vector<vector<KmPoint2>> &outPts);
        void serialize(vector<vector<KmPoint2>> &outPts);
};
#endif //NEW_CLUSTER_KMEANS_PLUS2_H
