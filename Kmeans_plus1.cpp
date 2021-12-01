//
// Created by LENOVO on 2021/11/25.
//

#include "Kmeans_plus1.h"
#include "Silhouette.h"

template<typename Real, int Dim1>

void KMeans_plus1<Real, Dim1>::dataGenerator(string file_name, Real radius, vector<KmPoint1> &pts){
    ifstream fin(file_name); //���ļ�������
    string line;
    int i = 0;
    while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
    {
        //if(i >= 2000) break;
        istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
        string field;
        int j = 0;
        KmPoint1 p;
        vector<double> temple;
        while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
        {
            p[j] = stod(field); //���ոն�ȡ���ַ�����ӵ�����fields��
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

template<typename Real, int Dim1>
int KMeans_plus1<Real, Dim1>::nearest(KmPoint1 &pt, vector<KmPoint1> &cents, Real &d){
    int i, min_i;
    Real d1, min_d;
    min_d = HUGE_VAL;
    min_i = pt.id();
    for(i = 0; i < (int)cents.size(); ++i){
        KmPoint1 c = cents[i];
        if(min_d > (d1 = dist(c, pt))){
            min_d = d1;
            min_i = i;
        }
    }
    d = min_d;
    return min_i;
}

template<typename Real, int Dim1>
void KMeans_plus1<Real, Dim1>::kpp(vector<KmPoint1> &pts, vector<KmPoint1> &cents){
    Real sum = 0;
    vector<Real> d;
    d.resize(pts.size());
    cents[0] = pts[rand() % pts.size()];
    vector<KmPoint1> tmpCents;
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

template<typename Real, int Dim1>
void KMeans_plus1<Real, Dim1>::kmcluster(vector<KmPoint1> &pts, int k, vector<KmPoint1> &outCents, vector<vector<KmPoint1>> &outPts){
    if(outCents.size() <= 0)
        outCents.resize(k);
    if(outPts.size() <= 0)
        outPts.resize(k);
    kpp(pts, outCents);
    int changed;
    do{
        for(int i = 0; i < (int)outCents.size(); ++i){
            for(int j = 0; j < Dim1; ++j)
                outCents[i][j] = 0;
            outCents[i].setId(0);
        }
        vector<int> cnt(k, 0);
        for(int i = 0; i < (int)pts.size(); ++i){
            int k = pts[i].id();
            for(int j = 0; j < Dim1; ++j)
                outCents[k][j] += pts[i][j];
            cnt[k]++;
        }
        for(int i = 0; i < (int)outCents.size(); ++i){
            for(int j = 0; j < Dim1; ++j)
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

template<typename Real, int Dim1>
void KMeans_plus1<Real, Dim1>::serialize(vector<vector<KmPoint1>> &outPts){
    ofstream ofs("./cluster1.txt", ofstream::out);
    if(!ofs.is_open()){
        cout<<"open file failed!"<<endl;
        return ;
    }
    //i�Ǹ�������
    for(int i = 0; i < (int)outPts.size(); ++i){
        cout << "��" << i+1 << "�����ĿΪ: " << (int)outPts[i].size() << endl;
        //double temple[] = outPts[i][0];
        //for(auto &t:temple) cout << t << ", ";
        //cout << endl;
        for(int j = 0; j < (int)outPts[i].size(); ++j){
            ofs<<outPts[i][j]<<endl;
        }
    }
    Silhouette sil((int)outPts.size(), Dim1, data_cluster.size());
    for(int i = 0; i < data_cluster.size(); i++){
        double temple[data_content[i].size()];
        for(int temple_index=0; temple_index<data_content[i].size(); temple_index++) temple[temple_index] = data_content[i][temple_index];
        sil.addClusterData(data_cluster[i], temple, i);
    }
    sil.showCluster();
    cout << "����ϵ��Ϊ�� " << sil.calSilhouette() << endl;
    ofs.close();
}
