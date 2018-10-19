#include <stdio.h>

#define N 4
#define VECTOR_LEN 3
typedef struct Data {
    int v[VECTOR_LEN];
    int pattern;    // 1表示w1, 2表示w2
} Data;
// 训练数据
Data Dataset[N] = {
        {{0, 0, 1}, 1},
        {{0, 1, 1}, 1},
        {{1, 0, 1}, -1},
        {{1, 1, 1}, -1}
};

// 向量的线性组合 a*v1+b*v2 结果保存到v1
void vectorLinearCombination(int *v1, int *v2, int coe1, int coe2, int len) {
    for (int i = 0; i < len; i++) {
        v1[i] = coe1 * v1[i] + coe2 * v2[i];
    }
}

// 向量点积 rtype: int   结果的符号以'+','-',或'0'返回给参数flag
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

// 打印表头
void print_titles() {
    printf("训练样本      W(k)*X    修正式   W(k+1)    迭代次数");
    printf("\n");
}

// 打印向量
void print_vector(int *v, int len) {
    for (int i = 0; i < len; i++) {
        printf("%2d ", v[i]);
    }
}

// 打印一行数据
void print_lines(int k, char flag, int *W, int iterations, int w_label) {
    printf("X%d ", k + 1);
    print_vector(Dataset[k].v, VECTOR_LEN);
    printf("\t%c", flag);
    if (flag != '+' && Dataset[k].pattern == 1) {
        printf("\tW%d+X%d\t", w_label, k + 1);
    } else if ((flag != '-') && Dataset[k].pattern == -1) {
        printf("\tW%d-X%d\t", w_label, k + 1);
    } else {
        printf("\tW%d\t", w_label);
    }

    print_vector(W, VECTOR_LEN);
    printf("\t%d\n", iterations);
}

// 打印判决函数
void print_judge_func(int *v, int len) {
    printf("权向量W：");
    print_vector(v, VECTOR_LEN);
    printf("  判别函数G(x)= ");
    for (int i = 0; i < len; i++) {
        if (v[i] != 0) {
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
    int error_flag = 0; // 分类是否出错
    char flag = 0; // 指示判决W*X的符号
    int w_label = 1; // 指示权向量打印的下标， 初始为1， 每更新一次+1
    print_titles();
    while (Nc < N) {
        if (Dataset[k].pattern == 1) {// 当前样本属于w1类
            if (vectorMultiply(W, Dataset[k].v, VECTOR_LEN, &flag) <= 0) {
                error_flag = 1;    // 分类错误
            } else {
                error_flag = 0;   // 分类正确
            }
        } else if (Dataset[k].pattern == -1) {// 当前样本属于w2类
            if (vectorMultiply(W, Dataset[k].v, VECTOR_LEN, &flag) >= 0) {
                error_flag = 1;    // 分类错误
            } else {
                error_flag = 0;   // 分类正确
            }
        }
        if (k % N == 0) {
            iterations++;  // 每迭代一轮，计数器+1
        }
        if (error_flag == 0) {
            print_lines(k, flag, W, iterations, w_label);
            Nc++;   // 分类未出错，连续分类正确的样本数目+1
        } else {
            vectorLinearCombination(W, Dataset[k].v, 1, p * Dataset[k].pattern, VECTOR_LEN);//修正权向量
            print_lines(k, flag, W, iterations, w_label);
            w_label++;
            Nc = 0; // 连续分类正确的样本数目置 0
        }
        k = (k + 1) % N;    // 分类下一个样本
    }
    print_judge_func(W, VECTOR_LEN);
    return 0;
}
