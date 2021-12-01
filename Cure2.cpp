#include "Cure2.h"
#include "Silhouette.h"

Cure2::Cure2()
{
}
Cure2::~Cure2()
{
    int i;
    for(i=0; i < NUMPATTERNS2; i++){
        if(p[i]==NULL)
            continue;
        else
            delete p[i];
    }
}
int Cure2::LoadPatterns(){
    ifstream fin("dataset/dataset2_vec.csv"); //���ļ�������
    string line;
    int i = 0;
    while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
    {
        if(i >= NUMPATTERNS2) break;
        istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
        vector<double> fields; //����һ���ַ�������
        string field;
        int j = 0;
        while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
        {
            Pattern[i][j] = stod(field); //���ոն�ȡ���ַ������ӵ�����fields��
            j++;
        }
        i++;
    }
    data_cluster = vector<int> (Pattern.size());
    fin.close();
    return SUCCESS;
}
void  Cure2::BuildClustList(){
    int i,j;
    for(i=0; i < NUMPATTERNS2; i++){
        p[i]=new ClustNode2;//�����µĴ���ڵ�
        p[i]->NumMembers=1;//���г�Ա����
        p[i]->Member[0]=i;//��Ա
        p[i]->PreMember[0]=i;//�صĴ�����
        for(j=0; j < SIZEVECTOR2; j++){
            p[i]->Means[j]=Pattern[i][j];//��ֵ
        }
        for(j=0; j < SIZEVECTOR2; j++){
            p[i]->Pre[0][j]=Pattern[i][j]+ (SHRINK2) * (p[i]->Means[j] - Pattern[i][j]);//���������
        }
    }
    updateMinDist();//���¸�����֮��ľ���
}



double Cure2::dist(ClustNode2 *u, ClustNode2 *v){
    double dist,MinDist;//�жϴ��д�����ĸ���
    //������еĴ���������Ƿ�С�������õ������������
    int i,j;
    int MaxNum1 = u->NumMembers < NUMPRE2 ? u->NumMembers : NUMPRE2;
    int MaxNum2 = v->NumMembers < NUMPRE2 ? v->NumMembers : NUMPRE2;
    MinDist=9.9e+99;//����������֮��Ĵ�������С��ŷ�Ͼ���
    for(i=0;i<MaxNum1;i++){
        for(j=0;j<MaxNum2;j++){
            //��������������֮���ŷʽ����
            dist=EucNorm(u->Pre[i],v->Pre[j]);
            //ѡ����С�ľ��뷵�ء�
            if(dist<MinDist)
                MinDist=dist;
        }
    }
    return MinDist;
}

double Cure2::EucNorm(double *u, double *v){
    int i;
    double dist;
    dist=0;//����ŷ�Ͼ���
    for(i=0; i < SIZEVECTOR2; i++){
        //�����Ե�ֵ��ƽ����
        dist+=(*(u+i)-*(v+i))*(*(u+i)-*(v+i));
    }
    return dist;
}
void Cure2::SHRINK2Pre(ClustNode2 * u){
    int i,j,m;
    int t = u->NumMembers < NUMPRE2 ? u->NumMembers : NUMPRE2;
    for(i = 0;i < t;i++){
        m=u->PreMember[i];//ȡmΪѡ��Ĵ�����
        for(j=0; j < SIZEVECTOR2; j++){
            //�������õ����������������µĴ�����
            u->Pre[i][j]= Pattern[m][j]+ (SHRINK2) * (u->Means[j] - Pattern[m][j]);
        }
    }
}
ClustNode2 * Cure2::createNode(ClustNode2 *u, ClustNode2 *v){
    int i,j;
    ClustNode2 *w=new ClustNode2;//�����µĴ�
    w->NumMembers=u->NumMembers+v->NumMembers;//�µĴ���Ϊ�ɵ����������ĺ�
    for(i=0; i < SIZEVECTOR2; i++){
        //�����µĴص���ֵ
        w->Means[i]=(u->Means[i]*u->NumMembers+v->Means[i]*v->NumMembers)/w->NumMembers;
    }
    for(i=0;i<u->NumMembers;i++){
        //����U�еĳ�Ա���ӵ��µĴ���
        w->Member[i]=u->Member[i];
    }
    for(i=u->NumMembers;i<w->NumMembers;i++){
        //������V�ĳ�Ա���ӵ�����
        w->Member[i]=v->Member[i-u->NumMembers];
    }
    return w;
}
ClustNode2 * Cure2::Merge(ClustNode2 *u, ClustNode2 *v){
    int i,j,MaxPoint;
    double MaxDist,dist;
    //������������һ���µĴ�
    ClustNode2 *w = createNode(u, v);
    if(w->NumMembers <= NUMPRE2){
        //������еĳ�Ա������������ڴ����������
        for(i=0;i<w->NumMembers;i++){
            w->PreMember[i]=w->Member[i]; //��Ա�㼴Ϊ������
        }
    }else{
        //���г�Ա����ڴ����㣬�����¼��������
        bool checkUsed[w->NumMembers];
        memset(checkUsed,false,w->NumMembers);
        for(i=0; i < NUMPRE2; i++){
            MaxDist=0;
            for(j=0;j<w->NumMembers;j++){
                int temple_size = Pattern[w->Member[j]].size();
                double temple[temple_size];
                for(int temple_i = 0; temple_i < Pattern[w->Member[j]].size(); temple_i++) temple[temple_i] = Pattern[w->Member[j]][temple_i];
                if(i==0){
                    //��һ��������Ϊ������ֵ��Զ�ĵ�
                    //dist=EucNorm(w->Means,Pattern[w->Member[j]]);//����ŷ�Ͼ���
                    dist=EucNorm(w->Means, temple);//����ŷ�Ͼ���
                }else{
                    //ʣ��Ĵ�����Ϊ����ǰһ����������Զ�ĵ�
                    if(checkUsed[j])//��ֹ�������ظ�
                        continue;
                    //����ŷ�Ͼ���
                    //dist=EucNorm(w->Pre[i-1],Pattern[w->Member[j]]);
                    dist=EucNorm(w->Pre[i-1],temple);
                }
                //ѡ�����ǰһ����������Զ�ĵ�Ϊ�µĴ�����
                if(dist>=MaxDist){
                    MaxDist=dist;
                    MaxPoint=j;
                    //����ѡ����
                    checkUsed[j] = true;
                }
            }
            //�����µĴ�����
            w->PreMember[i] = MaxPoint;
        }
    }
    //����������
    SHRINK2Pre(w);
    //���ش�����
    return w;
}
int Cure2::MinClust(){
    int i,Index;
    double MinDist=9.9e+99;
    for(i=0; i < NUMPATTERNS2; i++){
        //������ѱ��ϲ�����Ϊ��
        if(p[i]==NULL)
            continue;
        //�ж��Ƿ�Ϊ������С�Ĵ�
        if(p[i]->MinDist<MinDist){
            MinDist=p[i]->MinDist;
            Index=i;
        }
    }
    //��������ص��±�
    return Index;
}
void Cure2::RunCure2(){
    int k,u,v;
    ClustNode2 *w;
    BuildClustList();//�ҵ�ÿ��������ĵ�
    k=NUMPATTERNS2;//��ʼ�صĸ���Ϊʵ��ĸ���
    for(; k > NUMCLUSTERS2; k--){
        u=MinClust(); //�ҳ��������������������
        v=p[u]->closet;
        w=Merge(p[u],p[v]);//�������غϲ� ��һ���µĴ�
        delete p[u];delete p[v];//ɾ��ԭ�ȵ�������
        p[u]=w;   //��u,v�Ƴ�
        p[v]=NULL;
        updateMinDist(u,v); //�������е��������
    }
}

