#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <math.h>

int recursion (int a, int b) {
    int rest = a%b;
    if (a == b){
        printf("Yes");
    }
    else {
        if (rest == 0) {
        recursion (a/b, b);
        }
        else {
            printf("No");
        }
    }
}

void ex1(){
    printf("Enter your name \n");
    char name[11];
    scanf("%s", name);
    printf("Hello %s! \n", name);
}

void ex2(){
    int value;
    printf("Enter your number \n");
    scanf("%d", &value);
    if (value >= 0) {
        printf("%d \n", value);
    } else {
        printf("%d \n", -value);
    }
}

void ex3(){
    int n1;
    printf("Enter your number ");
    scanf("%d", &n1);
    for (int i=0; i < n1; i++) {
        printf("Hello World! \n");
    }
}

void ex4(){
    int n2;
    printf("Enter your number ");
    scanf("%d", &n2);
    for (int i=0; i < n2; i++) {
        for (int j=0; j < i+1; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void ex5(){
    int h1;
    int m1;
    printf("Enter the number of hours ");
    scanf("%d", &h1);
    printf("Enter the number of minutes ");
    scanf("%d", &m1);
    int s1;
    s1 = 3600*h1 + 60*m1;
    printf("The number of seconds is %d \n", s1);
}

void ex6(){
    float real1;
    printf("Enter the number of kilometers ");
    scanf("%f", &real1);
    float miles;
    printf("The number of miles is %f \n", real1*0.621371192);
}

void ex7(){
    float h2;
    float m2;
    float km1;
    printf("Enter the number of hours ");
    scanf("%f", &h2);
    printf("Enter the number of minutes ");
    scanf("%f", &m2);
    printf("Enter the number of kilometers ");
    scanf("%f", &km1);
    printf("Pace : %f \n", (3600*h2+60*m2)/(km1*0.621371192));
    float real2;
    real2 = km1/(h2+(m2/60));
    printf("Speed : %f \n", real2);
}

void ex8(){
    float r1;
    printf("Enter the radius ");
    scanf("%f", &r1);
    float V1;
    V1 = (4.0/3.0)*M_PI*(pow(r1, 3));
    printf("The volume is %f \n", V1);
}

void ex9(){
    int b3;
    printf("What is the number of books? ");
    scanf("%i", &b3);
    float cost;
    if (b3 > 50) {
        cost = 5 + (b3-1)*0.5 + b3*(40*0.6);
    }
    else {
        cost = 5 + (b3-1)*0.5 + b3*50;
    }
    printf("Total cost for the books is %f zl \n", cost);
}

void ex10(){
    float a4, b4, c4;
    int test;
    printf("Enter the values of a, b, c seperated by a space: ");
    scanf("%f%f%f", &a4, &b4, &c4);
    if (a4+b4<c4) {
        test++;
    }
    if (b4+c4<a4) {
        test++;
    }
    if (a4+c4<b4) {
        test++;
    }
    if (test > 0) {
        printf("No \n");
    }
    else {
        printf("Yes \n");
    }
}

void ex11(){
        char str[40];
    char rstr[40];
    printf("Enter the string: ");
    scanf("%s", &str);
    strcpy(rstr, str);
    strrev(rstr);
    if (strcmp(str, rstr) == 0) {
        printf("Yes \n");
    }
    else {
        printf("No \n");
    }
}

void ex12(){
    int a5, b5;
    printf("Enter two numbers: ");
    scanf("%i %i", &a5, &b5);
    recursion(a5, b5);
}

int main() {
    ex8();
}

