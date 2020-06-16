//
// Created by lengm on 2020/6/16.
//

#include "Disk_lmx.h"
#include "stdio.h"
#include "stdlib.h"
void CopyL(int Sour[],int Dist[] ,int x);
void SetDI(int DiscL[]);
void Print(int Pri[],int x);
void DelInq(int Sour[],int x,int y);
void SSTF(int Han,int DiscL[]);
int SCAN(int Han,int DiscL[],int x,int y);
void CSCAN(int Han,int DiscL[]);
//void N_Step_SCAN(int Han1,int DiscL[]);
void PaiXu();
void Pri();
int NAll=0;
int Best[5][2];
int Limit=0;
int Jage;
float Aver=0;

int main()
{
    int i;
    int DiscLine[10];
    int Hand;
    int Con=1;
    int n;
    while(Con==1)
    {
        Jage=0;
        printf("\n 请输入初始的磁道数:");
        scanf("%d",&Hand);
        printf("\n+ 输入寻找的范围:");
        scanf("%d",&Limit);
        if(Limit>65536){
            printf("超范围!");
        }
        else{
            printf("1.最短寻道时间优先算法(SSTF)\n");
            printf("2.扫描算法(SCAN)\n");
            printf("3.循环扫描算法(CSCAN)\n");
            scanf("%d",&n);
            if(n==0) exit(0);
            printf("\n");
            switch(n)
            {
                case 1:
                    SetDI(DiscLine);  //随机生成磁道数
                    SSTF(Hand,DiscLine); //最短寻道时间优先算法(SSTF)
                    break;
                case 2:
                    SetDI(DiscLine);  //随机生成磁道数
                    SCAN(Hand,DiscLine,0,9);  //扫描算法(SCAN)
                    break;
                case 3:
                    SetDI(DiscLine);  //随机生成磁道数
                    CSCAN(Hand,DiscLine); //循环扫描算法(CSCAN)
                    break;
                case 5:
                    SetDI(DiscLine);  //随机生成磁道数

                    SetDI(DiscLine);  //随机生成磁道数
                    SSTF(Hand,DiscLine); //最短寻道时间优先算法(SSTF)
                    SCAN(Hand,DiscLine,0,9); //扫描算法(SCAN)
                    CSCAN(Hand,DiscLine);  //循环扫描算法(CSCAN)
                    PaiXu();  //寻道长度由低到高排序
                    printf("\n\n+ 寻道长度由低到高排序:");
                    for(i=0;i<5;i++)
                    {
                        printf("%4d ",Best[i][0]);
                    }
                    break;
            }
            printf("\n\n+ 是否继续(按0结束,按1继续)?");
            scanf("%5d",&Con);
        }

    }
}

