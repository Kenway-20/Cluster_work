//
// Created by LENOVO on 2021/11/22.
//

#ifndef CLUSTER_WORK_DBSCANDATAPOINT3_H
#define CLUSTER_WORK_DBSCANDATAPOINT3_H
#include <vector>

using namespace std;


const int DIME_NUM3 = 178;          //����ά�ȣ�ȫ�ֳ���


//���ݵ�����
class DataPoint3
{
private:
    unsigned long dpID;                //���ݵ�ID
    double dimension[DIME_NUM3];        //ά������
    long clusterId;                    //��������ID
    bool isKey;                        //�Ƿ���Ķ���
    bool visited;                    //�Ƿ��ѷ���
    vector<unsigned long> arrivalPoints;    //�������ݵ�id�б�
public:
    DataPoint3();                                                    //Ĭ�Ϲ��캯��
    DataPoint3(unsigned long dpID, double* dimension , bool isKey);    //���캯��

    unsigned long GetDpId();                //GetDpId����
    void SetDpId(unsigned long dpID);        //SetDpId����
    double* GetDimension();                    //GetDimension����
    void SetDimension(vector<double> dimension);    //SetDimension����
    bool IsKey();                            //GetIsKey����
    void SetKey(bool isKey);                //SetKey����
    bool isVisited();                        //GetIsVisited����
    void SetVisited(bool visited);            //SetIsVisited����
    long GetClusterId();                    //GetClusterId����
    void SetClusterId(long classId);        //SetClusterId����
    vector<unsigned long>& GetArrivalPoints();    //GetArrivalPoints����
};

//Ĭ�Ϲ��캯��
DataPoint3::DataPoint3()
{
}

//���캯��
DataPoint3::DataPoint3(unsigned long dpID, double* dimension , bool isKey): isKey(isKey), dpID(dpID)
{
    //����ÿά��ά������
    for(int i=0; i < DIME_NUM3; i++)
    {
        this->dimension[i]=dimension[i];
    }
}

//����ά������
void DataPoint3::SetDimension(vector<double> dimension)
{
    for(int i=0; i < DIME_NUM3; i++)
    {
        this->dimension[i]=dimension[i];
    }
}

//��ȡά������
double* DataPoint3::GetDimension()
{
    return this->dimension;
}

//��ȡ�Ƿ�Ϊ���Ķ���
bool DataPoint3::IsKey()
{
    return this->isKey;
}

//���ú��Ķ����־
void DataPoint3::SetKey(bool isKey)
{
    this->isKey = isKey;
}

//��ȡDpId����
unsigned long DataPoint3::GetDpId()
{
    return this->dpID;
}

//����DpId����
void DataPoint3::SetDpId(unsigned long dpID)
{
    this->dpID = dpID;
}

//GetIsVisited����
bool DataPoint3::isVisited()
{
    return this->visited;
}


//SetIsVisited����
void DataPoint3::SetVisited(bool visited )
{
    this->visited = visited;
}

//GetClusterId����
long DataPoint3::GetClusterId()
{
    return this->clusterId;
}

//GetClusterId����
void DataPoint3::SetClusterId(long clusterId )
{
    this->clusterId = clusterId;
}

//GetArrivalPoints����
vector<unsigned long>& DataPoint3::GetArrivalPoints()
{
    return arrivalPoints;
}


#endif //CLUSTER_WORK_DBSCANDATAPOINT3_H
