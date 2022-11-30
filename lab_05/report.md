## 一、实验目的

本实验目的是帮助你理解cache对C语言程序性能的影响。

## 二、报告要求

本报告要求学生解释说明所提交的转置函数是如何针对三种矩阵大小进行了何种优化的，优化效果如何。欢迎你写出你尝试过的所有优化策略，比较它们的效果以及分析效果优劣的原因。

## 三、实现分析
参数为s=5, E=1, b=5的cache
则共有32组，每组一行，每行32字节，由于int整型占4字节，故每行可以存放8个int整数

1. 针对$32 \times 32 (M=32, N=32)$的矩阵
    
    优化策略和优化效果及原因分析。

        由于数组是按照行存放在内存空间中，且Cazhe中每只能存放8个整数，故整个Cache32行共能存放32X32矩阵的8行，那么相隔8行矩阵的行开始的缓存块的index就会重复。
        因此可将32X32的矩阵切分成16个8X8的矩阵分块处理，以消除缓冲区抖动现象
        理论上计算可得,缓冲区miss总数应为 16X8X2=256 次

    **第一次尝试**
    
    直接对8X8的块进行转置
    
    ```
    int i, j ,k;
    for(i=0; i<N ;i+=8){
        for(j=0; j<M; j+=8){
            for(k=i; k<i+8; k++){
                for(int l=j; l<j+8; l++){
                   B[l][k]=A[k][l];
                }
            }
        
    }
    ```
    结果
        
    >  godzilla@godzilla-virtual-machine:~/Code/cs/csapp-cachelab$ ./test-trans -M 32 -N 32
    > 
    >   Function 0 (2 total)
    > Step 1: Validating and generating memory traces
    > Step 2: Evaluating performance (s=5, E=1, b=5)
    > func 0 (Transpose submission): hits:1709, misses:344, evictions:312
    >     
    > Function 1 (2 total)
    > Step 1: Validating and generating memory traces
    > Step 2: Evaluating performance (s=5, E=1, b=5)
    > func 1 (Simple row-wise scan transpose): hits:869, misses:1184, evictions:1152
    >     
    > Summary for official submission (func 0): correctness=1 misses=344
    >     
    > TEST_TRANS_RESULTS=1:344



    测试结果miss的次数是344，和我们的分析相差很大，也没有达到满分的要求。
    
    输出数组A、B的地址发现:
    
        address_A: 0x10d0c0
        address_B: 0x14d0c0
    
    我们可以看到A，B的地址最后16 bits都是相同的，而缓存的index是由倒数5到10的bit组成，
    所以A，B在缓存中的内容会冲突。因为A， B是互为转置，所以冲突A， B只会发生在矩阵对角线上的块。

    在对角线元素复制时B[m][m] = A[m][m]， 会发生A[m]，B[m]之间的冲突。
    复制前， A[m]开始在缓存中，B[m]不在。 复制时， A[m]被B[m]取代。 
    下一个开始复制A[m]又被重新加载进入缓存取代B[m]。这样就会产生2次多余的miss。
    
    上面那种普通分块的实现会在对角块上产生太多的冲突，Ａ，Ｂ矩阵的缓存块相互替换的情况太多。
    我们可以考虑使用本地变量存下Ａ的一行后，再复制给Ｂ，即用本地变量作为缓存存储每个缓存块中的内容。
    本地变量数目不多的时候是放在寄存器上的，因此可以减少访问内存。
    
    **使用局部变量缓冲**
    ```
    int i, j ,k;
    int a0, a1, a2, a3, a4, a5, a6, a7;
    for(i=0; i<N ;i+=8){
        for(j=0; j<M; j+=8){
            for(k=i; k<i+8; k++){
                a0 = A[k][j];
                a1 = A[k][j + 1];
                a2 = A[k][j + 2];
                a3 = A[k][j + 3];
                a4 = A[k][j + 4];
                a5 = A[k][j + 5];
                a6 = A[k][j + 6];
                a7 = A[k][j + 7];
                B[j][k] = a0;
                B[j+1][k] = a1;
                B[j+2][k] = a2;
                B[j+3][k] = a3;
                B[j+4][k] = a4;
                B[j+5][k] = a5;
                B[j+6][k] = a6;
                B[j+7][k] = a7;
            }
        }
    }
    ```
    
    >   godzilla@godzilla-virtual-machine:~/Code/cs/csapp-cachelab$ ./test-trans -M 32 -N 32
    > 
    > Function 0 (2 total)
    > Step 1: Validating and generating memory traces
    > Step 2: Evaluating performance (s=5, E=1, b=5)
    > func 0 (Transpose submission): hits:1765, misses:288, evictions:256
    > 
    > Function 1 (2 total)
    > Step 1: Validating and generating memory traces
    > Step 2: Evaluating performance (s=5, E=1, b=5)
    > func 1 (Simple row-wise scan transpose): hits:869, misses:1184, evictions:1152
    > 
    > Summary for official submission (func 0): correctness=1 misses=288
    > 
    > TEST_TRANS_RESULTS=1:288

    实际的miss次数为287，小于300，优化完成！
    
    
