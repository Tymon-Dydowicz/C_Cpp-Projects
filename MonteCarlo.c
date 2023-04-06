#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int calc_dist(double i, double j){
    double dist = sqrt(i*i + j*j);
    return dist;
}

int main(){
    srand(time(NULL));
    int in;
    int out;
    double rand1;
    double rand2;
    while (1){
        rand1 = (double)rand()/RAND_MAX;
        rand2 = (double)rand()/RAND_MAX;
        if(calc_dist(rand1, rand2) < 1){
            in++;
        }
        out++;
        printf("%f \n", (double)in/out*4);
    }
    return 0;
}