//
// Created by LENOVO on 2021/11/22.
//

#ifndef CLUSTER_WORK_DBSCANCLUSTERANALYSIS3_H
#define CLUSTER_WORK_DBSCANCLUSTERANALYSIS3_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iosfwd>
#include <math.h>
#include <vector>
#include <string>
#include "DBSCANDataPoint3.h"
#include "Silhouette.h"
using namespace std;

//�����������
class ClusterAnalysis3
{
private:
    vector<DataPoint3> dadaSets;        //���ݼ���
    unsigned int dimNum;			//ά��
    double radius;                    //�뾶
    unsigned int dataNum;            //��������
    unsigned int minPTs;            //������С���ݸ���
    unsigned long clusterId;        //�ܹ��������
    unsigned long noise_point;    	//���������
    double GetDistance(DataPoint3& dp1, DataPoint3& dp2);                    //���뺯��
    void SetArrivalPoints(DataPoint3& dp);                                //�������ݵ��������б�
    void KeyPointCluster( unsigned long i, unsigned long clusterId );    //�����ݵ������ڵĵ�ִ�о������
public:

    ClusterAnalysis3(){}                    //Ĭ�Ϲ��캯��
    bool Init(char* fileName, double radius, int minPTs);    //��ʼ������
    int DoDBSCANRecursive();            //DBSCAN�ݹ��㷨
    int WriteToFile(char* fileName);    //��������д���ļ�
    vector<int> data_cluster;
};



/*
�����������ʼ������
˵�����������ļ������뾶��������С���ݸ�����Ϣд������㷨�࣬��ȡ�ļ�����������Ϣ����д���㷨�����ݼ�����
������
char* fileName;    //�ļ���
double radius;    //�뾶
int minPTs;        //������С���ݸ���
����ֵ�� true;    */
bool ClusterAnalysis3::Init(char* fileName, double radius, int minPTs)
{
    this->radius = radius;        //���ð뾶
    this->minPTs = minPTs;        //����������С���ݸ���
    this->dimNum = DIME_NUM3;    //��������ά��
    ifstream fin("dataset/dataset3_t.csv"); //���ļ�������
    if (! fin.is_open())                //���ļ��Ѿ����򿪣���������Ϣ
    {
        cout << "Error opening file\n";    //���������Ϣ
        exit (-1);                        //�����˳�
    }
    unsigned long i=0;            //���ݸ���ͳ��
    string line;
    bool flag = true;
    while (getline(fin, line)){   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
        if(flag){
            flag = false;
            continue;
        }
        //if(i >= 1000) break; //�����ü������ݹ�ģ�����.csv�ļ��Ѿ�����ÿ���ֱ��ȥ����һ��
        istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
        DataPoint3 tempDP;                //��ʱ���ݵ����
        string field;
        vector<double> tempDimData;
        bool flag2 = true;
        while (getline(sin, field, ',')){ //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
            if(flag2){
                flag2 = false;
                continue;
            }
            if(tempDimData.size() >= 178) break;
            tempDimData.push_back(stod(field)); //���ոն�ȡ���ַ�����ӵ�����fields��
        }

        tempDP.SetDimension(tempDimData);    //��ά����Ϣ�������ݵ������
        tempDP.SetDpId(i);                    //�����ݵ����ID����Ϊi
        tempDP.SetVisited(false);            //���ݵ����isVisited����Ϊfalse
        tempDP.SetClusterId(-1);            //����Ĭ�ϴ�IDΪ-1
        dadaSets.push_back(tempDP);            //������ѹ�����ݼ�������
        i++;        //����+1
    }
    cout << dadaSets.size() << endl;
    fin.close();
    dataNum =i;            //�������ݶ��󼯺ϴ�СΪi
    for(unsigned long k=0; k<dataNum;k++)
    {
        SetArrivalPoints(dadaSets[k]);            //�������ݵ������ڶ���
    }
    return true;    //����
}

/*
���������Ѿ��������㷨��������ݼ���д���ļ�
˵�������Ѿ���������д���ļ�
������
char* fileName;    //Ҫд����ļ���
����ֵ�� true    */
int ClusterAnalysis3::WriteToFile(char* fileName )
{
    Silhouette sil(clusterId, DIME_NUM3, dataNum);
    for(int i = 0;i< dataNum;i++)
    {
        if(dadaSets[i].GetClusterId() != -1) {
            sil.addClusterData(dadaSets[i].GetClusterId(), dadaSets[i].GetDimension(), i);
            data_cluster.push_back(dadaSets[i].GetClusterId());
        }
    }
    sil.showCluster();
    double res = sil.calSilhouette();
    cout<<"\n���������"<<res<<endl;
    return  clusterId;
}

