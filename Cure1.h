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

const int    NUMPATTERNS1   =  5000; //658923  // ���ݵ�ĸ���
const int       SIZEVECTOR1   =    128; //100     // ���ݼ���ά��
const int        NUMCLUSTERS1   =  109; //263     // ��ĸ���
const int       NUMPRE1      =    3 ; //3   // ��������
const int     SHRINK1      =    1 ; //1   // ������



using namespace std;
// ***** ����ṹ���� *****
struct ClustNode1 {
    vector<int>          Member = vector<int> (NUMPATTERNS1);  //���е�������
    int          NumMembers;//��ʾ�������ݵ�ĸ���
    double       Means[SIZEVECTOR1];  //��ֵ��
    double       Pre[NUMPRE1][SIZEVECTOR1];//�����
    int          PreMember[NUMPRE1];//��Ϊ������������
    int          closet;  //����Ĵ�
    double       MinDist;//������Ĵ�֮��ľ���
};

class Cure1 {
private:
    //double      Pattern[NUMPATTERNS1][SIZEVECTOR1]; //�洢���ݼ�
    vector<vector<double>>Pattern = vector<vector<double>>(NUMPATTERNS1, vector<double> (SIZEVECTOR1));
    vector<ClustNode1*> p = vector<ClustNode1*> (NUMPATTERNS1);
    void        BuildClustList(); //������ʼ������
    ClustNode1 * Merge(ClustNode1 *, ClustNode1 *); //�ϲ�������
    int         MinClust();    //�ҵ������������
    double      dist(ClustNode1*, ClustNode1 *);//������֮�����̾���
    double      EucNorm(double *,double *);//�����֮��ľ���
    void        SHRINK2Pre(ClustNode1 *);  //���������
    void        updateMinDist();
    void 		updateMinDist(const int w,const int v);
    ClustNode1 * createNode(ClustNode1 *u, ClustNode1 *v);
public:
    Cure1();
    ~Cure1();
    int LoadPatterns();      // �������ݼ�
    void RunCure1();                     // ����Ĺ���
    void ShowClusters();                // ��ʾ������
    vector<vector<double>> get_Pattern();
    vector<int> data_cluster;
};

#endif //DATA_CLASS_CURE1_H
