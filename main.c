#include <stdio.h>
#include <string.h>
#define MAX_SPLIT (100)
#define MAX_SIZE_LINE 1024
/**
 * 输入分割坐标对, 按行分割内容
 */

int getSplit(int *split);
int splitLine(char *base, char *after_split, int *split, int split_len, int line_len);
int getLine(char *line);

int main() {
    int split[MAX_SPLIT];
    int c_split;
    if ((c_split = getSplit(split)) == 0)
        return 1;
    while (1){
        char new[MAX_SIZE_LINE] = "Hello Wolrd";
        char split_new[MAX_SIZE_LINE] = "";
        int line_len = getLine(new);
        if (line_len == 0)
            break;
        splitLine(new, split_new, split, c_split, line_len);
        printf("split: %s\n", split_new);
    }
    return 0;
}

int getSplit(int *split){
    int c_split;
    printf("Enter the split number: ");
    for (c_split=0; c_split < MAX_SPLIT; c_split++){
        int tmp = 0;
        if (!scanf("%d", &tmp) || tmp < 0)
            break;
        split[c_split] = tmp;
    }
    if (c_split == 0 || c_split % 2 != 0)
        return 0;
    while (getc(stdin) != '\n');
    return c_split;
}

int splitLine(char *base, char *after_split, int *split, int split_len, int line_len) {
    int c_split = 0;
    int stop = 0;
    for (int i=0;i < split_len;i += 2){
        int a = split[i];
        int b = split[i + 1];
        int size = b - a;

        if (b > line_len)
            b = line_len;

        if (a > line_len)
            a = line_len;

        if (a > b){
            int tmp = a;
            a = b;
            b = tmp;
        }

        if (c_split + size > MAX_SIZE_LINE) {
            size = MAX_SIZE_LINE - c_split;
            stop = 1;
        }
        strncpy(after_split, base + a, size);
        after_split += size;
        c_split += size;
        if (stop)
            break;
    }
    return 0;
}

int getLine(char *line){
    int len;
    printf("Enter the split Line: ");
    for (len=0;len < MAX_SIZE_LINE;len++){
        char tmp = getc(stdin);
        if (tmp == '\n')
            break;
        line[len] = tmp;
    }
    line[len] = '\0';
    return len;
}
