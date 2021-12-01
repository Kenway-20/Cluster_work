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

const int    NUMPATTERNS3   =  2000; //11500   // ���ݵ�ĸ���
const int       SIZEVECTOR3   =    178; //178     // ���ݼ���ά��
const int        NUMCLUSTERS3   =  2; //2     // ��ĸ���
const int       NUMPRE3      =    3 ; //3   // ��������
const int     SHRINK3      =    1; //1   // ������\



using namespace std;
// ***** ����ṹ���� *****
struct ClustNode3 {
    int          Member[NUMPATTERNS3];  //���е�������
    int          NumMembers;//��ʾ�������ݵ�ĸ���
    double       Means[SIZEVECTOR3];  //��ֵ��
    double       Pre[NUMPRE3][SIZEVECTOR3];//�����
    int          PreMember[NUMPRE3];//��Ϊ������������
    int          closet;  //����Ĵ�
    double       MinDist;//������Ĵ�֮��ľ���
};

class Cure3 {
private:
    //double      Pattern[NUMPATTERNS3][SIZEVECTOR3]; //�洢���ݼ�
    vector<vector<double>>Pattern = vector<vector<double>>(NUMPATTERNS3, vector<double> (SIZEVECTOR3));
    ClustNode3 *p[NUMPATTERNS3];
    void        BuildClustList(); //������ʼ������
    ClustNode3 * Merge(ClustNode3 *, ClustNode3 *); //�ϲ�������
    int         MinClust();    //�ҵ������������
    double      dist(ClustNode3*, ClustNode3 *);//������֮�����̾���
    double      EucNorm(double *,double *);//�����֮��ľ���
    void        SHRINK2Pre(ClustNode3 *);  //���������
    void        updateMinDist();
    void 		updateMinDist(const int w,const int v);
    ClustNode3 * createNode(ClustNode3 *u, ClustNode3 *v);
public:
    Cure3();
    ~Cure3();
    int LoadPatterns();      // �������ݼ�
    void RunCure3();                     // ����Ĺ���
    void ShowClusters();                // ��ʾ������
    vector<int> data_cluster;
};

#endif //COPY_CURE3_H