2. 针对$64 \times 64 (M=64, N=64)$的矩阵

    优化策略和优化效果及原因分析。
    
    对于64X64的矩阵，则Cache中总共可以存放4行矩阵的内容。
    因此很容易想到按照4X4矩阵进行划分，同时使用4个局部变量存储
    
    ```
    void transpose_64_64(int M, int N, int A[N][M], int B[M][N]){
        int a0, a1, a2, a3;
        int i, j, k;
        for(i = 0; i < N; i+=4){
            for( j = 0; j < M; j+=4){
                for(k = i; k < i+4; k++){
                    a0 = A[k][j];
                    a1 = A[k][j + 1];
                    a2 = A[k][j + 2];
                    a3 = A[k][j + 3]; 
                    B[j][k] = a0;
                    B[j+1][k] = a1;
                    B[j+2][k] = a2;
                    B[j+3][k] = a3;
                }
            }
        }
    }
    ```
    输出结果
    
    > godzilla@godzilla-virtual-machine:~/Code/cs/csapp-cachelab$ ./test-trans -M 64 -N 64
    > 
    > Function 0 (2 total)
    > Step 1: Validating and generating memory traces
    > Step 2: Evaluating performance (s=5, E=1, b=5)
    > func 0 (Transpose submission): hits:6497, misses:1700, evictions:1668
    > 
    > Function 1 (2 total)
    > Step 1: Validating and generating memory traces
    > Step 2: Evaluating performance (s=5, E=1, b=5)
    > func 1 (Simple row-wise scan transpose): hits:3473, misses:4724, evictions:4692
    > 
    > Summary for official submission (func 0): correctness=1 misses=1700
    > 
    > TEST_TRANS_RESULTS=1:1700

    misses数为1700，很显然不符合满分要求。
    
    分析发现，Cache中每行可以存放8个整形，而我们却只是用了4个，即只使用了一半进行转置。
    
    上网查找相关资料发现，为了能够充分利用cache块，可以在8 × 8 的框架下具体分析操作。即将8X8块再划分为4个4X4块进行转置操作
    
    先将A的前四行全部转置复制到B的前四行，这个时候B的左上角的元素在最终正确的位置。
    B的右上角元素是应该放到左下角的元素。然后，我们在复制后A的后四行到B的过程中，
    利用本地变量将B右上角的内容复制到左下角。
    
    其中每次缓冲区Cache均可以缓冲 4X8的矩阵数据
    对矩阵A的上半4X8采用按行读取，对下半4X8采用按列读取
    
    由于矩阵A无法修改，矩阵B可以修改，且对于4个 4X4 矩阵，第一个与第四个4X4小矩阵的转置与8X8矩阵的转置相同，
    故只需对第二个和第三个矩阵作特殊处理。
    
    ```
    int a0, a1, a2, a3, a4, a5, a6, a7;
    int i, j, k;
    int tmp;
    for (i = 0; i < N; i += 8) {
        for (j = 0; j < M; j += 8){
            // 先划分出8X8大块
            // 对前两个4X4矩阵,即第1与第2个
            for (k = i; k < i + 4; k++) {
                // 缓冲A的一行八个数据到局部变量a0-a7中
                a0 = A[k][j];
                a1 = A[k][j + 1];
                a2 = A[k][j + 2];
                a3 = A[k][j + 3];
                a4 = A[k][j + 4];
                a5 = A[k][j + 5];
                a6 = A[k][j + 6];
                a7 = A[k][j + 7];
                // 对于矩阵B
                //第一个4X4. B的前四列，正常转置 
                B[j][k] = a0;
                B[j + 1][k] = a1;
                B[j + 2][k] = a2;
                B[j + 3][k] = a3;
                // 第二个4X4，转职后的结果先存放到B的第二个4X4矩阵中（但实际应该在第三个4X4矩阵中）
                B[j][k + 4] = a4;
                B[j + 1][k + 4] = a5;
                B[j + 2][k + 4] = a6;
                B[j + 3][k + 4] = a7;
            }
            // 对后两个4X4矩阵,即第3和第4个
            for (k = j; k < j + 4; k++) {
                // 矩阵A 按列读入局部变量a0-a7中
                // 第3个 4X4
                a0 = A[i + 4][k];
                a1 = A[i + 5][k];
                a2 = A[i + 6][k];
                a3 = A[i + 7][k];
                // 第4个 4X4
                a4 = A[i + 4][k + 4];
                a5 = A[i + 5][k + 4];
                a6 = A[i + 6][k + 4];
                a7 = A[i + 7][k + 4];
                // 交换局部变量与B矩阵第2个4X4子块
                tmp = B[k][i + 4]; B[k][i + 4] = a0; a0 = tmp;
                tmp = B[k][i + 5]; B[k][i + 5] = a1; a1 = tmp;
                tmp = B[k][i + 6]; B[k][i + 6] = a2; a2 = tmp;
                tmp = B[k][i + 7]; B[k][i + 7] = a3; a3 = tmp;
                // B矩阵第3个子块
                B[k + 4][i + 0] = a0;
                B[k + 4][i + 1] = a1;
                B[k + 4][i + 2] = a2;
                B[k + 4][i + 3] = a3;
                // B矩阵第4个子块
                B[k + 4][i + 4 + 0] = a4;
                B[k + 4][i + 4 + 1] = a5;
                B[k + 4][i + 4 + 2] = a6;
                B[k + 4][i + 4 + 3] = a7;
            }
        }
    }
    ```
    输出结果
    > godzilla@godzilla-virtual-machine:~/Code/cs/csapp-cachelab$ ./test-trans -M 64 -N 64
    > 
    > Function 0 (2 total)
    > Step 1: Validating and generating memory traces
    > Step 2: Evaluating performance (s=5, E=1, b=5)
    > func 0 (Transpose submission): hits:9137, misses:1108, evictions:1076
    > 
    > Function 1 (2 total)
    > Step 1: Validating and generating memory traces
    > Step 2: Evaluating performance (s=5, E=1, b=5)
    > func 1 (Simple row-wise scan transpose): hits:3473, misses:4724, evictions:4692
    > 
    > Summary for official submission (func 0): correctness=1 misses=1108
    > 
    > TEST_TRANS_RESULTS=1:1108

    测试结果miss的次数是1108<1300，优化完成！
    
