//
// Created by hou guoli on 2018/2/14.
//

/*
    深度学习神经网络V1.0
        made by xyt
        2015/7/23
       使用语言:C

本程序构建多层矩阵形神经网络多输入单输出
学习策略:随机梯度下降
激活函数:sigmoid
使用前必须用srand((unsigned)time(NULL))取随机映射初始值
*/

#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
using namespace std;

#define DNN_VEC 8  //输入训练组组数
#define DNN_INUM 5  //输入维度
double dnn_sig(double in){  //sigmoid函数,此处不可变
    return 1.0/(1.0+exp(-1.0*in));
}
struct dnn_cell{  //神经元结构体
    double w[DNN_INUM];
    double wb;
    double in[DNN_INUM];
    double out;
    double error;
    double v;
    void SetCell_Default(){  //默认初始化，权值初始化很小
        int i;
        for(i=0;i<DNN_INUM;i++){
            w[i]=0.000001;
        }
        wb=0.000001;
        v=0.001;
    }
    void SetCell_InitWeight(double Initial){  //权值统一权值初始化
        int i;
        for(i=0;i<DNN_INUM;i++){
            w[i]=Initial;
        }
        wb=Initial;
        v=0.001;
    }
    void SetCell_InitAll(double Initial,double InV){  //权值统一初始化，学习速率初始化
        int i;
        for(i=0;i<DNN_INUM;i++){
            w[i]=Initial;
        }
        wb=Initial;
        v=InV;
    }
    void SetCell_Precise(double *InW,double InWb,double InV){  //权值精确初始化，学习速率初始化
        int i;
        for(i=0;i<DNN_INUM;i++){
            w[i]=InW[i];
        }
        wb=InWb;
        v=InV;
    }
    void SetIn(double *SIn){  //设定神经元输入
        int i;
        for(i=0;i<DNN_INUM;i++){
            in[i]=SIn[i];
        }
    }
    double GetOut(){  //获取、设定神经元输出
        int i;
        double sum=0;
        for(i=0;i<DNN_INUM;i++){
            sum+=w[i]*in[i];
        }
        sum+=wb;
        out=dnn_sig(sum);
        return out;
    }
    void UpdateWeight(){  //更新神经元权值
        int i;
        for(i=0;i<DNN_INUM;i++){
            w[i]-=v*error*out*(1-out)*in[i];
        }
        wb=v*error*out*(1-out);
    }
    void SetError(double InErr){  //设定神经元误差传播值
        error=InErr;
    }
    void SetSpeed(double InV){  //设定神经元学习速率
        v=InV;
    }
};
/*  获得前向传播得到的输出值，第一个参数为神经元结构体数组，第二个参数为神经网络
层数。具体排列为：前0~DNN_INUM神经元为第一层，后面每DNN_INUM个神经元为一层，依次
排列，直至最后一个输出神经元为单独一层，如果层数是4，DNN_INUM=5（5输入）则神经元
数量应为(4-1)*5+1=16个。*in参数为输入网络的具有DNN_INUM个数据的数组
*/
double DNN_Cal(dnn_cell *incell,int deep,double *in)
{
    double out=0;
    int dd=0,i,j,k,count=0;
    double tmp[DNN_INUM];
    for(i=0;i<DNN_INUM;i++)  tmp[i]=in[i];
    for(j=0;j<deep-1;j++)
    {
        for(i=j*DNN_INUM;i<(j*DNN_INUM+DNN_INUM);i++)
        {
            incell[i].SetIn(tmp);
            incell[i].GetOut();
            count++;
        }
        k=0;
        for(i=j*DNN_INUM;i<(j*DNN_INUM+DNN_INUM);i++)  {tmp[k]=incell[i].out; k++;}
    }
    incell[count].SetIn(tmp);
    out=incell[count].GetOut();
    return out;
}
/*
    对输入矩阵训练，最后得到更新的神经网络,要求每组数据量限定为DNN_INUM数据组数限定为DNN_VEC
输入神经原组为按层排列，除了最后一层的节点数为一其他节点数都限定为输入向量DNN_INUM
deep为网络层数至少2层，算上最后输出层,n为训练次数,expect为期望,返回训练后平均误差
*/
double DNN_Train(dnn_cell *cell,int deep,double InMat[DNN_VEC][DNN_INUM],double *expect,int n)
{
    double out,devi,sum;
    double de[DNN_VEC];
    int co=n,kp=-1;
    int i,j,k,tt,l;
    for(i=0;i<DNN_VEC;i++) de[i]=9.9;
    while(co--){
        kp=(int)(rand()*(double)(DNN_VEC)/RAND_MAX);
        out=DNN_Cal(cell,deep,InMat[kp]);
        devi=out-expect[kp];
        de[kp]=devi;
        //printf("%lf  %lf  %lf  %d\n",fabs(de[0]),fabs(de[3]),fabs(de[7]),kp);
        tt=(deep-1)*DNN_INUM;
        cell[tt].error=devi;
        l=0;
        for(i=(deep-2)*DNN_INUM;i<tt;i++) {cell[i].error=cell[tt].error*cell[tt].out*(1-cell[tt].out)*cell[tt].w[l];l++;}
        for(j=deep-2;j>0;j--){
            l=0;
            for(i=(j-1)*DNN_INUM;i<j*DNN_INUM;i++){
                sum=0;
                for(k=j*DNN_INUM;k<(j+1)*DNN_INUM;k++){
                    sum+=cell[k].error*cell[k].out*(1-cell[k].out)*cell[k].w[l];
                }
                cell[i].error=sum;
                l++;
            }
        }
        for(i=0;i<=(deep-1)*DNN_INUM;i++){
            cell[i].UpdateWeight();
        }
        //变学习速率，可以自行更改===============================
        for(i=0;i<=(deep-1)*DNN_INUM;i++){
            cell[i].SetSpeed(fabs(devi));
        }
        //=======================================================
    }
    sum=0;
    for(i=0;i<DNN_VEC;i++) sum+=fabs(de[i]);
    return sum/DNN_VEC;
}


int main()
{
    srand( (unsigned)time(NULL) );
    double expect[8]={0.23,0.23,0.23,0.23,0.83,0.83,0.83,0.83};
    double in[8][5]={1,2,3,4,5,
                     1.1,2.1,3,3.9,5,
                     0.8,2.2,3,4.2,5,
                     0.9,2.1,3,4,5,
                     5,4,3,2,1,
                     4.9,4.1,2.9,2,1,
                     5,4,3.1,2,1,
                     5,4,2.9,2.1,1
    };
    dnn_cell a[16];
    int i;
    for(i=0;i<16;i++) a[i].SetCell_InitAll(rand()*2.0/RAND_MAX-1,0.001);
    DNN_Train(a,4,in,expect,100000);
    double pp[5];
    while(1)
    {
        for(i=0;i<5;i++)
            cin>>pp[i];
        cout<<DNN_Cal(a,4,pp)<<endl;
    }
}