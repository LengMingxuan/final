//
// Created by lengm on 2020/6/16.
//
#include "FCFS_SJFlmx.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct PCB_pro{
    float arrivetime;//����ʱ��
    float servetime;//����ʱ��
    float overtime;//���ʱ��
    float zztime;//��תʱ��
    float dqtime;//��Ȩ��תʱ��
    struct PCB_pro *aa;//�ṹ��ָ��
}FCFS;
FCFS *p,*q,*head=NULL;
struct PCB_pro a[100];
//������ʱ�����ð������

struct PCB_pro *sortarrivetime(struct PCB_pro a[],int n)
{int i,j;
    struct PCB_pro t;
    int flag;
    for(i=1;i<n;i++)
    {flag=0;
        for(j=0;j<n-i;j++)
        {if(a[j].arrivetime>a[j+1].arrivetime)
            {t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
                flag=1;
            }
        }
        if(flag==0)
            break;
    }
    return a;
}
//�����ȷ����㷨
void print(struct PCB_pro a[],int n)
{int i;
    for(i=0;i<n;i++)
    {printf("����ʱ�䣺%f",a[i].arrivetime);
        printf("����ʱ�䣺%f",a[i].servetime);
        printf("���ʱ�䣺%f",a[i].overtime);
        printf("��תʱ�䣺%f",a[i].zztime);
        printf("��Ȩ��תʱ�䣺%f",a[i].dqtime);
        printf("\n");
    }
}

void Fcfs(struct PCB_pro a[],int n)
{int i;
    a[0].overtime=a[0].arrivetime+a[0].servetime;
    a[0].zztime=a[0].overtime+a[0].arrivetime;
    a[0].dqtime=a[0].zztime/a[0].servetime;
    for(i=0;i<n;i++)
    {
        if(a[i].arrivetime<a[i-1].overtime)
        {a[i].overtime=a[i-1].overtime+a[i].servetime;
            a[i].zztime=a[i].overtime-a[i].arrivetime;
            a[i].dqtime=a[i].zztime/a[i].servetime;
        }
        else{
            a[i].overtime=a[i].arrivetime+a[i].servetime;
            a[i].zztime=a[i].overtime-a[i].arrivetime;
            a[i].dqtime=a[i].zztime/a[i].servetime;
        }
    }
    printf("�����ȷ����㷨\n");
    print(a,n);
}
//������
void main(){
    int n,i;
    printf("������\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {printf("����ʱ�䣺");
        scanf("%f",&a[i].arrivetime);
        printf("����ʱ��");
        scanf("%f",&a[i].servetime);
    }
    Fcfs(a,n);
}

