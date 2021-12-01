//
// Created by LENOVO on 2021/11/19.
//

#include "Silhouette.h"

Silhouette::Silhouette(int _cluster_num,int _dim,int _size)
        :cluster_num(_cluster_num),dim(_dim),size(_size)
{
    o_clustor.resize(_cluster_num);
    index_cluster.resize(_cluster_num);
}

Silhouette::~Silhouette()
{

}

double Silhouette::showCluster()
{
    for(int i = 0; i < cluster_num ; i++)
    {

        int count = index_cluster[i].size();
        cout<<"第"<<i+1<<"类个数为:"<<count<<"  序号如下: "<<endl;
        for(int j = 0;j<count;j++)
            cout<<index_cluster[i][j]<<" ";
        cout<<endl;
    }
}

double Silhouette::showClusterForCount()
{
    for(int i = 0; i < cluster_num ; i++)
    {
        int count = index_cluster[i].size();
        cout<<"第"<<i<<"类个数为:"<<count<<endl;
    }
}

bool Silhouette::addClusterData(int _cluster_index, double* _data,int _data_index)
{
    vector<double> temp(_data,_data+dim);
    index_cluster[_cluster_index].push_back(_data_index);
    o_clustor[_cluster_index].push_back(temp);
    return true;
}

double Silhouette::calSilhouette(){
    double tempSo = 0;
    for(int i = 0; i < cluster_num ; i++)
    {
        int count = o_clustor[i].size();

        for(int j = 0;j < count;j++)
        {
            double tempAo = 0;
            //对象o到自身簇内的平均距离a(o)
            for(int k = 0; k < count ;k++)
            {
                if(j == k)
                    continue;
                tempAo += dist(o_clustor[i][j],o_clustor[i][k]);
            }
            if(count > 1)
                tempAo = tempAo / (count - 1);

            double min = 9.9e+99;
            //对象o到不属于o的簇的最小平均距离b(o)
            for(int ii = 0; ii < cluster_num ; ii++)
            {
                if(i == ii) continue;
                int icount = o_clustor[ii].size();
                double tempBo = 0;
                for(int k = 0; k < icount ;k++)
                {
                    tempBo += dist(o_clustor[i][j],o_clustor[ii][k]);
                }
                tempBo = tempBo / icount;
                if(tempBo < min)
                {
                    min = tempBo;
                }
            }
            tempSo += (min - tempAo) / (tempAo > min ? tempAo : min);
        }
    }
    return tempSo/size;
}


double Silhouette::dist(const vector<double> x, const vector<double> u)
{
    double temp = 0;
    for (int d = 0; d < dim; d++)
    {
        temp += (x[d] - u[d]) * (x[d] - u[d]);
    }
    return sqrt(temp);
}
