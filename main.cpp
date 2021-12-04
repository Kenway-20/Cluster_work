#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <time.h>
#include <iomanip>
#include <string>
#include <cmath>
#include <map>
#include <cstdio>
#include <unordered_map>

#include "Kmeans.h"
#include "Cure1.h"
#include "Cure2.h"
#include "Cure3.h"
#include "DBSCANClusterAnalysis1.h"
#include "DBSCANClusterAnalysis2.h"
#include "DBSCANClusterAnalysis3.h"
#include "Kmeans_plus1.cpp"
#include "Kmeans_plus2.cpp"
#include "Kmeans_plus3.cpp"
#include "Correct.h"



using namespace std;


vector<vector<double>> data1_content;
vector<string> data1_result;
vector<vector<double>> data2_content;
vector<string> data2_result;
vector<vector<double>> data3_content;
vector<string> data3_result;


//����data������Ӧ�����ת���ĺ������������ò���
vector<int> get_datacluster(vector<vector<int>> cluster_data, int data_num){
    vector<int> data_cluster(data_num);
    for(int i = 0; i < cluster_data.size(); i++){
        for(int j = 0; j < cluster_data[i].size(); j++){
            data_cluster[cluster_data[i][j]] = i;
        }
    }
    return data_cluster;
}

//�ⲿָ���һ�ԣ�ͬһ����ֻ��ͬһ��ǩ�������ԣ�ͬһ��ǩ�ܱ�������ͬһ����
//�ڲ�ָ������ϵ��
void correct(vector<string> data_result, vector<int> data_cluster){
    //cout << "data_result.size = " << data_result.size() << endl;
    //cout << "data_cluster.size = " << data_cluster.size() << endl;
    Correct cor(data_result, data_cluster);
    double one = cor.get_one() * 100;
    double total = cor.get_total() * 100;
    cout << "���ξ���Ĺ�һ��: " << one << '%' << endl;
    cout << "���ξ����������: " << total << '%' << endl;
}

//55.162s
void data1_pro(){
    ifstream fin("dataset/dataset1_t.csv"); //���ļ�������
    string line;
    bool flag = true;
    unordered_map<string, int> memo;
    while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
    {
        istringstream sin2(line); //�������ַ���line���뵽�ַ�����istringstream��
        string field2;
        while(getline(sin2, field2, ',')) {
            if (flag) {
                flag = false;
                continue;
            }
        }
        if(field2 != "EventId") {
            data1_result.push_back(field2);
            memo[field2]++;
        }
        //if(data1_result.size() >= 500) break;
    }
    //cout << "data1 result count = " << memo.size() << endl;
    fin.close();
}
//63.503s
void data2_pro(){
    string line;
    ifstream fin("dataset/dataset2_t.csv");
    bool flag = true;
    unordered_map<string, int> memo;
    while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
    {
        istringstream sin2(line); //�������ַ���line���뵽�ַ�����istringstream��
        string field2;
        while(getline(sin2, field2, ',')) {
            if (flag) {
                flag = false;
                continue;
            }
        }
        if(field2 != "EventId") {
            data2_result.push_back(field2);
            memo[field2]++;
        }
    }
    //cout << "data2 result count = " << memo.size() << endl;
    fin.close();
}
//0.532s
void data3_pro(){
    ifstream fin("dataset/dataset3_t.csv"); //���ļ�������
    string line;
    bool flag = true;
    unordered_map<string, int> memo;
    while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
    {
        if(flag){
            flag = false;
            continue;
        }
        istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
        vector<double> fields; //����һ���ַ�������
        string field;
        bool flag2 = true;
        while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
        {
            if(flag2){
                flag2 = false;
                continue;
            }
            if(fields.size() >=178 ){
                if(field != "1") field = "2";
                data3_result.push_back(field);
                memo[field]++;
                continue;
            }
            double temple = stod(field);
            fields.push_back(temple); //���ոն�ȡ���ַ�����ӵ�����fields��
        }
        //data3_content.push_back(fields);
    }
    fin.close();
}

