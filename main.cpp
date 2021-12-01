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


//外部指标均一性：同一类中只含同一标签、完整性：同一标签能被包含到同一类中
//内部指标轮廓系数
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
    cout << "本次聚类的归一性: " << one << '%' << endl;
    cout << "本次聚类的完整性: " << total << '%' << endl;
}

//55.162s
void data1_pro(){
    ifstream fin("dataset/dataset1_vec.csv"); //打开文件流操作
    string line;
    /*
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        if(data1_content.size() >= 1000) break;
        istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
        vector<double> fields; //声明一个字符串向量
        string field;
        while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
        {
            fields.push_back(stod(field)); //将刚刚读取的字符串添加到向量fields中
        }
        data1_content.push_back(fields);
    }
    */
    fin.close();

    fin.open("dataset/dataset1_t.csv");
    bool flag = true;
    unordered_map<string, int> memo;
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        istringstream sin2(line); //将整行字符串line读入到字符串流istringstream中
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
    ifstream fin("dataset/dataset2_vec.csv"); //打开文件流操作
    string line;
    /*
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
        vector<double> fields; //声明一个字符串向量
        string field;
        while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
        {
            fields.push_back(stod(field)); //将刚刚读取的字符串添加到向量fields中
        }
        data2_content.push_back(fields);
    }
    */
    fin.close();
    fin.open("dataset/dataset2_t.csv");
    bool flag = true;
    unordered_map<string, int> memo;
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        istringstream sin2(line); //将整行字符串line读入到字符串流istringstream中
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
    ifstream fin("dataset/dataset3_t.csv"); //打开文件流操作
    string line;
    bool flag = true;
    unordered_map<string, int> memo;
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        if(flag){
            flag = false;
            continue;
        }
        istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
        vector<double> fields; //声明一个字符串向量
        string field;
        bool flag2 = true;
        while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
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
            fields.push_back(temple); //将刚刚读取的字符串添加到向量fields中
        }
        //data3_content.push_back(fields);
    }
    fin.close();
}

