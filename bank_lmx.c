//
// Created by lengm on 2020/6/16.
//
# include <stdio.h>
# define lmx 888
#include "bank_lmx.h"
# define MAXvalue 50


int Max[MAXvalue][MAXvalue];
int Allocation[MAXvalue][MAXvalue];
int NEED[MAXvalue][MAXvalue];
int Available[MAXvalue];

//设置参数
int i,j = 0;
int safenum = 0;
int n,m,x=0;

int main()
{   	void check();
    int  p,q,control;
    int req[MAXvalue],Allocation1[MAXvalue][MAXvalue],
            NEED1[MAXvalue][MAXvalue],Available1[MAXvalue];
    printf("=================冷鸣轩================\n");
    printf("请输入进程数:");
    scanf("%d", &n);
    printf("输入资源种量:");
    scanf("%d", &m);
    printf("输入MAXvalueax矩阵:\n");
    for(i=0;i<n; i++)
        for(j=0;j<m; j++)
            scanf("%2d",&Max[i][j]);
    printf("输入Allocation矩阵:\n");
    for(i=0;i<n; i++)
        for(j=0;j<m; j++)
            scanf("%d", &Allocation[i][j]);
    for (i=0;i<n; i++)
        for(j=0;j<m; j++)
            NEED[i][j]=Max[i][j]-Allocation[i][j];
    printf("请输入资源的系统初始值:\n");
    for (j=0;j<m;j++)
        scanf("%d", &Available[j]);
    for (j=0;j<m;j++)
        for(i=0;i<n;i++)
            Available[j]=Available[j]-Allocation[i][j];
    check();
    if (safenum==1)
    {
        for(control=0;;control++)
        {  p=0,q=0;
            printf("输入请求的进程号: ");
            scanf("%d", &i);
            printf("输入该进程的请求资源数组:");
            for(j=0;j<m; j++)
                scanf("%d",&req[j]);
            for(j=0;j<m; j++)
                if(req[j]>NEED[i][j])
                    p=1;
            if(p)
                printf("请求资源大于该进程还需要的资源!\n");
            else
            {
                for(j=0;j<m; j++)
                    if(req[j]>Available[j])
                        q=1;
                if(q)
                    printf("可用资源不能满足请求!\n");
                else
                {
                    for(j=0;j<m; j++)
                    {

                        Available1[j]=Available[j];
                        Allocation1[i][j]=Allocation[i][j];
                        NEED1[i][j]=NEED[i][j];

                        Available[j]=Available[j]-req[j];
                        Allocation[i][j]=Allocation[i][j]+req[j];
                        NEED[i][j]=NEED[i][j]-req[j];
                        if(NEED[i][j]==0)
                            x=x+1;

                    }
                    if(x==m)
                        for(j=0;j<m;j++)
                        {
                            Available[j]=Available[j]+Allocation[i][j];
                            Allocation[i][j]=0;
                            Available1[j]=Available[j];
                            x--;
                        }
                    else x=0;
                    check();
                    if(safenum==0)
                    {for (j=0;j<m; j++)
                        {    Available[j]=Available1[j];
                            Allocation[i][j]=Allocation1[i][j];
                            NEED[i][j]=NEED1[i][j];
                        }
                        printf("不安全！\n");
                    }
                }
            }
            printf("是否继续请求?\n");
        }
    }
}
void check()
{  int k, f, no=0;
    int work[MAXvalue],a[MAXvalue];
    char  finish[MAXvalue];
    safenum=1;
    for(i=0;i<n; i++)
        finish[i]='F';
    for(j=0;j<m; j++)
        work[j]=Available[j];
    k=n;
    do
    {
        for (i=0;i<n; i++)
        {if (finish[i]=='F')
            {  f=1;
                for (j=0;j<m; j++)
                    if (NEED[i][j]>work[j])
                        f=0;
                if (f==1)
                {  finish[i]='T';
                    a[no++]=i;
                    for (j=0;j<m; j++)
                        work[j]=work[j]+Allocation[i][j];
                    Available[j] =work[j];
                }
            }
        }
        k--;
    }while(k>0);
    f=1;
    for (i=0;i<n; i++)
    {
        if (finish[i]=='F')
        {
            f=0;
            break;
        }
    }
    if (f==0)
    {
        printf("不安全状态！\n");
        safenum=0;
    }
    else
    {

        printf("安全！");
        printf("安全序列:");
        for (i=0;i<n;i++)
            printf ("%d ",a[i]);
        printf("\n");
        printf("进程");
        printf("   ");
        printf("  MAXvalueax  ");
        printf("   ");
        printf("Allocation");
        printf("    ");
        printf("NEED");
        printf("    ");
        printf("Available");
        printf("\n");
        for (i=0;i<n; i++)
        {
            printf("%2d",i);
            printf("     ");
            for(j=0;j<m; j++)
                printf("%2d",Max[i][j]);
            printf("     ");
            for(j=0;j<m; j++)
                printf("%2d",Allocation[i][j]);
            printf("     ");
            for(j=0;j<m; j++)
                printf("%2d",NEED[i][j]);
            printf("     ");
            for(j=0;j<m; j++){
                if(i>0)
                    break;
                printf("%2d",Available[j]);
            }
            printf("\n");
        }
    }
}