//�����������ļ���������������������
void data1_kmeans(){
    clock_t startTime,endTime;
    cout<<"----------------Kmeans��data1�е�Ӧ��---------------------"<<endl;
    startTime = clock();
    Kmeans kmeans;
    kmeans.loaddata("dataset/dataset1_vec.csv");
    vector<Cluster> clusters_out = kmeans.runserver(109, 100); //��ε���ֱ�������������Ǿ�������͵�������
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    vector<vector<double>> out_centroid;
    kmeans.show_result();
    correct(data1_result, kmeans.data_cluster);
}
void data2_kmeans(){
    clock_t startTime,endTime;
    cout<<"----------------Kmeans��data2�е�Ӧ��---------------------"<<endl;
    startTime = clock();
    Kmeans kmeans;
    kmeans.loaddata("dataset/dataset2_vec.csv");
    vector<Cluster> clusters_out = kmeans.runserver(16, 100); //��ε���ֱ�������������Ǿ�������͵�������
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    vector<vector<double>> out_centroid;
    kmeans.show_result();
    correct(data2_result, kmeans.data_cluster);
}
void data3_kmeans(){
    clock_t startTime,endTime;
    cout<<"----------------Kmeans��data3�е�Ӧ��---------------------"<<endl;
    startTime = clock();
    Kmeans kmeans;
    kmeans.loaddata("dataset/dataset3_vec.csv");
    vector<Cluster> clusters_out = kmeans.runserver(2, 100); //��ε���ֱ�������������Ǿ�������͵�������
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    vector<vector<double>> out_centroid;
    kmeans.show_result();
    correct(data3_result, kmeans.data_cluster);
}

//.h�ļ����������ݵ������ά������������������������ʣ�.cpp�ļ��������ļ���
void data1_cure(){
    cout<<"----------------Cure��data1�е�Ӧ��---------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    Cure1 cure;
    if (cure.LoadPatterns()==FAILURE ){
        cout<<"���ܴ������ļ�:"<<endl;
        exit(0);
    }
    data1_content = cure.get_Pattern();
    cure.RunCure1();
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    cure.ShowClusters();
    correct(data1_result, cure.data_cluster);
}
void data2_cure(){
    cout<<"----------------Cure��data2�е�Ӧ��---------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    Cure2 cure;
    if (cure.LoadPatterns()==FAILURE ){
        cout<<"���ܴ������ļ�:"<<endl;
        exit(0);
    }
    cure.RunCure2();
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    cure.ShowClusters();
    correct(data2_result, cure.data_cluster);
}
void data3_cure(){
    cout<<"----------------Cure��data3�е�Ӧ��---------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    Cure3 cure;
    if (cure.LoadPatterns()==FAILURE ){
        cout<<"���ܴ������ļ�:"<<endl;
        exit(0);
    }
    cure.RunCure3();
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    cure.ShowClusters();
    correct(data3_result, cure.data_cluster);
}