/*
�������������ݵ��������б�
˵�����������ݵ��������б�
������
����ֵ�� true;    */
void ClusterAnalysis3::SetArrivalPoints(DataPoint3& dp)
{
    for(unsigned long i=0; i<dataNum; i++)                //��ÿ�����ݵ�ִ��
    {
        double distance =GetDistance(dadaSets[i], dp);//��ȡ���ض���֮��ľ���
        //cout << dp.GetDpId()<<"to"<<i<<"is"<<distance<< endl;
        if(distance <= radius && i!=dp.GetDpId())        //������С�ڰ뾶�������ض����id��dp��id��ִͬ��
            dp.GetArrivalPoints().push_back(i);            //���ض���idѹ��dp�������б���
    }

    if(dp.GetArrivalPoints().size() >= minPTs)            //��dp���������ݵ�������> minPTsִ��
    {
        dp.SetKey(true);    //��dp���Ķ����־λ��Ϊtrue
        return;                //����
    }
    dp.SetKey(false);    //���Ǻ��Ķ�����dp���Ķ����־λ��Ϊfalse
}


/*
������ִ�о������
˵����ִ�о������
������
����ֵ�� true;    */
int ClusterAnalysis3::DoDBSCANRecursive()
{
    clusterId=0;
    noise_point = 0;                        //����id��������ʼ��Ϊ0
    for(unsigned long i=0; i<dataNum;i++)            //��ÿһ�����ݵ�ִ��
    {
        DataPoint3& dp=dadaSets[i];                    //ȡ����i�����ݵ����
        if(!dp.isVisited() && dp.IsKey())            //������û�����ʹ��������Ǻ��Ķ���ִ��
        {
            dp.SetClusterId(clusterId);                //���øö���������IDΪclusterId
            dp.SetVisited(true);                    //���øö����ѱ����ʹ�
            KeyPointCluster(i,clusterId);            //�Ըö��������ڵ���о���
            clusterId++;                            //clusterId����1
        }
        /*if(!dp.IsKey()) {
            cout <<"������"<<i<< endl;
            k++;
        }*/
    }
    for(unsigned long j=0; j<dataNum;j++)
    {
        DataPoint3& dptemp=dadaSets[j];
        if(dptemp.GetClusterId()!=-1); //cout << "���ݵ�"<< dptemp.GetDpId()<< " ����IDΪ"<< dptemp.GetClusterId() << endl;
        else
        {
            //cout <<"������"<<j<< endl;
            noise_point++;
        }
    }
    return noise_point;    //����
}

/*
�����������ݵ������ڵĵ�ִ�о������
˵�������õݹ�ķ�����������Ⱦ�������
������
unsigned long dpID;            //���ݵ�id
unsigned long clusterId;    //���ݵ�������id
����ֵ�� void;    */
void ClusterAnalysis3::KeyPointCluster(unsigned long dpID, unsigned long clusterId )
{
    DataPoint3& srcDp = dadaSets[dpID];        //��ȡ���ݵ����
    if(!srcDp.IsKey())    return;
    vector<unsigned long>& arrvalPoints = srcDp.GetArrivalPoints();        //��ȡ���������ڵ�ID�б�
    for(unsigned long i=0; i<arrvalPoints.size(); i++)
    {
        DataPoint3& desDp = dadaSets[arrvalPoints[i]];    //��ȡ�����ڵ����ݵ�
        if(!desDp.isVisited())                            //���ö���û�б����ʹ�ִ��
        {
            //cout << "���ݵ�"<< desDp.GetDpId()<<" ����IDΪ" <<clusterId << endl;
            desDp.SetClusterId(clusterId);        //���øö��������ص�IDΪclusterId�������ö����������
            desDp.SetVisited(true);                //���øö����ѱ�����
            if(desDp.IsKey())                    //���ö����Ǻ��Ķ���
            {
                KeyPointCluster(desDp.GetDpId(),clusterId);    //�ݹ�ضԸ���������ݵ������ڵĵ�ִ�о������������������ȷ���
            }
        }
    }
}

//�����ݵ�֮�����
/*
��������ȡ�����ݵ�֮�����
˵������ȡ�����ݵ�֮���ŷʽ����
������
DataPoint& dp1;        //���ݵ�1
DataPoint& dp2;        //���ݵ�2
����ֵ�� double;    //����֮��ľ���        */
double ClusterAnalysis3::GetDistance(DataPoint3& dp1, DataPoint3& dp2)
{
    double distance =0;        //��ʼ������Ϊ0
    for(int i=0; i < DIME_NUM3; i++)    //������ÿһά����ִ��
    {
        distance += pow(dp1.GetDimension()[i] - dp2.GetDimension()[i],2);    //����+ÿһά���ƽ��
    }
    return pow(distance,0.5);        //���������ؾ���
}




#endif //CLUSTER_WORK_DBSCANCLUSTERANALYSIS3_H
