//
// Created by LENOVO on 2021/11/21.
//

#ifndef CLUSTER_WORK_CURE2_H
#define CLUSTER_WORK_CURE2_H
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <vector>

/*
#define         SUCCESS         1
#define         FAILURE         0
#define         TRUE            1
#define         FALSE           0
#define         NUMPATTERNS3     10   // 数据点的个数
#define         SIZEVECTOR3      2     // 数据集的维数
#define         NUMCLUSTERS3     2     // 类的个数
#define         NUMPRE3          3    // 代表点个数
#define         SHRINK3          0.5   // 收缩率
*/

#define         SUCCESS         1
#define         FAILURE         0
#define         TRUE            1
#define         FALSE           0

const int    NUMPATTERNS2   =  5000; //210   // 数据点的个数
const int       SIZEVECTOR2   =    128; //2     // 数据集的维数
const int        NUMCLUSTERS2   =  16; //3     // 类的个数
const int       NUMPRE2      =    3 ; //3   // 代表点个数
const int     SHRINK2      =    1 ; //1   // 收缩率



using namespace std;
// ***** 定义结构和类 *****
struct ClustNode2 {
    int          Member[NUMPATTERNS2];  //类中的数据项
    int          NumMembers;//表示类中数据点的个数
    double       Means[SIZEVECTOR2];  //均值点
    double       Pre[NUMPRE2][SIZEVECTOR2];//代表点
    int          PreMember[NUMPRE2];//作为代表点的数据项
    int          closet;  //最近的簇
    double       MinDist;//与最近的簇之间的距离
};

class Cure2 {
private:
    //double      Pattern[NUMPATTERNS2][SIZEVECTOR2]; //存储数据集
    vector<vector<double>>Pattern = vector<vector<double>>(NUMPATTERNS2, vector<double> (SIZEVECTOR2));
    ClustNode2 *p[NUMPATTERNS2];
    void        BuildClustList(); //建立初始簇链表
    ClustNode2 * Merge(ClustNode2 *, ClustNode2 *); //合并两个簇
    int         MinClust();    //找到最近的两个簇
    double      dist(ClustNode2*, ClustNode2 *);//两个簇之间的最短距离
    double      EucNorm(double *,double *);//代表点之间的距离
    void        SHRINK2Pre(ClustNode2 *);  //收缩代表点
    void        updateMinDist();
    void 		updateMinDist(const int w,const int v);
    ClustNode2 * createNode(ClustNode2 *u, ClustNode2 *v);
public:
    Cure2();
    ~Cure2();
    int LoadPatterns();      // 处理数据集
    void RunCure2();                     // 聚类的过程
    void ShowClusters();                // 显示聚类结果
    vector<int> data_cluster;
};

#endif //CLUSTER_WORK_CURE2_H
