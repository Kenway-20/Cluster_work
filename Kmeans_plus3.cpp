//
// Created by LENOVO on 2021/11/25.
//

#include "Kmeans_plus3.h"
#include "Silhouette.h"

template<typename Real, int Dim3>

void KMeans_plus3<Real, Dim3>::dataGenerator(string file_name, Real radius, vector<KmPoint3> &pts){
    ifstream fin(file_name); //打开文件流操作
    string line;
    int i = 0;
    bool flag = true;
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        //if(pts.size() >= 2000) break;
        if(flag){
            flag = false;
            continue;
        }
        istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
        string field;
        int j = 0;
        KmPoint3 p;
        bool flag2 = true;
        vector<double> temple;
        while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
        {
            if(j >= 178) break;
            if(flag2){
                flag2 = false;
                continue;
            }
            p[j] = stod(field); //将刚刚读取的字符串添加到向量fields中
            temple.push_back(p[j]);
            j++;
        }
        i++;
        data_content.push_back(temple);
        pts.push_back(p);
    }
    data_cluster = vector<int> (pts.size());
    fin.close();
}

template<typename Real, int Dim3>
int KMeans_plus3<Real, Dim3>::nearest(KmPoint3 &pt, vector<KmPoint3> &cents, Real &d){
    int i, min_i;
    Real d1, min_d;
    min_d = HUGE_VAL;
    min_i = pt.id();
    for(i = 0; i < (int)cents.size(); ++i){
        KmPoint3 c = cents[i];
        if(min_d > (d1 = dist(c, pt))){
            min_d = d1;
            min_i = i;
        }
    }
    d = min_d;
    return min_i;
}

template<typename Real, int Dim3>
void KMeans_plus3<Real, Dim3>::kpp(vector<KmPoint3> &pts, vector<KmPoint3> &cents){
    Real sum = 0;
    vector<Real> d;
    d.resize(pts.size());
    cents[0] = pts[rand() % pts.size()];
    vector<KmPoint3> tmpCents;
    tmpCents.push_back(cents[0]);
    for(int k = 1; k < (int)cents.size(); ++k){
        sum = 0;
        for(int i = 0; i < (int)pts.size(); ++i){
            nearest(pts[i], tmpCents, d[i]);
            sum += d[i];
        }
        sum = randf(sum);
        for(int i = 0; i < (int)pts.size(); ++i){
            if((sum -= d[i]) > 0)	continue;
            cents[k] = pts[i];
            tmpCents.push_back(cents[k]);
            break;
        }
    }
    for(int i = 0; i < (int)pts.size(); ++i){
        int id = nearest(pts[i], cents, *(new Real));
        pts[i].setId(id);
    }
}

template<typename Real, int Dim3>
void KMeans_plus3<Real, Dim3>::kmcluster(vector<KmPoint3> &pts, int k, vector<KmPoint3> &outCents, vector<vector<KmPoint3>> &outPts){
    if(outCents.size() <= 0)
        outCents.resize(k);
    if(outPts.size() <= 0)
        outPts.resize(k);
    kpp(pts, outCents);
    int changed;
    do{
        for(int i = 0; i < (int)outCents.size(); ++i){
            for(int j = 0; j < Dim3; ++j)
                outCents[i][j] = 0;
            outCents[i].setId(0);
        }
        vector<int> cnt(k, 0);
        for(int i = 0; i < (int)pts.size(); ++i){
            int k = pts[i].id();
            for(int j = 0; j < Dim3; ++j)
                outCents[k][j] += pts[i][j];
            cnt[k]++;
        }
        for(int i = 0; i < (int)outCents.size(); ++i){
            for(int j = 0; j < Dim3; ++j)
                outCents[i][j] /= cnt[i];
        }
        changed = 0;
        for(int i = 0; i < (int)pts.size(); ++i){
            int min_i = nearest(pts[i], outCents, *(new Real));
            if(min_i != pts[i].id()){
                changed++;
                pts[i].setId(min_i);
            }
        }
    }while(changed > 0.001 * pts.size());
    for(int i = 0; i < (int)outCents.size(); ++i)
        outCents[i].setId(i);
    for(int i = 0; i < (int)pts.size(); ++i) {
        data_cluster[i] = pts[i].id();
        outPts[pts[i].id()].push_back(pts[i]);
    }
}

template<typename Real, int Dim3>
void KMeans_plus3<Real, Dim3>::serialize(vector<vector<KmPoint3>> &outPts){
    ofstream ofs("./cluster3.txt", ofstream::out);
    if(!ofs.is_open()){
        cout<<"open file failed!"<<endl;
        return ;
    }
    //i是该类的序号
    for(int i = 0; i < (int)outPts.size(); ++i){
        cout << "第" << i+1 << "类的数目为: " << (int)outPts[i].size() << endl;
        for(int j = 0; j < (int)outPts[i].size(); ++j){
            ofs<<outPts[i][j]<<endl;
        }
    }
    Silhouette sil((int)outPts.size(), Dim3, data_cluster.size());
    for(int i = 0; i < data_cluster.size(); i++){
        double temple[data_content[i].size()];
        for(int temple_index=0; temple_index<data_content[i].size(); temple_index++) temple[temple_index] = data_content[i][temple_index];
        sil.addClusterData(data_cluster[i], temple, i);
    }
    sil.showCluster();
    cout << "轮廓系数为： " << sil.calSilhouette() << endl;
    ofs.close();
}
