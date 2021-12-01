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
#define         NUMPATTERNS3     10   // ���ݵ�ĸ���
#define         SIZEVECTOR3      2     // ���ݼ���ά��
#define         NUMCLUSTERS3     2     // ��ĸ���
#define         NUMPRE3          3    // ��������
#define         SHRINK3          0.5   // ������
*/

#define         SUCCESS         1
#define         FAILURE         0
#define         TRUE            1
#define         FALSE           0

const int    NUMPATTERNS2   =  5000; //210   // ���ݵ�ĸ���
const int       SIZEVECTOR2   =    128; //2     // ���ݼ���ά��
const int        NUMCLUSTERS2   =  16; //3     // ��ĸ���
const int       NUMPRE2      =    3 ; //3   // ��������
const int     SHRINK2      =    1 ; //1   // ������



using namespace std;
// ***** ����ṹ���� *****
struct ClustNode2 {
    int          Member[NUMPATTERNS2];  //���е�������
    int          NumMembers;//��ʾ�������ݵ�ĸ���
    double       Means[SIZEVECTOR2];  //��ֵ��
    double       Pre[NUMPRE2][SIZEVECTOR2];//�����
    int          PreMember[NUMPRE2];//��Ϊ������������
    int          closet;  //����Ĵ�
    double       MinDist;//������Ĵ�֮��ľ���
};

class Cure2 {
private:
    //double      Pattern[NUMPATTERNS2][SIZEVECTOR2]; //�洢���ݼ�
    vector<vector<double>>Pattern = vector<vector<double>>(NUMPATTERNS2, vector<double> (SIZEVECTOR2));
    ClustNode2 *p[NUMPATTERNS2];
    void        BuildClustList(); //������ʼ������
    ClustNode2 * Merge(ClustNode2 *, ClustNode2 *); //�ϲ�������
    int         MinClust();    //�ҵ������������
    double      dist(ClustNode2*, ClustNode2 *);//������֮�����̾���
    double      EucNorm(double *,double *);//�����֮��ľ���
    void        SHRINK2Pre(ClustNode2 *);  //���������
    void        updateMinDist();
    void 		updateMinDist(const int w,const int v);
    ClustNode2 * createNode(ClustNode2 *u, ClustNode2 *v);
public:
    Cure2();
    ~Cure2();
    int LoadPatterns();      // �������ݼ�
    void RunCure2();                     // ����Ĺ���
    void ShowClusters();                // ��ʾ������
    vector<int> data_cluster;
};

#endif //CLUSTER_WORK_CURE2_H
