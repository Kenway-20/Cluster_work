#include "Cure1.h"
#include "Silhouette.h"

Cure1::Cure1()
{
}
Cure1::~Cure1()
{
    int i;
    for(i=0; i < NUMPATTERNS1; i++){
        if(p[i]==NULL)
            continue;
        else
            delete p[i];
    }
}
int Cure1::LoadPatterns(){
    ifstream fin("dataset/dataset1_vec.csv"); //打开文件流操作
    string line;
    int i = 0;
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        if(i >= NUMPATTERNS1) break;
        istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
        string field;
        int j = 0;
        while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
        {
            Pattern[i][j] = stod(field); //将刚刚读取的字符串添加到向量fields中
            j++;
        }
       i++;
    }
    data_cluster = vector<int> (Pattern.size());
    fin.close();
    return SUCCESS;
}
void  Cure1::BuildClustList(){
    int i,j;
    for(i=0; i < NUMPATTERNS1; i++){
        p[i]=new ClustNode1;//创建新的簇类节点
        p[i]->NumMembers=1;//簇中成员个数
        p[i]->Member[0]=i;//成员
        p[i]->PreMember[0]=i;//簇的代表点
        for(j=0; j < SIZEVECTOR1; j++){
            p[i]->Means[j]=Pattern[i][j];//均值
        }
        for(j=0; j < SIZEVECTOR1; j++){
            p[i]->Pre[0][j]=Pattern[i][j]+ (SHRINK1) * (p[i]->Means[j] - Pattern[i][j]);//计算代表点
        }
    }
    updateMinDist();//更新各个簇之间的距离
}



double Cure1::dist(ClustNode1 *u, ClustNode1 *v){
    double dist,MinDist;//判断簇中代表点的个数
    //如果簇中的代表点个数是否小于所设置的最多代表点个数
    int i,j;
    int MaxNum1 = u->NumMembers < NUMPRE1 ? u->NumMembers : NUMPRE1;
    int MaxNum2 = v->NumMembers < NUMPRE1 ? v->NumMembers : NUMPRE1;
    MinDist=9.9e+99;//计算两个簇之间的代表点最小的欧氏距离
    for(i=0;i<MaxNum1;i++){
        for(j=0;j<MaxNum2;j++){
            //计算两个代表点之间的欧式距离
            dist=EucNorm(u->Pre[i],v->Pre[j]);
            //选择最小的距离返回。
            if(dist<MinDist)
                MinDist=dist;
        }
    }
    return MinDist;
}

double Cure1::EucNorm(double *u, double *v){
    int i;
    double dist;
    dist=0;//计算欧氏距离
    for(i=0; i < SIZEVECTOR1; i++){
        //求属性的值的平方和
        dist+=(*(u+i)-*(v+i))*(*(u+i)-*(v+i));
    }
    return dist;
}
void Cure1::SHRINK2Pre(ClustNode1 * u){
    int i,j,m;
    int t = u->NumMembers < NUMPRE1 ? u->NumMembers : NUMPRE1;
    for(i = 0;i < t;i++){
        m=u->PreMember[i];//取m为选择的代表点
        for(j=0; j < SIZEVECTOR1; j++){
            //根据设置的收缩比例，计算新的代表点
            u->Pre[i][j]= Pattern[m][j]+ (SHRINK1) * (u->Means[j] - Pattern[m][j]);
        }
    }
}
ClustNode1 * Cure1::createNode(ClustNode1 *u, ClustNode1 *v){
    int i,j;
    ClustNode1 *w=new ClustNode1;//创建新的簇
    w->NumMembers=u->NumMembers+v->NumMembers;//新的簇数为旧的两个簇数的和
    for(i=0; i < SIZEVECTOR1; i++){
        //计算新的簇的中值
        w->Means[i]=(u->Means[i]*u->NumMembers+v->Means[i]*v->NumMembers)/w->NumMembers;
    }
    for(i=0;i<u->NumMembers;i++){
        //将簇U中的成员添加到新的簇中
        w->Member[i]=u->Member[i];
    }
    for(i=u->NumMembers;i<w->NumMembers;i++){
        //将簇中V的成员添加到簇中
        w->Member[i]=v->Member[i-u->NumMembers];
    }
    return w;
}
ClustNode1 * Cure1::Merge(ClustNode1 *u, ClustNode1 *v){
    int i,j,MaxPoint;
    double MaxDist,dist;
    //由两个簇生成一个新的簇
    ClustNode1 *w = createNode(u, v);
    if(w->NumMembers <= NUMPRE1){
        //如果簇中的成员点的数量不大于代表点的数量
        for(i=0;i<w->NumMembers;i++){
            w->PreMember[i]=w->Member[i]; //成员点即为代表点
        }
    }else{
        //簇中成员点多于代表点，则重新计算代表点
        bool checkUsed[w->NumMembers];
        memset(checkUsed,false,w->NumMembers);
        for(i=0; i < NUMPRE1; i++){
            MaxDist=0;
            for(j=0;j<w->NumMembers;j++){
                int temple_size = Pattern[w->Member[j]].size();
                double temple[temple_size];
                for(int temple_i = 0; temple_i < Pattern[w->Member[j]].size(); temple_i++) temple[temple_i] = Pattern[w->Member[j]][temple_i];
                if(i==0){
                    //第一个代表点为距离中值最远的点
                    //dist=EucNorm(w->Means,Pattern[w->Member[j]]);//计算欧氏距离
                    dist=EucNorm(w->Means, temple);//计算欧氏距离
                }else{
                    //剩余的代表点为距离前一个代表点最远的点
                    if(checkUsed[j])//防止代表点重复
                        continue;
                    //计算欧氏距离
                    //dist=EucNorm(w->Pre[i-1],Pattern[w->Member[j]]);
                    dist=EucNorm(w->Pre[i-1],temple);
                }
                //选择距离前一个代表点最远的点为新的代表点
                if(dist>=MaxDist){
                    MaxDist=dist;
                    MaxPoint=j;
                    //设置选择标记
                    checkUsed[j] = true;
                }
            }
            //设置新的代表点
            w->PreMember[i] = MaxPoint;
        }
    }
    //收缩代表点
    SHRINK2Pre(w);
    //返回代表点
    return w;
}
int Cure1::MinClust(){
    int i,Index;
    double MinDist=9.9e+99;
    for(i=0; i < NUMPATTERNS1; i++){
        //如果簇已被合并，则为空
        if(p[i]==NULL)
            continue;
        //判断是否为距离最小的簇
        if(p[i]->MinDist<MinDist){
            MinDist=p[i]->MinDist;
            Index=i;
        }
    }
    //返回这个簇的下标
    return Index;
}
void Cure1::RunCure1(){
    int k,u,v;
    ClustNode1 *w;
    BuildClustList();//找到每个点最近的点
    k=NUMPATTERNS1;//初始簇的个数为实验的个数
    for(; k > NUMCLUSTERS1; k--){
        u=MinClust(); //找出簇中相邻最近的两个簇
        v=p[u]->closet;
        w=Merge(p[u],p[v]);//将两个簇合并 成一个新的簇
        delete p[u];delete p[v];//删除原先的两个簇
        p[u]=w;   //将u,v移除
        p[v]=NULL;
        updateMinDist(u,v); //更新所有点最近距离
    }
}