//数组Sour复制到数组Dist，复制到x个数
void CopyL(int Sour[],int Dist[] ,int x)
{
    int i;
    for(i=0;i<=x;i++)
    {
        Dist[i]=Sour[i];
    }
}
//打印输出数组Pri
void Print(int Pri[],int x)
{
    int i;
    for(i=0;i<=x;i++)
    {
        printf("%5d",Pri[i]);
    }
}
//随机生成磁道数
void SetDI(int DiscL[])
{
    int i;
    for(i=0;i<=9;i++)
    {
        DiscL[i]=rand()%Limit;//随机生成10个磁道号
    }
    printf("+ 需要寻找的磁道号:");
    Print(DiscL,9);  //输出随机生成的磁道号
    printf("\n");
}
//数组Sour把x位置的数删除，并把y前面的数向前移动，y后的数保持不变(即会出现2个y)
void DelInq(int Sour[],int x,int y)
{
    int i;
    for(i=x;i<y;i++)
    {
        Sour[i]=Sour[i+1];
        x++;
    }
}
//最短寻道时间优先算法(SSTF)
void SSTF(int Han,int DiscL[])
{
    int i,j,k,h,All;
    int Temp;  //Temp是计算移动的磁道距离的临时变量
    int RLine[10];   //将随机生成的磁道数数组Discl[]复制给数组RLine[]
    int Min;
    All=0;  //统计全部的磁道数变量
    k=9;  //限定10个的磁道数
    CopyL(DiscL,RLine,9);  //复制磁道号到临时数组RLine
    printf("\n+ 按照SSTF算法磁道的访问顺序为:");
    for(i=0;i<=9;i++)
    {
        Min=64000;
        for(j=0;j<=k;j++) //内循环寻找与当前磁道号最短寻道的时间的磁道号
        {
            if(RLine[j]>Han)  //如果第一个随机生成的磁道号大于当前的磁道号，执行下一句
                Temp=RLine[j]-Han;  //求出临时的移动距离
            else
                Temp=Han-RLine[j];  //求出临时的移动距离
            if(Temp<Min)  //如果每求出一次的移动距离小于Min，执行下一句
            {
                Min=Temp;  //Temp临时值赋予Min
                h=j;  //把最近当前磁道号的数组下标赋予h
            }
        }
        All=All+Min;  //统计一共移动的距离
        printf("%5d",RLine[h]);
        Han=RLine[h];
        DelInq(RLine,h,k);  //每个磁道数向前移动一位
        k--;
    }
    Best[Jage][1]=All;//Best[][1]存放移动磁道数
    Best[Jage][0]=2;//Best[][0]存放算法的序号为:2
    Jage++;//排序序号加1
    Aver=((float)All)/10;//求平均寻道次数
    printf("\n+ 移动磁道数:<%5d> ",All);
    printf("\n+ 平均寻道长度:*%0.2f* ",Aver);
}
//扫描算法(SCAN)
int SCAN(int Han,int DiscL[],int x,int y)
{
    int j,n,k,h,m,All;
    int t=0;
    int Temp;
    int Min;
    int RLine[10]; //将随机生成的磁道数数组Discl[]复制给数组RLine[]
    int Order;
    Order=1;
    k=y;
    m=2;  //控制while语句的执行，即是一定要使当前磁道向内向外都要扫描到
    All=0;  //统计全部的磁道数变量
    CopyL(DiscL,RLine,9);  //复制磁道号到临时数组RLine
    printf("\n+ 按照SCAN算法磁道的访问顺序为:");
    Min=64000;
    for(j=x;j<=y;j++)  //寻找与当前磁道号最短寻道的时间的磁道号
    {
        if(RLine[j]>Han)  //如果第一个随机生成的磁道号大于当前的磁道号，执行下一句
            Temp=RLine[j]-Han;  //求出临时的移动距离
        else
            Temp=Han-RLine[j];  //求出临时的移动距离
        if(Temp<Min)
        {
            Min=Temp;  //Temp临时值赋予Min
            h=j;   //把最近当前磁道号的数组下标赋予h
        }
    }
    All=All+Min;
    printf("%5d",RLine[h]);
    if(RLine[h]>=Han){  //判断磁道的移动方向，即是由里向外还是由外向里
        Order=0;
        t=1;
    }
    Han=RLine[h];
    DelInq(RLine,h,k);  //每个磁道数向前移动一位
    k--;
    while(m>0)
    {
        if(Order==1)  //order是判断磁盘扫描的方向标签，order是1的话，磁道向内移动
        {
            for(j=x;j<=y;j++)
            {
                h=-1;
                Min=64000;
                for(n=x;n<=k;n++)  //判断离当前磁道最近的磁道号
                {
                    if(RLine[n]<=Han)
                    {
                        Temp=Han-RLine[n];
                        if(Temp<Min)
                        {
                            Min=Temp;  //Temp临时值赋予Min
                            h=n;  //把最近当前磁道号的数组下标赋予h
                        }
                    }
                }
                if(h!=-1)
                {
                    All=All+Min;  //叠加移动距离
                    printf("%5d",RLine[h]);
                    Han=RLine[h]; //最近的磁道号作为当前磁道
                    DelInq(RLine,h,k);
                    k--;
                }
            }
            Order=0;  //当完成向内的移动，order赋予0，执行else语句，使磁道向外移动
            m--;  //向内完成一次，m减一次，保证while循环执行两次
        }
        else  //order是0的话，磁道向外移动
        {
            for(j=x;j<=y;j++)
            {
                h=-1;
                Min=64000;
                for(n=x;n<=k;n++)  //判断离当前磁道最近的磁道号
                {
                    if(RLine[n]>=Han)
                    {
                        Temp=RLine[n]-Han;
                        if(Temp<Min)
                        {
                            Min=Temp;   //Temp临时值赋予Min
                            h=n;  //把最近当前磁道号的数组下标赋予h
                        }
                    }
                }
                if(h!=-1)
                {
                    All=All+Min;  //叠加移动距离
                    printf("%5d",RLine[h]);
                    Han=RLine[h];  //最近的磁道号作为当前磁道
                    DelInq(RLine,h,k);
                    k--;
                }
            }
            Order=1;  //当完成向内的移动，order赋予0，执行else语句，使磁道向外移动
            m--;   //向内完成一次，m减一次，保证while循环执行两次
        }
    }
    NAll=NAll+All;
    if((y-x)>5)
    {
        Best[Jage][1]=All;//Best[][1]存放移动磁道数
        Best[Jage][0]=3;//Best[][0]存放算法的序号为:3
        Jage++;//排序序号加1
        Aver=((float)All)/10;//求平均寻道次数
        printf("\n+ 移动磁道数:<%5d> ",All);
        printf("\n+ 平均寻道长度:*%0.2f* ",Aver);
    }
    if(t==1) printf("\n+ 磁道由内向外移动");
    else printf("\n+ 磁道由外向内移动");
    return(Han);
}
//循环扫描算法(CSCAN)
void CSCAN(int Han,int DiscL[])
{

    int j,h,n,Temp,m,k,All,Last,i;
    int RLine[10];  //将随机生成的磁道数数组Discl[]复制给数组RLine[]
    int Min;
    int tmp=0;
    m=2;
    k=9;
    All=0;   //统计全部的磁道数变量
    Last=Han;
    CopyL(DiscL,RLine,9);  //复制磁道号到临时数组RLine
    printf("\n+ 按照CSCAN算法磁道的访问顺序为:");
    while(k>=0)
    {
        for(j=0;j<=9;j++)  //从当前磁道号开始，由内向外搜索离当前磁道最近的磁道号
        {
            h=-1;
            Min=64000;
            for(n=0;n<=k;n++)
            {
                if(RLine[n]>=Han)
                {
                    Temp=RLine[n]-Han;
                    if(Temp<Min)
                    {
                        Min=Temp;
                        h=n;
                    }
                }
            }
            if(h!=-1)
            {
                All=All+Min;  //统计一共移动的距离
                printf("%5d",RLine[h]);
                Han=RLine[h];
                Last=RLine[h];
                DelInq(RLine,h,k);
                k--;
            }
        }
        if(k>=0)
        { tmp=RLine[0];
            for(i=0;i<k;i++)//算出剩下磁道号的最小值
            {
                if(tmp>RLine[i]) tmp=RLine[i];
            }
            Han=tmp;//把最小的磁道号赋给Han
            Temp=Last-tmp;//求出最大磁道号和最小磁道号的距离差
            All=All+Temp;
        }
    }
    Best[Jage][1]=All;//Best[][1]存放移动磁道数
    Best[Jage][0]=4;//Best[][0]存放算法的序号为:4
    Jage++;//排序序号加1
    Aver=((float)All)/10;//求平均寻道次数
    printf("\n+ 移动磁道数:<%5d> ",All);
    printf("\n+ 平均寻道长度:*%0.2f* ",Aver);
}

void PaiXu()
{
    int i,j,Temp;
    for(i=0;i<5;i++)
    {
        for(j=0;j<4;j++)
        {
            if(Best[j][1]>Best[j+1][1])  //如果前一个算法的移动磁道距离大于后一个移动磁道数，执行下面语句
            {
                Temp=Best[j+1][1];    //从这起下三行执行冒泡法将移动距离大小排序，排完后则执行每个算法的排序
                Best[j+1][1]=Best[j][1];
                Best[j][1]=Temp;
                Temp=Best[j+1][0];  //将每个算法的序号用冒泡法排序
                Best[j+1][0]=Best[j][0];
                Best[j][0]=Temp;
            }
        }
    }
}
