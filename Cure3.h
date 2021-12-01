#ifndef COPY_CURE3_H
#define COPY_CURE3_H

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

const int    NUMPATTERNS3   =  2000; //11500   // 数据点的个数
const int       SIZEVECTOR3   =    178; //178     // 数据集的维数
const int        NUMCLUSTERS3   =  2; //2     // 类的个数
const int       NUMPRE3      =    3 ; //3   // 代表点个数
const int     SHRINK3      =    1; //1   // 收缩率\



using namespace std;
// ***** 定义结构和类 *****
struct ClustNode3 {
    int          Member[NUMPATTERNS3];  //类中的数据项
    int          NumMembers;//表示类中数据点的个数
    double       Means[SIZEVECTOR3];  //均值点
    double       Pre[NUMPRE3][SIZEVECTOR3];//代表点
    int          PreMember[NUMPRE3];//作为代表点的数据项
    int          closet;  //最近的簇
    double       MinDist;//与最近的簇之间的距离
};

class Cure3 {
private:
    //double      Pattern[NUMPATTERNS3][SIZEVECTOR3]; //存储数据集
    vector<vector<double>>Pattern = vector<vector<double>>(NUMPATTERNS3, vector<double> (SIZEVECTOR3));
    ClustNode3 *p[NUMPATTERNS3];
    void        BuildClustList(); //建立初始簇链表
    ClustNode3 * Merge(ClustNode3 *, ClustNode3 *); //合并两个簇
    int         MinClust();    //找到最近的两个簇
    double      dist(ClustNode3*, ClustNode3 *);//两个簇之间的最短距离
    double      EucNorm(double *,double *);//代表点之间的距离
    void        SHRINK2Pre(ClustNode3 *);  //收缩代表点
    void        updateMinDist();
    void 		updateMinDist(const int w,const int v);
    ClustNode3 * createNode(ClustNode3 *u, ClustNode3 *v);
public:
    Cure3();
    ~Cure3();
    int LoadPatterns();      // 处理数据集
    void RunCure3();                     // 聚类的过程
    void ShowClusters();                // 显示聚类结果
    vector<int> data_cluster;
};

#endif //COPY_CURE3_H
