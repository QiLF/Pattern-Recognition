#include <stdio.h>

#define N 4
#define VECTOR_LEN 3
typedef struct Data {
    int v[VECTOR_LEN];
    int pattern;
} Data;
Data Dataset[N] = {
        {{0, 0, 1}, 1},
        {{0, 1, 1}, 1},
        {{1, 0, 1}, -1},
        {{1, 1, 1}, -1}
};
void vectorLinearCombination(int *v1, int *v2, int coe1, int coe2, int len) {
    for (int i = 0; i < len; i++) {
        v1[i] = coe1 * v1[i] + coe2 * v2[i];
    }
}

int vectorMultiply(int *v1, int *v2, int len, char *flag) {
    int res = 0;
    for (int i = 0; i < len; i++) {
        res += v1[i] * v2[i];
    }
    if (res > 0) {
        *flag = '+';
    } else if (res == 0) {
        *flag = '0';
    } else {
        *flag = '-';
    }
    return res;
}
void print_titles()
{
    printf("训练样本      W(k)*X)    修正式   W(k+1)    迭代次数");
    printf("\n");
}
void print_vector(int *v, int len)
{
    for(int i =0;i<len;i++)
    {
        printf("%2d ",v[i]);
    }
}
void print_lines(int k, char flag, int*W, int iterations)
{
    printf("X%d ",k+1);
    print_vector(Dataset[k].v,VECTOR_LEN);
    printf("\t%c", flag);
    if(flag!='0'){
        printf("\tW%d%cX%d\t",iterations,flag,k+1);
    }else{
        printf("\tW%d\t", k+1);
    }
    print_vector(W,VECTOR_LEN);
    printf("\t%d\n",iterations);
}
void print_judge_func(int *v, int len)
{
    printf("G(x)= ");
    for(int i=0;i<len;i++)
    {
        if(v[i]!=0) {
            printf("%+d*x%d", v[i], i + 1);
        }
    }
    printf("\n");
}
int main() {
    int W[VECTOR_LEN] = {1, 1, 1};   // 权向量初值
    int Nc = 0; // 连续正确分类的样本个数
    int k = 0;  // 训练样本序号
    int p = 1; // 训练步长
    int iterations = 0; // 迭代次数
    char flag = 0; // 指示判决W*X的符号
    print_titles();
    while (Nc < N) {
        if (Dataset[k].pattern * vectorMultiply(W, Dataset[k].v, VECTOR_LEN, &flag) <= 0) {// 不能正确分类，则修正权向量
            Nc = 0;
            vectorLinearCombination(W, Dataset[k].v, 1, p * Dataset[k].pattern, VECTOR_LEN);
        } else {
            Nc++;   // 连续分类的样本数目+1
        }
        if (k % N == 0) {
            iterations++;  // 每迭代一轮，计数器+1
        }
        print_lines(k,flag,W,iterations);
        k = (k + 1) % N;
    }
    print_judge_func(W, VECTOR_LEN);
    return 0;
}
