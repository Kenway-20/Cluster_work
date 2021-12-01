//
// Created by LENOVO on 2021/11/23.
//

#ifndef CLUSTER_WORK_KMEANS_H
#define CLUSTER_WORK_KMEANS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Silhouette.h"

using namespace std;
typedef unsigned int uint;

struct Cluster{
    vector<double> centroid;
    vector<uint> samples;
};

class Kmeans{
private:
    vector<vector<double>> trainX;
    uint kindNum;
    vector<Cluster> clusters_out;
public:
    vector<int> data_cluster;
    void loaddata(string file_name);
    double cal_distance(vector<double> a, vector<double> b);
    vector<Cluster> runserver(uint k, uint maxepoches);
    void show_result();
};

void Kmeans::loaddata(string file_name){
    ifstream fin(file_name); //���ļ�������
    string line;

    while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
    {
        //if(trainX.size() >= 500) break; //�������ݴ�С
        istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
        vector<double> fields; //����һ���ַ�������
        string field;
        while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
        {
            fields.push_back(stod(field)); //���ոն�ȡ���ַ�����ӵ�����fields��
        }
        trainX.push_back(fields);
    }
    fin.close();
}

double  Kmeans::cal_distance(vector<double> a, vector<double> b){
    uint da = a.size();
    uint db = b.size();
    if (da != db) cerr << "Dimensions of two vectors must be same!!\n";
    double val = 0.0;
    for (uint i = 0; i < da; i++)
    {
        val += pow((a[i] - b[i]), 2);
    }
    return pow(val, 0.5);
}

vector<Cluster> Kmeans::runserver(uint k, uint maxepoches){
    const uint row_num = trainX.size();
    const uint col_num = trainX[0].size();
    kindNum = k;
    /*��ʼ����������*/
    vector<Cluster> clusters(k);
    uint seed = (uint)time(NULL);
    for (uint i = 0; i < k; i++){
        srand(seed);
        int c = rand() % row_num;
        clusters[i].centroid = trainX[c];
        seed = rand();
    }
/*��ε���ֱ�������������������maxepoches��*/
    for (uint it = 0; it < maxepoches; it++)
    {
        /*ÿһ�����¼����������������֮ǰ�����ԭ����������Ϣ*/
        for (uint i = 0; i < k; i++)
        {
            clusters[i].samples.clear();
        }
        /*���ÿ���������Ӧ��������һ������*/
        for (uint j = 0; j < row_num; j++)
        {
            /*����ʼ�����ڵ�0������*/
            uint c = 0;
            double min_distance = cal_distance(trainX[j],clusters[c].centroid);
            for (uint i = 1; i < k; i++)
            {
                double distance = cal_distance(trainX[j], clusters[i].centroid);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    c = i;
                }
            }
            clusters[c].samples.push_back(j);
        }
        /*���¾�������*/
        for (uint i = 0; i < k; i++)
        {
            vector<double> val(col_num, 0.0);
            for (uint j = 0; j < clusters[i].samples.size(); j++)
            {
                uint sample = clusters[i].samples[j];
                for (uint d = 0; d < col_num; d++)
                {
                    val[d] += trainX[sample][d];
                    if (j == clusters[i].samples.size() - 1)
                        clusters[i].centroid[d] = val[d] / clusters[i].samples.size();
                }
            }
        }
    }
    clusters_out = clusters;
    return clusters;
}

void Kmeans::show_result() {
    data_cluster = vector<int> (trainX.size());
    Silhouette sil((int)kindNum, trainX[0].size(), trainX.size());
    for(int cluster_id = 0; cluster_id < clusters_out.size(); cluster_id++) {
        for (int j = 0; j < clusters_out[cluster_id].samples.size(); j++) {
            int i = clusters_out[cluster_id].samples[j];
            double temple[trainX[i].size()];
            for (int temple_index = 0; temple_index < trainX[i].size(); temple_index++)
                temple[temple_index] = trainX[i][temple_index];
            sil.addClusterData(cluster_id, temple, i);
            data_cluster[i] = cluster_id;
        }
    }
    sil.showCluster();
    cout << "����ϵ��Ϊ�� " << sil.calSilhouette() << endl;
}

#endif //CLUSTER_WORK_KMEANS_H
