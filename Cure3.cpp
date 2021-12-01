#include "Cure3.h"
#include "Silhouette.h"

Cure3::Cure3()
{
}
Cure3::~Cure3()
{
    int i;
    for(i=0; i < NUMPATTERNS3; i++){
        if(p[i]==NULL)
            continue;
        else
            delete p[i];
    }
}
int Cure3::LoadPatterns(){
    /*
    int    i,j,len;
    char buff[300];
    char *ptr,*ptr1;
    ifstream infile("seed.txt",ios::in);    //将fname打开作为输入
    if(!infile){
        cout<<"不能打开输入文件:\n";
        return FAILURE;
    }

    for(i=0; i<NUMPATTERNS3; i++){
        int tc = 0;

        for (j=0; j< SIZEVECTOR3; j++) {
            infile >>Pattern[i][j];
        }

        infile.getline(buff,300);
    }
    infile.close();
    return SUCCESS;
    */

    ifstream fin("dataset/dataset3_t.csv"); //打开文件流操作
    string line;
    bool flag = true;
    int i = 0;
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        if(i >= NUMPATTERNS3) break;
        if(flag){
            flag = false;
            continue;
        }
        istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
        vector<double> fields; //声明一个字符串向量
        string field;
        bool flag2 = true;
        int j = 0;
        while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
        {
            if(flag2){
                flag2 = false;
                continue;
            }
            if(j >= SIZEVECTOR3) break;
            double temple = stod(field);
            //fields.push_back(temple); //将刚刚读取的字符串添加到向量fields中
            Pattern[i][j] = temple;
            j++;
        }
        i++;
    }
    data_cluster = vector<int> (Pattern.size());
    fin.close();
    return SUCCESS;
}
void  Cure3::BuildClustList(){
    int i,j;
    for(i=0; i < NUMPATTERNS3; i++){
        p[i]=new ClustNode3;//创建新的簇类节点
        p[i]->NumMembers=1;//簇中成员个数
        p[i]->Member[0]=i;//成员
        p[i]->PreMember[0]=i;//簇的代表点
        for(j=0; j < SIZEVECTOR3; j++){
            p[i]->Means[j]=Pattern[i][j];//均值
        }
        for(j=0; j < SIZEVECTOR3; j++){
            p[i]->Pre[0][j]=Pattern[i][j]+ (SHRINK3) * (p[i]->Means[j] - Pattern[i][j]);//计算代表点
        }
    }
    updateMinDist();//更新各个簇之间的距离
}



double Cure3::dist(ClustNode3 *u, ClustNode3 *v){
    double dist,MinDist;//判断簇中代表点的个数
    //如果簇中的代表点个数是否小于所设置的最多代表点个数
    int i,j;
    int MaxNum1 = u->NumMembers < NUMPRE3 ? u->NumMembers : NUMPRE3;
    int MaxNum2 = v->NumMembers < NUMPRE3 ? v->NumMembers : NUMPRE3;
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

double Cure3::EucNorm(double *u, double *v){
    int i;
    double dist;
    dist=0;//计算欧氏距离
    for(i=0; i < SIZEVECTOR3; i++){
        //求属性的值的平方和
        dist+=(*(u+i)-*(v+i))*(*(u+i)-*(v+i));
    }
    return dist;
}
void Cure3::SHRINK2Pre(ClustNode3 * u){
    int i,j,m;
    int t = u->NumMembers < NUMPRE3 ? u->NumMembers : NUMPRE3;
    for(i = 0;i < t;i++){
        m=u->PreMember[i];//取m为选择的代表点
        for(j=0; j < SIZEVECTOR3; j++){
            //根据设置的收缩比例，计算新的代表点
            u->Pre[i][j]= Pattern[m][j]+ (SHRINK3) * (u->Means[j] - Pattern[m][j]);
        }
    }
}
ClustNode3 * Cure3::createNode(ClustNode3 *u, ClustNode3 *v){
    int i,j;
    ClustNode3 *w=new ClustNode3;//创建新的簇
    w->NumMembers=u->NumMembers+v->NumMembers;//新的簇数为旧的两个簇数的和
    for(i=0; i < SIZEVECTOR3; i++){
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
ClustNode3 * Cure3::Merge(ClustNode3 *u, ClustNode3 *v){
    int i,j,MaxPoint;
    double MaxDist,dist;
    //由两个簇生成一个新的簇
    ClustNode3 *w = createNode(u, v);
    if(w->NumMembers <= NUMPRE3){
        //如果簇中的成员点的数量不大于代表点的数量
        for(i=0;i<w->NumMembers;i++){
            w->PreMember[i]=w->Member[i]; //成员点即为代表点
        }
    }else{
        //簇中成员点多于代表点，则重新计算代表点
        bool checkUsed[w->NumMembers];
        memset(checkUsed,false,w->NumMembers);
        for(i=0; i < NUMPRE3; i++){
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
int Cure3::MinClust(){
    int i,Index;
    double MinDist=9.9e+99;
    for(i=0; i < NUMPATTERNS3; i++){
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
void Cure3::RunCure3(){
    int k,u,v;
    ClustNode3 *w;
    BuildClustList();//找到每个点最近的点
    k=NUMPATTERNS3;//初始簇的个数为实验的个数
    for(; k > NUMCLUSTERS3; k--){
        u=MinClust(); //找出簇中相邻最近的两个簇
        v=p[u]->closet;
        w=Merge(p[u],p[v]);//将两个簇合并 成一个新的簇
        delete p[u];delete p[v];//删除原先的两个簇
        p[u]=w;   //将u,v移除
        p[v]=NULL;
        updateMinDist(u,v); //更新所有点最近距离
    }
}

void Cure3::updateMinDist(const int w, const int v){

    double MinDist,d;
    p[w]->closet = 0;
    p[w]->MinDist = 9.9e+99;
    for(int i=0; i < NUMPATTERNS3; i++){
        if(NULL == p[i] || w == i)
            continue;
        if(v == p[i]->closet || w == p[i]->closet)
        {
            p[i]->MinDist=9.9e+99;
            //遍历所有的簇，计算他们的距离
            for(int j=0; j < NUMPATTERNS3; j++){
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
                    //if(d < p[i]->MinDist && p[i]->NumMembers + p[j]->NumMembers < NUMPATTERNS3/2 )
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
        //	if( temp < p[w]->MinDist && p[i]->NumMembers + p[w]->NumMembers < NUMPATTERNS3/2)
        //	if( temp < p[w]->MinDist && p[i]->NumMembers + p[w]->NumMembers < 75)
        if( temp < p[w]->MinDist)
        {
            p[w]->closet = i;
            p[w]->MinDist = temp;
        }
    }
}

void Cure3::updateMinDist(){
    double MinDist,d;
    for(int i=0; i < NUMPATTERNS3; i++){
        if(p[i]==NULL)
            continue;
        //首先将簇的最小距离设置为一个很大的值
        p[i]->MinDist=9.9e+99;
        //遍历所有的簇，计算他们的距离
        for(int j=0; j < NUMPATTERNS3; j++){
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

void Cure3::ShowClusters(){
    //return;
    int i,j = 0;
    Silhouette sil(NUMCLUSTERS3, SIZEVECTOR3, NUMPATTERNS3);
    //cout<<"该数据集分为"<<NUMCLUSTERS3<<"类"<<endl;
    int right3 = 0;
    int right2 = 0;
    int right1 = 0;
    cout << " start show()" << endl;
    for(i=0; i < NUMPATTERNS3; i++){
        if(p[i]==NULL)
            continue;
        else
        {
            sort(p[i]->Member,p[i]->Member+p[i]->NumMembers);
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

