#include <stdio.h>

extern double mean(double a, double b);

int main(void)
{

    double v1, v2, m;

    v1 = 5.2;
    v2 = 7.9;

    m = mean(v1, v2);

    printf("The mean of %4.2f, %4.2f is %4.2f\n", v1, v2, m);

    return 0;

}