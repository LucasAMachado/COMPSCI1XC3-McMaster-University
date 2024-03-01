#include <stdio.h>
int main()
{
    const double a1 = 1e18;
    double a2 = 1e18;
    double c1 = 0.1 * a1 - 0.1 * a1;
    double c2 = 0.1 * a2 - 0.1 * a2;
    printf("c1 = % e\n", c1);
    printf("c2 = % e\n", c2);
}