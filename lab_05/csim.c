// 		金雅各          1102021316
# include "cachelab.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <getopt.h>
typedef struct node1{
    int valid;      // 有效位
    int tag;        // 标记
    int stamp;      // 时间，时间为从0开始的整数，每次读入一条内存访问，仍在缓冲区的有效缓冲行时间就+1，
                    // stamp最大的就是在缓冲区中时间最久的，以此实现LRU替换策略
}cache_line;                // 定义行的数据结构

typedef struct node2{
    int s;          // 缓冲区的组所占的位数
    int S;          // 缓冲区的组数
    int E;          // 每一组的行数
    int b;          // 每一行中的块数
    int hit;        // 缓冲区命中次数
    int miss;       // 未命中次数
    int eviction;   // 替换次数
    cache_line **cache;         // 缓冲区结构体
}Cache;

// 初始化缓冲区
void initCache(Cache *myCache);
// 清空缓冲区，释放缓冲区的内存空间
void clearCache(Cache *myCache);
// 更新缓冲区中的有效行时间,即+1
void updateTime(Cache *mycache);
// 根据地址更新缓冲区
void updateCache(unsigned int address, Cache *myCache);
// verbose为1 表示输出每条内存指令的详细情况
int verbose = 0;

int main(int argc, char **argv)
{
    // 申请一个缓冲区内存
    Cache *myCache = (Cache *)malloc(sizeof(Cache));
    if(myCache == NULL){ // 若申请失败直接退出
        printf("myCache malloc wrong\n");
        exit(-1);
    }
    // 定义文件指针，用以打开指令文件
    FILE *file = NULL;
    int para = 0;
    // 使用getopt函数得到命令行输入的键值对
    // 使用atoi函数将字符串转换为整数
    while((para = getopt(argc, argv, "vs:E:b:t:"))!=-1){
        switch(para){
            case 'v':       // 详细模式
                verbose = 1;
                break;
            case 's':       // 组位数
                myCache->s = atoi(optarg);
                myCache->S = 1<< myCache->s;
                break;
            case 'E':       // 行数
                myCache->E=atoi(optarg);
                break;
            case 'b':       // 块数
                myCache->b=atoi(optarg);
                break; 
            case 't':       // 执行命令文件名
                if((file=fopen(optarg, "r")) == NULL){
                    printf("Open file: %s wrong\n", optarg);		
                    exit(-1);
                }
                break;
            default :
                break;
        }
    }
    // 初始化缓冲区
    initCache(myCache);
    // 定义三个便令以得到每条指令的内容，格式为operation address, size
    char operation;
	unsigned int address;
	int size;
    while(fscanf(file, " %c %x,%d", &operation, &address, &size) != EOF){
        // 若为详细输出，则输出指令的内容
        if(verbose) printf("%c %x,%d", operation, address, size);
        // 根据指令的类型做不同的处理
        switch (operation){
            case 'I': // I为加载指令，由于指令在PC中，无需访问缓冲区，所以不用更新缓冲区
                //updateCache(address, myCache);
                break;
            case 'M': // M为修改数据，包含两部分，加载和写回，故需要两次访问缓冲区
                updateCache(address, myCache);
                updateCache(address, myCache);
                break;
            case 'L': // L为加载数据，访问一次缓冲区
                updateCache(address, myCache);
                break;
            case 'S': // S为写回，访问一次缓冲区
                updateCache(address, myCache);
                break;
            default:
                break;
        }
        if(verbose) printf("\n");
        // 没读入一条操作，需要更新缓冲区中的有效行时间
        updateTime(myCache);
    }
    // 清空缓冲区，释放缓冲区内存
    clearCache(myCache);
    // 关闭文件
    fclose(file);
    // 输出结果
    printSummary(myCache->hit, myCache->miss, myCache->eviction);
    return 0;
}

// 初始化缓冲区
void initCache(Cache *myCache){
    myCache->hit = 0;
    myCache->miss = 0;
    myCache->eviction = 0;
    // 动态申请缓冲区内存空间
    myCache->cache = (cache_line **)malloc(sizeof(cache_line *)*myCache->S);
    for(int i=0; i<myCache->S; i++){
        myCache->cache[i]=(cache_line *)malloc(sizeof(cache_line)*myCache->E);
    }
    // 初始化缓冲区的字段
    for(int i=0; i<myCache->S; i++){
        for(int j=0; j<myCache->E; j++){
            myCache->cache[i][j].valid = 0;
            myCache->cache[i][j].tag = 0;
            myCache->cache[i][j].stamp = 0;
        }
    }
    return ;
}
// 清空缓冲区，释放缓冲区的内存
void clearCache(Cache *myCache){
    for(int i=0; i<myCache->S; i++){
        free(myCache->cache[i]);
    }
    free(myCache->cache);
    free(myCache);
}
// 更新缓冲区中有效行时间
void updateTime(Cache *mycache){
    for(int i=0 ;i<mycache->S; i++){
        for(int j=0; j<mycache->E; j++){
            // 若改行为有效行，则其时间+1
            if(mycache->cache[i][j].valid){
                mycache->cache[i][j].stamp++;
            }
        }
    }
}
// 更新缓冲区
void updateCache(unsigned int address, Cache *myCache){
    // 地址组成为 tag|s_index|block，由于地址为无符号数，所以均为逻辑位移
    // 得到组号
    unsigned s_index =(address>>myCache->b) & ((0xffffffff)>>(32-myCache->s));
    // 得到标记
	unsigned tag = address>>(myCache->s+myCache->b);
	
	// 判断是否组命中
    for(int j=0; j<myCache->E; j++){
        // 在s_index组中查找有效且标志相同的一行
        if(myCache->cache[s_index][j].valid&&myCache->cache[s_index][j].tag==tag){
            // 若找到，表明这一行刚刚使用过，重置其时间为0，命中数+1
            myCache->cache[s_index][j].stamp = 0;
            myCache->hit++;
            if(verbose) printf(" hit");
            return ;
        }
    }
    // 否则未找到，则未命中，再去判断改组中是否有空行，即valid=0
    myCache->miss++;    //未命中次数+1
    for(int j=0; j<myCache->E; j++){
        if(!myCache->cache[s_index][j].valid){
            // 若存在空行，则将该内容加入该空行
            myCache->cache[s_index][j].stamp=0;
            myCache->cache[s_index][j].valid=1;
            myCache->cache[s_index][j].tag=tag;
            if(verbose) printf(" miss");
            return ;
        }
    }
    // 若不存在空行，则需要进行替换，在s_index组中寻找最久未使用的行进行替换
    // 即寻找max_stamp 最大的行进行替换
    int max_stamp = 0;
    int max_j=0;
    for(int j=0; j<myCache->E; j++){
        if(max_stamp < myCache->cache[s_index][j].stamp){
            max_stamp = myCache->cache[s_index][j].stamp;
            max_j = j;
        }
    }
    // 替换掉改行
    myCache->cache[s_index][max_j].stamp = 0;
    myCache->cache[s_index][max_j].tag = tag;
    myCache->cache[s_index][max_j].valid = 1;
    // 替换次数+1
    myCache->eviction ++;
    if(verbose) printf(" miss eviction");
    return ;
}
