#include <stdio.h>

int num = 10;

void addOne() {
    num++;
}

void subtractOne() {
    num--;
}

int getNum() {
    return num;
}

void setNum(int n) {
    num = n;
}

void printNum() {
    printf("%d\n", num);
}