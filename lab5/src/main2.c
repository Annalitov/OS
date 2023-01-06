#include <stdio.h>
#include <dlfcn.h>
#include "lib1.h"

const char* lib1 = "./liblib1.so";
const char* lib2 = "./liblib2.so";

int main(int argc, char const *argv[])
{
    float A = 0,deltaX = 0,B = 0;
    printf("\nWrite:\n [command] [arg1] ... [argN]\n");
    printf("\nCommands:\n");
    printf("\n0 - to change methods of calculation\n");
    printf("\n1 - to compute the derived function f(x) = cos(x) with arguments point and delta\n");
    printf("\n2 - to calculate the area of flat figure with arguments length and width\n");
    printf("\n3 - to end programme\n\n");
    int command = 0, link = 0, flag = 1;
    void *currentLib = dlopen(lib1, RTLD_LAZY);
    printf("\nCurrent lib is %d\n\n", link);
    float (*Derivative)(float A, float deltaX);
    float (*Square)(float A, float B);
    Derivative = dlsym(currentLib, "Derivative");
    Square = dlsym(currentLib, "Square");
    while (flag) {
        scanf("%d", &command);
        switch (command) {
        case 0:
            dlclose(currentLib);
            if (link == 0) {
                currentLib = dlopen(lib2, RTLD_LAZY);
            } else {
                currentLib = dlopen(lib1, RTLD_LAZY);
            }
            link = !link;
            Derivative = dlsym(currentLib, "Derivative");
            Square = dlsym(currentLib, "Square");
            break;
        
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
            printf("\nCommands:\n");
            printf("\n0 - to change methods of calculation\n");
            printf("\n1 - to compute the derived function f(x) = cos(x) with arguments point and delta\n");
            printf("\n2 - to calculate the area of flat figure with arguments length and width\n");
            printf("\n3 - to end programme\n\n");
            printf("\nCurrent lib is %d\n\n", link);
        } else {
            printf("programme is completed!\n");
        }
    }
    return 0;
}