void Cure1::updateMinDist(const int w, const int v){
    double MinDist,d;
    p[w]->closet = 0;
    p[w]->MinDist = 9.9e+99;
    for(int i=0; i < NUMPATTERNS1; i++){
        if(NULL == p[i] || w == i)
            continue;
        if(v == p[i]->closet || w == p[i]->closet)
        {
            p[i]->MinDist=9.9e+99;
            //遍历所有的簇，计算他们的距离
            for(int j=0; j < NUMPATTERNS1; j++){
                //如果这个簇已经被合并，则跳过。
                if(p[j]==NULL)
                    continue;
                    //如果这个簇是自身，也跳过
                else if(i==j)
                    continue;
                else{
                    //计算簇之间的距离
                    d=dist(p[i],p[j]);
                    //更新最近的簇和距离
                    //if(d < p[i]->MinDist && p[i]->NumMembers + p[j]->NumMembers < NUMPATTERNS1/2 )
                    //if(d < p[i]->MinDist  && p[i]->NumMembers + p[j]->NumMembers < 75 )
                    if(d < p[i]->MinDist)
                    {
                        p[i]->closet=j;
                        p[i]->MinDist=d;
                    }
                }
            }
        }
        double temp = dist(p[i],p[w]);
        //	if( temp < p[w]->MinDist && p[i]->NumMembers + p[w]->NumMembers < NUMPATTERNS1/2)
        //	if( temp < p[w]->MinDist && p[i]->NumMembers + p[w]->NumMembers < 75)
        if( temp < p[w]->MinDist)
        {
            p[w]->closet = i;
            p[w]->MinDist = temp;
        }
    }
}

void Cure1::updateMinDist(){
    double MinDist,d;
    for(int i=0; i < NUMPATTERNS1; i++){
        if(p[i]==NULL)
            continue;
        //首先将簇的最小距离设置为一个很大的值
        p[i]->MinDist=9.9e+99;
        //遍历所有的簇，计算他们的距离
        for(int j=0; j < NUMPATTERNS1; j++){
            //如果这个簇已经被合并，则跳过。
            if(p[j]==NULL)
                continue;
                //如果这个簇是自身，也跳过
            else if(i==j)
                continue;
            else{
                //计算簇之间的距离
                d=dist(p[i],p[j]);
                //更新最近的簇和距离
                if(d < p[i]->MinDist){
                    p[i]->closet=j;
                    p[i]->MinDist=d;
                }
            }
        }
    }
}

void Cure1::ShowClusters(){
    //return;
    int i,j = 0;
    Silhouette sil(NUMCLUSTERS1, SIZEVECTOR1, NUMPATTERNS1);
    //cout<<"该数据集分为"<<NUMCLUSTERS1<<"类"<<endl;
    int right3 = 0;
    int right2 = 0;
    int right1 = 0;
    cout << " start show()" << endl;
    for(i=0; i < NUMPATTERNS1; i++){
        if(p[i]==NULL)
            continue;
        else
        {
            sort(p[i]->Member.begin(),p[i]->Member.begin()+p[i]->NumMembers);
            for(int k=0;k<p[i]->NumMembers;k++)
            {
                int index_temp = p[i]->Member[k];
                int temple_size = Pattern[index_temp].size();
                double temple[temple_size];
                for(int temple_i = 0; temple_i < Pattern[index_temp].size(); temple_i++) temple[temple_i] = Pattern[index_temp][temple_i];
                //sil.addClusterData(j,Pattern[index_temp],index_temp);
                sil.addClusterData(j,temple,index_temp);
                data_cluster[index_temp] = j;
            }
            j++;
        }
    }
    cout << " end show()" << endl;
    sil.showCluster();

    cout<<"\n评估结果："<<sil.calSilhouette()<<endl;
}

vector<vector<double>> Cure1::get_Pattern(){
    return Pattern;
}

