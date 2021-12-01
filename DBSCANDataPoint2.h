//
// Created by LENOVO on 2021/11/23.
//

#ifndef DATA_CLASS_DBSCANDATAPOINT2_H
#define DATA_CLASS_DBSCANDATAPOINT2_H
#include <vector>

using namespace std;


const int DIME_NUM2 = 128;          //����ά�ȣ�ȫ�ֳ���


//���ݵ�����
class DataPoint2
{
private:
    unsigned long dpID;                //���ݵ�ID
    double dimension[DIME_NUM2];        //ά������
    long clusterId;                    //��������ID
    bool isKey;                        //�Ƿ���Ķ���
    bool visited;                    //�Ƿ��ѷ���
    vector<unsigned long> arrivalPoints;    //�������ݵ�id�б�
public:
    DataPoint2();                                                    //Ĭ�Ϲ��캯��
    DataPoint2(unsigned long dpID, double* dimension , bool isKey);    //���캯��

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
DataPoint2::DataPoint2()
{
}

//���캯��
DataPoint2::DataPoint2(unsigned long dpID, double* dimension , bool isKey): isKey(isKey), dpID(dpID)
{
    //����ÿά��ά������
    for(int i=0; i < DIME_NUM2; i++)
    {
        this->dimension[i]=dimension[i];
    }
}

//����ά������
void DataPoint2::SetDimension(vector<double> dimension)
{
    for(int i=0; i < DIME_NUM2; i++)
    {
        this->dimension[i]=dimension[i];
    }
}

//��ȡά������
double* DataPoint2::GetDimension()
{
    return this->dimension;
}

//��ȡ�Ƿ�Ϊ���Ķ���
bool DataPoint2::IsKey()
{
    return this->isKey;
}

//���ú��Ķ����־
void DataPoint2::SetKey(bool isKey)
{
    this->isKey = isKey;
}

//��ȡDpId����
unsigned long DataPoint2::GetDpId()
{
    return this->dpID;
}

//����DpId����
void DataPoint2::SetDpId(unsigned long dpID)
{
    this->dpID = dpID;
}

//GetIsVisited����
bool DataPoint2::isVisited()
{
    return this->visited;
}


//SetIsVisited����
void DataPoint2::SetVisited(bool visited )
{
    this->visited = visited;
}

//GetClusterId����
long DataPoint2::GetClusterId()
{
    return this->clusterId;
}

//GetClusterId����
void DataPoint2::SetClusterId(long clusterId )
{
    this->clusterId = clusterId;
}

//GetArrivalPoints����
vector<unsigned long>& DataPoint2::GetArrivalPoints()
{
    return arrivalPoints;
}

#endif //DATA_CLASS_DBSCANDATAPOINT2_H