3. 针对$61 \times 67 (M=61, N=67)$的矩阵

    优化策略和优化效果及原因分析。
    此时所给的M和N对于cache块来说已经无法像前面的情况一样，可以对齐处理，
    如果要分析的话比较复杂，题目的满分要求也比较低misses < 2000。故我采用变换分块大小来观察。
     
    ```
    int i,j,k,l;
    int block=16;
    for (i = 0; i < N; i += block) {
        for (j = 0; j < M; j += block) {
            for(k = i; k < N && k < i+block; k++){
                for(l = j; l < M && l < j+block; l++){
                    B[l][k]=A[k][l];
                }
            }
        }
    }
    ```
    
    测试不同的块数大小后发现
    
     分块规模N × N | miss数 
     ------ | ------ 
     4X4 | 2426 
     8X8 | 2119 
     16X16 | 1993
     
    在分块规模为16X16时，miss总数已经小于2000，优化结束！

## 四、实验总结

做本实验前，首先需要了解缓冲区能够存放的数据个数。例如本实验共可存放32X8个整数，对于不同的数组，我们需要划分出不同大小的块以尽可能多的利用缓冲区

对于M = 32 , N = 32来说，只需分为8 × 8即可，是最为简单的一种情况，不用什么改动就可完成适配cache，达到目标。

对于M = 64 , N = 64 来说，因为元素增多，导致cache映射的不同，就需要在第一种情况的8 × 8下进一步的分析，难度递增，需要在网上求助才能解答。

而对于M = 61 , N = 64 来说，数组的行列似乎没有规矩，故采用测试的方法，通过测试不同的划分模型，来得到较好的结果。

通过这次实验，可以加深对存储器层次结构和高速缓存工作原理的理解，为后续学习打下铺垫

