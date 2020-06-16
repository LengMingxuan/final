//
// Created by lengm on 2020/6/16.
//

#include "replacementlmx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

main()
{
    int pagen;
    int memoryn;              //可用内存块数为memoryn，页面长度为pagen，
    int choose;                          //3<=memoryn<=5.15<=pagen<=20

    printf("*****************************页*面*置*换*算*法**********************************\n");
    printf("\n\n请输入您要求的内存块数量（范围为3至5）：");
    scanf("%d",&memoryn);
    if(memoryn<3||memoryn>5)
    {
        printf("\n\n输入有误，请重新输入：");
        scanf("%d",&memoryn);
    }
    printf("\n\n输入您要求的页面长度（范围为15至20）：");
    scanf("%d",&pagen);
    if(pagen<15||pagen>20)
    {
        printf("\n\n输入有误，请重新输入：");
        scanf("%d",&pagen);
    }
    printf("\n\n请问您希望用哪种页面置换算法来实现？");
    printf("\n\n  1.FIFO算法     2.LRU算法      3.OPT算法");
    printf("\n\n  请选择您希望使用的算法：");
    scanf("%d",&choose);
    if(choose<1||choose>3)
    {
        printf("\n\n输入有误，请重新输入：");
        scanf("%d",&choose);
    }
    if(choose==1)printf("\n\n您选择的是FIFO算法--");
    if(choose==2)printf("\n\n您选择的是LRU算法--");
    if(choose==3)printf("\n\n您选择的是OPT算法--");
//从用户处获取内存块与页面长度
//****************************************************************************************//

    short times[5]={0,0,0,0,0};
    short pagenumber[20]={0};
    short pagememory[5]={88,88,88,88,88};
    int i;

    printf("\n\n\n由您所确定的页面走向为：");

    srand(time(NULL));
    for(i=0;i<pagen;i++)
    {
        pagenumber[i]=rand()%9+1;
        printf("%2d ",pagenumber[i]);
    }
    printf("\n");

    int want=0;          //want为缺页数
    int now;             //中断数

    pagememory[0]=pagenumber[0];
    printf("第 %2d 步：  ",i=1);
    for(i=0;i<memoryn;i++)
    {
        printf("  %2d",pagememory[i]);
    }
    printf("\n");

    for(i=1;i<pagen;i++)
    {
        if(pagememory[0]!=pagenumber[i])
        {
            pagememory[1]=pagenumber[i];
            now=i+1;
            break;
        }
    }
    printf("第 %2d 步：  ",now);
    for(i=0;i<memoryn;i++)
    {
        printf("  %2d",pagememory[i]);
    }
    printf("\n");

    for(i=2;i<pagen;i++)
    {
        if((pagememory[0]!=pagenumber[i])&&(pagememory[1]!=pagenumber[i]))
        {
            pagememory[2]=pagenumber[i];
            now=i+1;
            break;
        }
    }
    want=3;
    printf("第 %2d 步：  ",now);
    for(i=0;i<memoryn;i++)
    {
        printf("  %2d",pagememory[i]);
    }
    printf("\n");

    if(memoryn==4)
    {
        for(i=3;i<pagen;i++)
        {
            if((pagememory[0]!=pagenumber[i])&&(pagememory[1]!=pagenumber[i])
               &&(pagememory[2]!=pagenumber[i]))
            {
                pagememory[3]=pagenumber[i];
                now=i+1;
                want=4;
                break;
            }
        }
        printf("第 %2d 步：  ",now);
        for(i=0;i<memoryn;i++)
        {
            printf("  %2d",pagememory[i]);
        }
        printf("\n");
    }

    if(memoryn==5)
    {
        for(i=3;i<pagen;i++)
        {
            if((pagememory[0]!=pagenumber[i])&&(pagememory[1]!=pagenumber[i])
               &&(pagememory[2]!=pagenumber[i]))
            {
                pagememory[3]=pagenumber[i];
                now=i+1;
                want=4;
                break;
            }
        }
        printf("第 %2d 步：  ",now);
        for(i=0;i<memoryn;i++)
        {
            printf("  %2d",pagememory[i]);
        }
        printf("\n");

        for(i=4;i<pagen;i++)
        {
            if((pagememory[0]!=pagenumber[i])&&(pagememory[1]!=pagenumber[i])
               &&(pagememory[2]!=pagenumber[i])
               &&(pagememory[3]!=pagenumber[i]))
            {
                pagememory[4]=pagenumber[i];
                now=i+1;
                want=5;
                break;
            }
        }
    }	//如果为五个物理块，则为第四个物理块赋值
    printf("第 %2d 步：  ",now);
    for(i=0;i<memoryn;i++)
    {
        printf("  %2d",pagememory[i]);
    }
    printf("\n");


    if(choose==1)
    {
        int needchange;
        int mn=memoryn;
        int max;
        int j;

        for(i=0;i<memoryn;i++)
        {
            mn--;
            times[i]=mn;
        }               //给时间轴数组设定初值

        for(j=now;j<pagen;j++)
        {
            if((pagenumber[j]!=pagememory[0])&&(pagenumber[j]!=pagememory[1])
               &&(pagenumber[j]!=pagememory[2])
               &&(pagenumber[j]!=pagememory[3])
               &&(pagenumber[j]!=pagememory[4]))
            {
                if(times[0]<=times[1])
                {
                    max=times[1];
                }
                else
                {
                    max=times[0];
                }
                if(max<=times[2])
                {
                    max=times[2];
                }
                if(max<=times[3])
                {
                    max=times[3];
                }
                if(max<=times[4])
                {
                    max=times[4];
                }          //确定时间轴数组里储存的最大时间

                for(i=0;i<memoryn;i++)
                {
                    if(max==times[i])
                    {
                        needchange=i;
                        break;
                    }
                }          //提取出最大时间也就是先进入的页面所对应的物理块号

                pagememory[needchange]=pagenumber[j];

                for(i=0;i<memoryn;i++)
                {
                    if(i==needchange)
                    {
                        times[i]=0;
                    }
                    else
                    {
                        times[i]++;
                    }
                }           //更新时间轴

                want++;       //缺页数进行自增运算
                printf("第 %2d 步：  ",j+1);
                for(i=0;i<memoryn;i++)
                {
                    printf("  %2d",pagememory[i]);
                }
                printf("\n");
            }

            else
            {
                for(i=0;i<memoryn;i++)
                {
                    times[i]++;
                }
            }                //出线相同页面只把时间轴自增一，不做其他操作
        }

        printf("\n\n  FIFO页面置换次数为: %d\n",want);

    }
//FIFO
//***************************************************************************************//

    if(choose==2)
    {
        int needchange;
        int mn=memoryn;
        int max;
        int j;

        for(i=0;i<memoryn;i++)
        {
            mn--;
            times[i]=mn;
        }

        for(j=now;j<pagen;j++)
        {
            if((pagenumber[j]!=pagememory[0])&&(pagenumber[j]!=pagememory[1])
               &&(pagenumber[j]!=pagememory[2])
               &&(pagenumber[j]!=pagememory[3])
               &&(pagenumber[j]!=pagememory[4]))
            {
                if(times[0]<=times[1])
                {
                    max=times[1];
                }
                else
                {
                    max=times[0];
                }
                if(max<=times[2])
                {
                    max=times[2];
                }
                if(max<=times[3])
                {
                    max=times[3];
                }
                if(max<=times[4])
                {
                    max=times[4];
                }          //确定时间轴数组里储存的最大时间


                for(i=0;i<memoryn;i++)
                {
                    if(max==times[i])
                    {
                        needchange=i;
                        break;
                    }
                }

                pagememory[needchange]=pagenumber[j];

                for(i=0;i<memoryn;i++)
                {
                    if(i==needchange)
                    {
                        times[i]=0;
                    }
                    else
                    {
                        times[i]++;
                    }
                }

                want++;
                printf("第 %2d 步：  ",j+1);
                for(i=0;i<memoryn;i++)
                {
                    printf("  %2d",pagememory[i]);
                }
                printf("\n");
            }
            else
            {
                for(i=0;i<memoryn;i++)
                {
                    if(pagenumber[j]==pagememory[i])
                    {
                        times[i]=0;
                    }
                    else
                    {
                        times[i]++;
                    }
                }
            }
        }

        printf("\n\n  LRU页面置换次数为: %d\n",want);
    }

    if(choose==3)
    {
        int needchange;
        int mn=memoryn;
        int max;
        int j,k;
        short future[5]={0,0,0,0,0};

        for(k=now;k<pagen;k++)
        {
            if((pagenumber[k]!=pagememory[0])&&(pagenumber[k]!=pagememory[1])
               &&(pagenumber[k]!=pagememory[2])
               &&(pagenumber[k]!=pagememory[3])
               &&(pagenumber[k]!=pagememory[4]))
            {
                for(j=0;j<memoryn;j++)
                {
                    for(i=k;i<pagen;i++)
                    {
                        if(pagememory[j]!=pagenumber[i])
                        {
                            future[j]++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }                          //
                if(future[0]<future[1])
                {
                    max=future[1];
                }
                else
                {
                    max=future[0];
                }
                if(max<future[2])
                {
                    max=future[2];
                }
                if(max<future[3])
                {
                    max=future[3];
                }
                if(max<future[4])
                {
                    max=future[4];
                }

                for(i=0;i<memoryn;i++)
                {
                    if(max==future[i])
                    {
                        needchange=i;
                        break;
                    }
                }

                pagememory[needchange]=pagenumber[k];

                want++;

                printf("第 %2d 步：  ",k+1);
                for(i=0;i<memoryn;i++)
                {
                    printf("  %2d",pagememory[i]);
                }
                printf("\n");
            }
        }
        printf("\n\n  OPT页面置换次数为: %d\n",want);
    }}
