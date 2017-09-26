#include <stdio.h>
#include <iostream>
#include <cmath>
int main()
{
    std::puts("please enter a, b and c for `ax^2 + bx + c`:");
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);
    float D = (b * b) - (4 * a * c);
    float x1 = (-b + sqrt(D)) / (2 * a);
    float x2 = (-b - sqrt(D)) / (2 * a);
    if (D > 0)
    {
        std::printf("x1: %f\n", x1);
        std::printf("x2: %f\n", x2);
    }
    else if (D == 0)
    {
        float x = -b / a;
        std::printf("x: %f\n", x);
    }
    else if (D < 0)
    {
        std::puts("no solutions");
    }
}