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
//#include "Hopkins.h"


using namespace std;


vector<vector<double>> data1_content;
vector<string> data1_result;
vector<vector<double>> data2_content;
vector<string> data2_result;
vector<vector<double>> data3_content;
vector<string> data3_result;


//�ⲿָ���һ�ԣ�ͬһ����ֻ��ͬһ��ǩ�������ԣ�ͬһ��ǩ�ܱ�������ͬһ����
//�ڲ�ָ������ϵ��
vector<int> get_datacluster(vector<vector<int>> cluster_data, int data_num){
    vector<int> data_cluster(data_num);
    for(int i = 0; i < cluster_data.size(); i++){
        for(int j = 0; j < cluster_data[i].size(); j++){
            data_cluster[cluster_data[i][j]] = i;
        }
    }
    return data_cluster;
}

void correct(vector<string> data_result, vector<int> data_cluster){
    cout << "data_result.size = " << data_result.size() << endl;
    cout << "data_cluster.size = " << data_cluster.size() << endl;
    Correct cor(data_result, data_cluster);
    double one = cor.get_one() * 100;
    double total = cor.get_total() * 100;
    cout << "���ξ���Ĺ�һ��: " << one << '%' << endl;
    cout << "���ξ����������: " << total << '%' << endl;
}

//55.162s
void data1_pro(){
    ifstream fin("dataset/dataset1_vec.csv"); //���ļ�������
    string line;
    /*
    while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
    {
        if(data1_content.size() >= 1000) break;
        istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
        vector<double> fields; //����һ���ַ�������
        string field;
        while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
        {
            fields.push_back(stod(field)); //���ոն�ȡ���ַ�����ӵ�����fields��
        }
        data1_content.push_back(fields);
    }
    */
    fin.close();

    fin.open("dataset/dataset1_t.csv");
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
    cout << "data1 result count = " << memo.size() << endl;
    fin.close();
}
//63.503s
void data2_pro(){
    clock_t startTime,endTime;
    startTime = clock();
    ifstream fin("dataset/dataset2_vec.csv"); //���ļ�������
    string line;
    /*
    while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
    {
        istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
        vector<double> fields; //����һ���ַ�������
        string field;
        while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
        {
            fields.push_back(stod(field)); //���ոն�ȡ���ַ�����ӵ�����fields��
        }
        data2_content.push_back(fields);
    }
    */
    fin.close();
    fin.open("dataset/dataset2_t.csv");
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
    cout << "data2 result count = " << memo.size() << endl;
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
    vector<Cluster> clusters_out = kmeans.runserver(200, 100); //��ε���ֱ�������������Ǿ�������͵�������
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
    vector<Cluster> clusters_out = kmeans.runserver(16, 1000); //��ε���ֱ�������������Ǿ�������͵�������
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    vector<vector<double>> out_centroid;
    //cluster_out����һ��k������������ɵĶ�ά���飬ÿ��clusters_out[i]�����һ�����飬��������������������
    /*
    for (uint i = 0; i < clusters_out.size(); i++){
        vector<double> temple;
        cout << "Cluster " << i << " :" << endl;
        cout << "\t" << "Centroid: " << "\n\t\t[ ";
        for (uint j = 0; j < clusters_out[i].centroid.size(); j++){
            cout << clusters_out[i].centroid[j] << " ";
            temple.push_back(clusters_out[i].centroid[j]);
        }
        cout << "]" << endl;
        out_centroid.push_back(temple);
    }
     */
    kmeans.show_result();
    correct(data2_result, kmeans.data_cluster);
}
void data3_kmeans(){
    clock_t startTime,endTime;
    cout<<"----------------Kmeans��data3�е�Ӧ��---------------------"<<endl;
    startTime = clock();
    Kmeans kmeans;
    kmeans.loaddata("dataset/dataset3_vec.csv");
    vector<Cluster> clusters_out = kmeans.runserver(5, 100); //��ε���ֱ�������������Ǿ�������͵�������
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    vector<vector<double>> out_centroid;
    //cluster_out����һ��k������������ɵĶ�ά���飬ÿ��clusters_out[i]�����һ�����飬��������������������
    /*
    for (uint i = 0; i < clusters_out.size(); i++){
        vector<double> temple;
        cout << "Cluster " << i << " :" << endl;
        cout << "\t" << "Centroid: " << "\n\t\t[ ";
        for (uint j = 0; j < clusters_out[i].centroid.size(); j++){
            cout << clusters_out[i].centroid[j] << " ";
            temple.push_back(clusters_out[i].centroid[j]);
        }
        cout << "]" << endl;
        out_centroid.push_back(temple);
    }
    */
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
    double radius = 0.5;//�뾶
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
    char datafile[50] = "seeddata.txt";
    char resultfile[50] = "redata.txt";
    double radius = 8;//600�뾶
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
    char datafile[50] = "seeddata.txt";
    char resultfile[50] = "redata.txt";
    double radius = 1500;//600�뾶
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
    int k = 200;
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
    int k = 5; //������
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
    int k = 5; //������
    vector<vector<KmPoint3<>>> outPts;
    km.dataGenerator("dataset/dataset3_t.csv", 10, pts);
    km.kmcluster(pts, k, outCents, outPts);
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    km.serialize(outPts);
    correct(data3_result, km.data_cluster);
}


int main() {
    data1_pro();
    data2_pro();
    data3_pro();

    //data1_kmeans();
    //data2_kmeans();
    //data3_kmeans();
    //cout << "hello world" << endl;
    //data1_cure();
    //data2_cure();
    //data3_cure();

    //data1_DBSCAN();
    //data2_DBSCAN(); //����totalʱ�ᱨ��(�Ѽ�����������Ϊ-1�����
    //data3_DBSCAN();

    //data1_kmeans_plus();
    //data2_kmeans_plus();
    data3_kmeans_plus(); //����totalʱ�ᱨ��
    //data3_cure();
    //cout << "data1: " << endl;
    //cout << data1_result.size() << endl; //658923
    //cout << data1_content.size() << ',' << data1_content[0].size() << endl;
    //cout << "data2: " << endl;
    //cout <<data2_result.size() << endl; //748093
    //cout << data2_content.size() << ',' << data2_content[0].size() << endl;
    //cout << "data3: " << endl;
    //cout <<data3_result.size() << endl; //11500
    //cout << data3_content.size() << ',' << data3_content[0].size() << endl;
    //cout<<"\n\n\n\n";
    /*
    seedData_DBSCAN();
    cout<<"\n\n\n\n";
    diabetes_Kmeans();
    cout<<"\n\n\n\n";
    diabete_cure();
    cout<<"\n\n\n\n";
    diabete_DBSCAN();
    cout<<"\n\n\n\n";
    jow_kmeans();
    cout<<"\n\n\n\n";
    jow_cure();
    cout<<"\n\n\n\n";
    jow_DBSCAN();
     */
    cout<<"\n---------------------------ִ�н���---------------------------\n";
    return 0;
}
