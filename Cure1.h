//
// Created by LENOVO on 2021/11/22.
//

#ifndef DATA_CLASS_CURE1_H
#define DATA_CLASS_CURE1_H
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

const int    NUMPATTERNS1   =  5000; //658923  // 数据点的个数
const int       SIZEVECTOR1   =    128; //100     // 数据集的维数
const int        NUMCLUSTERS1   =  109; //263     // 类的个数
const int       NUMPRE1      =    3 ; //3   // 代表点个数
const int     SHRINK1      =    1 ; //1   // 收缩率



using namespace std;
// ***** 定义结构和类 *****
struct ClustNode1 {
    vector<int>          Member = vector<int> (NUMPATTERNS1);  //类中的数据项
    int          NumMembers;//表示类中数据点的个数
    double       Means[SIZEVECTOR1];  //均值点
    double       Pre[NUMPRE1][SIZEVECTOR1];//代表点
    int          PreMember[NUMPRE1];//作为代表点的数据项
    int          closet;  //最近的簇
    double       MinDist;//与最近的簇之间的距离
};

class Cure1 {
private:
    //double      Pattern[NUMPATTERNS1][SIZEVECTOR1]; //存储数据集
    vector<vector<double>>Pattern = vector<vector<double>>(NUMPATTERNS1, vector<double> (SIZEVECTOR1));
    vector<ClustNode1*> p = vector<ClustNode1*> (NUMPATTERNS1);
    void        BuildClustList(); //建立初始簇链表
    ClustNode1 * Merge(ClustNode1 *, ClustNode1 *); //合并两个簇
    int         MinClust();    //找到最近的两个簇
    double      dist(ClustNode1*, ClustNode1 *);//两个簇之间的最短距离
    double      EucNorm(double *,double *);//代表点之间的距离
    void        SHRINK2Pre(ClustNode1 *);  //收缩代表点
    void        updateMinDist();
    void 		updateMinDist(const int w,const int v);
    ClustNode1 * createNode(ClustNode1 *u, ClustNode1 *v);
public:
    Cure1();
    ~Cure1();
    int LoadPatterns();      // 处理数据集
    void RunCure1();                     // 聚类的过程
    void ShowClusters();                // 显示聚类结果
    vector<vector<double>> get_Pattern();
    vector<int> data_cluster;
};

#endif //DATA_CLASS_CURE1_H
