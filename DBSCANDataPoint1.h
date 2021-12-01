//
// Created by LENOVO on 2021/11/23.
//

#ifndef DATA_CLASS_DBSCANDATAPOINT1_H
#define DATA_CLASS_DBSCANDATAPOINT1_H
//
// Created by LENOVO on 2021/11/22.
//
#include <vector>

using namespace std;


const int DIME_NUM1 = 128;          //����ά�ȣ�ȫ�ֳ���


//���ݵ�����
class DataPoint1
{
private:
    unsigned long dpID;                //���ݵ�ID
    double dimension[DIME_NUM1];        //ά������
    long clusterId;                    //��������ID
    bool isKey;                        //�Ƿ���Ķ���
    bool visited;                    //�Ƿ��ѷ���
    vector<unsigned long> arrivalPoints;    //�������ݵ�id�б�
public:
    DataPoint1();                                                    //Ĭ�Ϲ��캯��
    DataPoint1(unsigned long dpID, double* dimension , bool isKey);    //���캯��

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
DataPoint1::DataPoint1()
{
}

//���캯��
DataPoint1::DataPoint1(unsigned long dpID, double* dimension , bool isKey): isKey(isKey), dpID(dpID)
{
    //����ÿά��ά������
    for(int i=0; i < DIME_NUM1; i++)
    {
        this->dimension[i]=dimension[i];
    }
}

//����ά������
void DataPoint1::SetDimension(vector<double> dimension)
{
    for(int i=0; i < DIME_NUM1; i++)
    {
        this->dimension[i]=dimension[i];
    }
}

//��ȡά������
double* DataPoint1::GetDimension()
{
    return this->dimension;
}

//��ȡ�Ƿ�Ϊ���Ķ���
bool DataPoint1::IsKey()
{
    return this->isKey;
}

//���ú��Ķ����־
void DataPoint1::SetKey(bool isKey)
{
    this->isKey = isKey;
}

//��ȡDpId����
unsigned long DataPoint1::GetDpId()
{
    return this->dpID;
}

//����DpId����
void DataPoint1::SetDpId(unsigned long dpID)
{
    this->dpID = dpID;
}

//GetIsVisited����
bool DataPoint1::isVisited()
{
    return this->visited;
}


//SetIsVisited����
void DataPoint1::SetVisited(bool visited )
{
    this->visited = visited;
}

//GetClusterId����
long DataPoint1::GetClusterId()
{
    return this->clusterId;
}

//GetClusterId����
void DataPoint1::SetClusterId(long clusterId )
{
    this->clusterId = clusterId;
}

//GetArrivalPoints����
vector<unsigned long>& DataPoint1::GetArrivalPoints()
{
    return arrivalPoints;
}


#endif //DATA_CLASS_DBSCANDATAPOINT1_H