void Cure2::updateMinDist(const int w, const int v){

    double MinDist,d;
    p[w]->closet = 0;
    p[w]->MinDist = 9.9e+99;
    for(int i=0; i < NUMPATTERNS2; i++){
        if(NULL == p[i] || w == i)
            continue;
        if(v == p[i]->closet || w == p[i]->closet)
        {
            p[i]->MinDist=9.9e+99;
            //�������еĴأ��������ǵľ���
            for(int j=0; j < NUMPATTERNS2; j++){
                //���������Ѿ����ϲ�����������
                if(p[j]==NULL)
                    continue;
                    //����������������Ҳ����
                else if(i==j)
                    continue;
                else{
                    //�����֮��ľ���
                    d=dist(p[i],p[j]);
                    //��������Ĵغ;���
                    //if(d < p[i]->MinDist && p[i]->NumMembers + p[j]->NumMembers < NUMPATTERNS2/2 )
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
        //	if( temp < p[w]->MinDist && p[i]->NumMembers + p[w]->NumMembers < NUMPATTERNS2/2)
        //	if( temp < p[w]->MinDist && p[i]->NumMembers + p[w]->NumMembers < 75)
        if( temp < p[w]->MinDist)
        {
            p[w]->closet = i;
            p[w]->MinDist = temp;
        }
    }
}

void Cure2::updateMinDist(){
    double MinDist,d;
    for(int i=0; i < NUMPATTERNS2; i++){
        if(p[i]==NULL)
            continue;
        //���Ƚ��ص���С��������Ϊһ���ܴ��ֵ
        p[i]->MinDist=9.9e+99;
        //�������еĴأ��������ǵľ���
        for(int j=0; j < NUMPATTERNS2; j++){
            //���������Ѿ����ϲ�����������
            if(p[j]==NULL)
                continue;
                //����������������Ҳ����
            else if(i==j)
                continue;
            else{
                //�����֮��ľ���
                d=dist(p[i],p[j]);
                //��������Ĵغ;���
                if(d < p[i]->MinDist){
                    p[i]->closet=j;
                    p[i]->MinDist=d;
                }
            }
        }
    }
}

void Cure2::ShowClusters(){
    //return;
    int i,j = 0;
    Silhouette sil(NUMCLUSTERS2, SIZEVECTOR2, NUMPATTERNS2);
    //cout<<"�����ݼ���Ϊ"<<NUMCLUSTERS2<<"��"<<endl;
    int right3 = 0;
    int right2 = 0;
    int right1 = 0;
    cout << " start show()" << endl;
    for(i=0; i < NUMPATTERNS2; i++){
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

    cout<<"\n���������"<<sil.calSilhouette()<<endl;
}
