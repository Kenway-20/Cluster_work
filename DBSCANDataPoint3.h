//
// Created by LENOVO on 2021/11/22.
//

#ifndef CLUSTER_WORK_DBSCANDATAPOINT3_H
#define CLUSTER_WORK_DBSCANDATAPOINT3_H
#include <vector>

using namespace std;


const int DIME_NUM3 = 178;          //数据维度，全局常量


//数据点类型
class DataPoint3
{
private:
    unsigned long dpID;                //数据点ID
    double dimension[DIME_NUM3];        //维度数据
    long clusterId;                    //所属聚类ID
    bool isKey;                        //是否核心对象
    bool visited;                    //是否已访问
    vector<unsigned long> arrivalPoints;    //领域数据点id列表
public:
    DataPoint3();                                                    //默认构造函数
    DataPoint3(unsigned long dpID, double* dimension , bool isKey);    //构造函数

    unsigned long GetDpId();                //GetDpId方法
    void SetDpId(unsigned long dpID);        //SetDpId方法
    double* GetDimension();                    //GetDimension方法
    void SetDimension(vector<double> dimension);    //SetDimension方法
    bool IsKey();                            //GetIsKey方法
    void SetKey(bool isKey);                //SetKey方法
    bool isVisited();                        //GetIsVisited方法
    void SetVisited(bool visited);            //SetIsVisited方法
    long GetClusterId();                    //GetClusterId方法
    void SetClusterId(long classId);        //SetClusterId方法
    vector<unsigned long>& GetArrivalPoints();    //GetArrivalPoints方法
};

//默认构造函数
DataPoint3::DataPoint3()
{
}

//构造函数
DataPoint3::DataPoint3(unsigned long dpID, double* dimension , bool isKey): isKey(isKey), dpID(dpID)
{
    //传递每维的维度数据
    for(int i=0; i < DIME_NUM3; i++)
    {
        this->dimension[i]=dimension[i];
    }
}

//设置维度数据
void DataPoint3::SetDimension(vector<double> dimension)
{
    for(int i=0; i < DIME_NUM3; i++)
    {
        this->dimension[i]=dimension[i];
    }
}

//获取维度数据
double* DataPoint3::GetDimension()
{
    return this->dimension;
}

//获取是否为核心对象
bool DataPoint3::IsKey()
{
    return this->isKey;
}

//设置核心对象标志
void DataPoint3::SetKey(bool isKey)
{
    this->isKey = isKey;
}

//获取DpId方法
unsigned long DataPoint3::GetDpId()
{
    return this->dpID;
}

//设置DpId方法
void DataPoint3::SetDpId(unsigned long dpID)
{
    this->dpID = dpID;
}

//GetIsVisited方法
bool DataPoint3::isVisited()
{
    return this->visited;
}


//SetIsVisited方法
void DataPoint3::SetVisited(bool visited )
{
    this->visited = visited;
}

//GetClusterId方法
long DataPoint3::GetClusterId()
{
    return this->clusterId;
}

//GetClusterId方法
void DataPoint3::SetClusterId(long clusterId )
{
    this->clusterId = clusterId;
}

//GetArrivalPoints方法
vector<unsigned long>& DataPoint3::GetArrivalPoints()
{
    return arrivalPoints;
}


#endif //CLUSTER_WORK_DBSCANDATAPOINT3_H
