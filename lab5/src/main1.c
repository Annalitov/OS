#include <stdio.h>
#include <ctype.h>
#include "lib1.h"

int main(int argc, char const *argv[])
{
    float A = 0,deltaX = 0,B = 0;
    printf("\nWrite:\n [command] [arg1] ... [argN]\n");
    printf("\nCommands:\n");
    printf("\n1 - to compute the derived function f(x) = cos(x) with arguments point and delta\n");
    printf("\n2 - to calculate the area of flat figure with arguments length and width\n");
    printf("\n3 - to end programme\n\n");
    int command = 0, flag = 1;
    while (flag) {
        scanf("%d", &command);
        switch (command) {
        case 1:
            scanf("%f%f", &A, &deltaX);
            printf("Answer: %f\n", Derivative(A, deltaX));
            break;
        
        case 2:
            scanf("%f%f", &A, &B);
            printf("Answer: %f\n", Square(A, B));
            break;
        case 3:
            flag = 0;
            break;

        default:
            printf("wrong command\n");
            break;
        }
        if (flag == 1) {
            printf("\nWrite:\n [command] [arg1] ... [argN]\n");
            printf("\n1 - to compute the derived function f(x) = cos(x) with arguments point and delta\n");
            printf("\n2 - to calculate the area of flat figure with arguments length and width\n");
            printf("\n3 - to end programme\n\n");
        } else {
            printf("programme is completed!\n");
        }
    }
    return 0;
}