//�����������뾶����С���ݵ������.h�������ļ�����Point.h����������ά��
//DBSCAN���Զ�ȥ�������㣬���Բ�����ԭ�����ݹ�ģȥ����ж�
void data1_DBSCAN()
{
    cout<<"----------------DBSCAN��data1���ݼ��е�Ӧ��-------------------"<<endl;
    double radius = 5;//�뾶
    int minPTs = 1;//��������С���ݵ����
    clock_t startTime,endTime;
    startTime = clock();
    ClusterAnalysis1 myClusterAnalysis;
    myClusterAnalysis.Init(radius,minPTs);
    int temp_noise_num = myClusterAnalysis.DoDBSCANRecursive();
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    int temp_cluster = myClusterAnalysis.WriteToFile();
    correct(data1_result, myClusterAnalysis.data_cluster);
    cout<<"�������:"<< temp_cluster<<";�뾶:"<<radius<<";����ֵ:"<<temp_noise_num<<";��������С�����:"<<minPTs<<endl;
}
void data2_DBSCAN()
{
    cout<<"----------------DBSCAN��data2���ݼ��е�Ӧ��-------------------"<<endl;
    char datafile[50] = " ";
    char resultfile[50] = " ";
    double radius = 5;//600�뾶
    int minPTs = 1;//18��������С���ݵ����
    clock_t startTime,endTime;
    startTime = clock();
    ClusterAnalysis2 myClusterAnalysis;  //�����㷨��������
    myClusterAnalysis.Init(datafile,radius,minPTs);	//ָ���뾶����������С���ݵ����
    int temp_noise_num = myClusterAnalysis.DoDBSCANRecursive();//ִ�о����㷨
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    int temp_cluster = myClusterAnalysis.WriteToFile(resultfile);
    cout<<"�������:"<< temp_cluster<<";�뾶:"<<radius<<";����ֵ:"<<temp_noise_num<<";��������С�����:"<<minPTs<<endl;
    correct(data2_result, myClusterAnalysis.data_cluster);
}
void data3_DBSCAN()
{
    cout<<"----------------DBSCAN��data3���ݼ��е�Ӧ��-------------------"<<endl;
    char datafile[50] = " ";
    char resultfile[50] = " ";
    double radius = 1100;//600�뾶
    int minPTs = 1;//18��������С���ݵ����
    clock_t startTime,endTime;
    startTime = clock();
    ClusterAnalysis3 myClusterAnalysis;  //�����㷨��������
    myClusterAnalysis.Init(datafile,radius,minPTs);	//ָ���뾶����������С���ݵ����
    int temp_noise_num = myClusterAnalysis.DoDBSCANRecursive();//ִ�о����㷨
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    int temp_cluster = myClusterAnalysis.WriteToFile(resultfile);
    correct(data3_result, myClusterAnalysis.data_cluster);
    cout<<"�������:"<< temp_cluster<<";�뾶:"<<radius<<";����ֵ:"<<temp_noise_num<<";��������С�����:"<<minPTs<<endl;
}

//�����������ļ�����.h������ά�ȣ�Point.h������ά��
void data1_kmeans_plus(){
    cout<<"----------------Kmeans++��data1���ݼ��е�Ӧ��-------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    KMeans_plus1<> km;
    vector<KmPoint1<>> pts, outCents;
    int k = 109; //������
    vector<vector<KmPoint1<>>> outPts;
    km.dataGenerator("dataset/dataset1_vec.csv", 10, pts);
    km.kmcluster(pts, k, outCents, outPts);
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    km.serialize(outPts);
    correct(data1_result, km.data_cluster);
}
void data2_kmeans_plus(){
    cout<<"----------------Kmeans++��data2���ݼ��е�Ӧ��-------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    KMeans_plus2<> km;
    vector<KmPoint2<>> pts, outCents;
    int k = 16; //������
    vector<vector<KmPoint2<>>> outPts;
    km.dataGenerator("dataset/dataset2_vec.csv", 10, pts);
    km.kmcluster(pts, k, outCents, outPts);
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    km.serialize(outPts);
    correct(data2_result, km.data_cluster);
}
void data3_kmeans_plus(){
    cout<<"----------------Kmeans++��data3���ݼ��е�Ӧ��-------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    KMeans_plus3<> km;
    vector<KmPoint3<>> pts, outCents;
    int k = 2; //������
    vector<vector<KmPoint3<>>> outPts;
    km.dataGenerator("dataset/dataset3_t.csv", 10, pts);
    km.kmcluster(pts, k, outCents, outPts);
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    km.serialize(outPts);
    correct(data3_result, km.data_cluster);
}


int main() {
    cout<<"---------------------------���������ʼ---------------------------"<<endl;
    data1_pro();
    data2_pro();
    data3_pro();

    data1_kmeans();
    data2_kmeans();
    data3_kmeans();

    data1_cure();
    data2_cure();
    data3_cure();

    data1_DBSCAN();
    data2_DBSCAN(); //����totalʱ�ᱨ��(�Ѽ�����������Ϊ-1�����
    data3_DBSCAN();

    data1_kmeans_plus();
    data2_kmeans_plus();
    data3_kmeans_plus(); //����totalʱ�ᱨ��(�ѽ��)
    cout<<"---------------------------�����������---------------------------"<<endl;
    return 0;
}