//函数参数：文件名、类数、最大迭代次数
void data1_kmeans(){
    clock_t startTime,endTime;
    cout<<"----------------Kmeans在data1中的应用---------------------"<<endl;
    startTime = clock();
    Kmeans kmeans;
    kmeans.loaddata("dataset/dataset1_vec.csv");
    vector<Cluster> clusters_out = kmeans.runserver(200, 100); //多次迭代直至收敛，参数是聚类个数和迭代次数
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    vector<vector<double>> out_centroid;
    kmeans.show_result();
    correct(data1_result, kmeans.data_cluster);
}
void data2_kmeans(){
    clock_t startTime,endTime;
    cout<<"----------------Kmeans在data2中的应用---------------------"<<endl;
    startTime = clock();
    Kmeans kmeans;
    kmeans.loaddata("dataset/dataset2_vec.csv");
    vector<Cluster> clusters_out = kmeans.runserver(16, 1000); //多次迭代直至收敛，参数是聚类个数和迭代次数
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    vector<vector<double>> out_centroid;
    //cluster_out就是一个k个中心坐标组成的二维数组，每个clusters_out[i]存的是一个数组，数组里面存的是中心坐标
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
    cout<<"----------------Kmeans在data3中的应用---------------------"<<endl;
    startTime = clock();
    Kmeans kmeans;
    kmeans.loaddata("dataset/dataset3_vec.csv");
    vector<Cluster> clusters_out = kmeans.runserver(5, 100); //多次迭代直至收敛，参数是聚类个数和迭代次数
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    vector<vector<double>> out_centroid;
    //cluster_out就是一个k个中心坐标组成的二维数组，每个clusters_out[i]存的是一个数组，数组里面存的是中心坐标
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

//.h文件参数：数据点个数、维数、类数、代表点数、收缩率，.cpp文件参数：文件名
void data1_cure(){
    cout<<"----------------Cure在data1中的应用---------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    Cure1 cure;
    if (cure.LoadPatterns()==FAILURE ){
        cout<<"不能打开输入文件:"<<endl;
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
    cout<<"----------------Cure在data2中的应用---------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    Cure2 cure;
    if (cure.LoadPatterns()==FAILURE ){
        cout<<"不能打开输入文件:"<<endl;
        exit(0);
    }
    cure.RunCure2();
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    cure.ShowClusters();
    correct(data2_result, cure.data_cluster);
}
void data3_cure(){
    cout<<"----------------Cure在data3中的应用---------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    Cure3 cure;
    if (cure.LoadPatterns()==FAILURE ){
        cout<<"不能打开输入文件:"<<endl;
        exit(0);
    }
    cure.RunCure3();
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    cure.ShowClusters();
    correct(data3_result, cure.data_cluster);
}

//函数参数：半径、最小数据点个数，.h参数：文件名，Point.h参数：数据维度
//DBSCAN会自动去除噪声点，所以不能用原有数据规模去最后判断
void data1_DBSCAN()
{
    cout<<"----------------DBSCAN在data1数据集中的应用-------------------"<<endl;
    double radius = 0.5;//半径
    int minPTs = 1;//领域内最小数据点个数
    clock_t startTime,endTime;
    startTime = clock();
    ClusterAnalysis1 myClusterAnalysis;
    myClusterAnalysis.Init(radius,minPTs);
    int temp_noise_num = myClusterAnalysis.DoDBSCANRecursive();
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    int temp_cluster = myClusterAnalysis.WriteToFile();
    correct(data1_result, myClusterAnalysis.data_cluster);
    cout<<"簇类个数:"<< temp_cluster<<";半径:"<<radius<<";噪声值:"<<temp_noise_num<<";领域内最小点个数:"<<minPTs<<endl;
}
void data2_DBSCAN()
{
    cout<<"----------------DBSCAN在data2数据集中的应用-------------------"<<endl;
    char datafile[50] = "seeddata.txt";
    char resultfile[50] = "redata.txt";
    double radius = 8;//600半径
    int minPTs = 1;//18领域内最小数据点个数
    clock_t startTime,endTime;
    startTime = clock();
    ClusterAnalysis2 myClusterAnalysis;  //聚类算法对象声明
    myClusterAnalysis.Init(datafile,radius,minPTs);	//指定半径和领域内最小数据点个数
    int temp_noise_num = myClusterAnalysis.DoDBSCANRecursive();//执行聚类算法
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    int temp_cluster = myClusterAnalysis.WriteToFile(resultfile);
    cout<<"簇类个数:"<< temp_cluster<<";半径:"<<radius<<";噪声值:"<<temp_noise_num<<";领域内最小点个数:"<<minPTs<<endl;
    correct(data2_result, myClusterAnalysis.data_cluster);
}
void data3_DBSCAN()
{
    cout<<"----------------DBSCAN在data3数据集中的应用-------------------"<<endl;
    char datafile[50] = "seeddata.txt";
    char resultfile[50] = "redata.txt";
    double radius = 1500;//600半径
    int minPTs = 1;//18领域内最小数据点个数
    clock_t startTime,endTime;
    startTime = clock();
    ClusterAnalysis3 myClusterAnalysis;  //聚类算法对象声明
    myClusterAnalysis.Init(datafile,radius,minPTs);	//指定半径和领域内最小数据点个数
    int temp_noise_num = myClusterAnalysis.DoDBSCANRecursive();//执行聚类算法
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    int temp_cluster = myClusterAnalysis.WriteToFile(resultfile);
    correct(data3_result, myClusterAnalysis.data_cluster);
    cout<<"簇类个数:"<< temp_cluster<<";半径:"<<radius<<";噪声值:"<<temp_noise_num<<";领域内最小点个数:"<<minPTs<<endl;
}

//函数参数：文件名，.h参数：维度，Point.h参数：维度
void data1_kmeans_plus(){
    cout<<"----------------Kmeans++在data1数据集中的应用-------------------"<<endl;
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
    cout<<"----------------Kmeans++在data2数据集中的应用-------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    KMeans_plus2<> km;
    vector<KmPoint2<>> pts, outCents;
    int k = 5; //聚类数
    vector<vector<KmPoint2<>>> outPts;
    km.dataGenerator("dataset/dataset2_vec.csv", 10, pts);
    km.kmcluster(pts, k, outCents, outPts);
    endTime = clock();
    cout << "Run Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    km.serialize(outPts);
    correct(data2_result, km.data_cluster);
}
void data3_kmeans_plus(){
    cout<<"----------------Kmeans++在data3数据集中的应用-------------------"<<endl;
    clock_t startTime,endTime;
    startTime = clock();
    KMeans_plus3<> km;
    vector<KmPoint3<>> pts, outCents;
    int k = 5; //聚类数
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
    //data2_DBSCAN(); //在算total时会报错(已加入噪声分类为-1解决）
    //data3_DBSCAN();

    //data1_kmeans_plus();
    //data2_kmeans_plus();
    data3_kmeans_plus(); //在算total时会报错
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
    cout<<"\n---------------------------执行结束---------------------------\n";
    return 0;
}
