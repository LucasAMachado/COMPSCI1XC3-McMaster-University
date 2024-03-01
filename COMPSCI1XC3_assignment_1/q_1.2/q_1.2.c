#include <stdio.h>
#include <math.h>
// Union to represent a double value and its corresponding bit pattern
union DoubleRepresentation
{
    double value;
    unsigned long long bits;
};

// Function to print the hexadecimal representation of a double value
void printHex(double value)
{
    union DoubleRepresentation dr;
    dr.value = value;
    printf("Hex: %llx\n", dr.bits);
}

int main()
{
    double a1 = 1e18;
    double c1, c2;

    for (double m = 0.1; m <= 0.5; m += 0.1)
    {
        c1 = m * a1 - m * a1;
        c2 = fma(m, a1, -m * a1);

        printf("For m = %.1f:\n", m);
        printf("c1 = %e\n", c1);
        printHex(c1);
        printf("c2 = %e\n", c2);
        printHex(c2);
        printf("\n");
    }

    return 0;
}
