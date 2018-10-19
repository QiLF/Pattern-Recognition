#include <stdio.h>

#define N 4
#define VECTOR_LEN 3
typedef struct Data {
    int v[VECTOR_LEN];
    int pattern;    // 1��ʾw1, 2��ʾw2
} Data;
// ѵ������
Data Dataset[N] = {
        {{0, 0, 1}, 1},
        {{0, 1, 1}, 1},
        {{1, 0, 1}, -1},
        {{1, 1, 1}, -1}
};

// ������������� a*v1+b*v2 ������浽v1
void vectorLinearCombination(int *v1, int *v2, int coe1, int coe2, int len) {
    for (int i = 0; i < len; i++) {
        v1[i] = coe1 * v1[i] + coe2 * v2[i];
    }
}

// ������� rtype: int   ����ķ�����'+','-',��'0'���ظ�����flag
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

// ��ӡ��ͷ
void print_titles() {
    printf("ѵ������      W(k)*X    ����ʽ   W(k+1)    ��������");
    printf("\n");
}

// ��ӡ����
void print_vector(int *v, int len) {
    for (int i = 0; i < len; i++) {
        printf("%2d ", v[i]);
    }
}

// ��ӡһ������
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

// ��ӡ�о�����
void print_judge_func(int *v, int len) {
    printf("Ȩ����W��");
    print_vector(v, VECTOR_LEN);
    printf("  �б���G(x)= ");
    for (int i = 0; i < len; i++) {
        if (v[i] != 0) {
            printf("%+d*x%d", v[i], i + 1);
        }
    }
    printf("\n");
}

int main() {
    int W[VECTOR_LEN] = {1, 1, 1};   // Ȩ������ֵ
    int Nc = 0; // ������ȷ�������������
    int k = 0;  // ѵ���������
    int p = 1; // ѵ������
    int iterations = 0; // ��������
    int error_flag = 0; // �����Ƿ����
    char flag = 0; // ָʾ�о�W*X�ķ���
    int w_label = 1; // ָʾȨ������ӡ���±꣬ ��ʼΪ1�� ÿ����һ��+1
    print_titles();
    while (Nc < N) {
        if (Dataset[k].pattern == 1) {// ��ǰ��������w1��
            if (vectorMultiply(W, Dataset[k].v, VECTOR_LEN, &flag) <= 0) {
                error_flag = 1;    // �������
            } else {
                error_flag = 0;   // ������ȷ
            }
        } else if (Dataset[k].pattern == -1) {// ��ǰ��������w2��
            if (vectorMultiply(W, Dataset[k].v, VECTOR_LEN, &flag) >= 0) {
                error_flag = 1;    // �������
            } else {
                error_flag = 0;   // ������ȷ
            }
        }
        if (k % N == 0) {
            iterations++;  // ÿ����һ�֣�������+1
        }
        if (error_flag == 0) {
            print_lines(k, flag, W, iterations, w_label);
            Nc++;   // ����δ��������������ȷ��������Ŀ+1
        } else {
            vectorLinearCombination(W, Dataset[k].v, 1, p * Dataset[k].pattern, VECTOR_LEN);//����Ȩ����
            print_lines(k, flag, W, iterations, w_label);
            w_label++;
            Nc = 0; // ����������ȷ��������Ŀ�� 0
        }
        k = (k + 1) % N;    // ������һ������
    }
    print_judge_func(W, VECTOR_LEN);
    return 0;
}
