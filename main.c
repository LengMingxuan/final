#include "stdio.h"
#include "bank_lmx.h"
#include "Disk_lmx.h"
#include "FCFS_SJFlmx.h"
#include "replacementlmx.h"

int lmx;

int main() {
    while (1){
    printf("----请选择----\n");
    printf("进程调度算法\n1.先来先服务\n2.短作业优先 \n3：银行家算法\n4：页面置换算法\n5：磁盘寻道算法\n0.退出\n");
    printf("请选择以上序号（0～5）：");
    scanf("%d", &lmx);
    if(lmx == 0) break;
    switch(lmx) {
        case 1:
            FCFSlmx_main();
            break;
        case 2:
            SJFlmx_main();
            break;
        case 3:
            bankerlmx_main();
            break;
        case 4:
            replacementlmx_main();
            break;
        case 5:
            disklmx_main();
            break;
        default:
            return 0;
    }
}
return 0;
}
