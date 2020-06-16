//
// Created by lengm on 2020/6/16.
//
#include "FCFS_SJFlmx.h"
#include <stdio.h>
#include <stdlib.h>
int MAX;
/*短作业优先算法*/

struct pro
{

    int num;    //进程名
    int arriveTime; //到达时间
    int service;    //服务时间;
    struct pro *next;
};

//函数声明
struct pro* creatList();
void insert(struct pro *head,struct pro *s);
struct pro* searchByAT(struct pro *head,int AT);
void run(struct pro *head);
void del(struct pro* p);
int getCount(struct pro *head,int time);

struct pro* creatList()    //创建链表，按照进程的到达时间排列
{
    struct pro* head=(struct pro*)malloc(sizeof(struct pro));
    head->next=NULL;
    struct pro* s;
    int i;
    for(i=0;i<MAX;i++)
    {
        s=(struct pro*)malloc(sizeof(struct pro));
        printf("请输入到达时间:\n");
        scanf("%d",&(s->arriveTime));
        printf("请输入服务时间:\n");
        scanf("%d",&(s->service));
        s->next=NULL;
        insert(head,s);
    }
    return head;
}

void insert(struct pro *head,struct pro *s)
{
    struct pro *p=searchByAT(head,s->arriveTime);
    s->next=p->next;
    p->next=s;
    return;
}

struct pro* searchByAT(struct pro *head,int AT)
{
    struct pro *p,*q;
    p=head;
    q=head->next;
    while(q!=NULL&&q->arriveTime<=AT)
    {
        p=q;
        q=q->next;
    }
    return p;
}

void del(struct pro* p)
{
    struct pro *tmp;
    tmp=p->next;
    p->next=tmp->next;
    free(tmp);
    return;
}

int getCount(struct pro *head,int time)
{
    int count=0;
    struct pro *p,*q;
    p=head;
    q=p->next;
    while(q!=NULL&&q->arriveTime<=time)
    {
        count++;
        p=q;
        q=q->next;
    }
    return count;
}

struct pro* SJF(struct pro *head,int count)
{
    int min;
    struct pro *p,*q,*flag;
    p=head;
    q=p->next;
    min=q->service;
    flag=p;
    while(count>0)
    {
        if(q->service<min)
        {
            min=q->service;
            flag=p;
        }
        count--;
        p=q;
        q=q->next;
    }
    return flag;
}

void  run(struct pro *head)
{
    int time=0,count,i,j,k,sum1=0,sum2=0;
    struct pro *s,*t;
    while(head->next!=NULL)
    {
        count=getCount(head,time);
        if(count==0)
            time++;
        else if(count==1)
        {
            t=head;
            s=t->next;
            printf("进程名:%d\n",s->num);
            printf("到达时间:%d\n",s->arriveTime);
            printf("服务时间:%d\n\n",s->service);
            printf("开始时间:%d\n",time);
            time+=s->service;
            printf("结束时间:%d\n",time);
            printf("周转时间:%d\n",time-s->arriveTime);
            i=time-s->arriveTime;
            sum1=sum1+i;
            printf("带权周转时间：%d\n",i/s->service);
            sum2=sum2+i/s->service;
            printf("=================================\n");
            del(t);
        }
        else
        {
            t=SJF(head,count);
            s=t->next;
            printf("进程名:%d\n",s->num);
            printf("到达时间:%d\n",s->arriveTime);
            printf("服务时间:%d\n\n",s->service);
            printf("开始时间:%d\n",time);
            time+=s->service;
            printf("结束时间:%d\n",time);
            printf("周转时间:%d\n",time-s->arriveTime);
            i=time-s->arriveTime;
            sum1=sum1+i;
            printf("带权周转时间：%d\n",i/s->service);
            sum2=sum2+i/s->service;
            printf("=================================\n");
            del(t);
        }

    }
    j=sum1/MAX;
    k=sum2/MAX;
    printf("平均周转时间：%d\n",j);
    printf("平均带权周转时间：%d\n",k);
    printf("=================================\n");
}

void main()
{printf("进程数:");
    scanf("%d",&MAX);
    struct pro *head=creatList();
    printf("按短作业优先算法调度运行结果如下:\n");
    run(head);
}
