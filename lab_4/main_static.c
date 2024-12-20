#include <stdio.h>
#include <stdlib.h>
#include "contract.h"

int main() {
    int command;
    double arg1, arg2;

    while (1) {
        printf("Введите команду: ");
        scanf("%d", &command);

        if (command == -1) {
            printf("Завершение программы.\n");
            break;
        } else if (command == 1) {
            scanf("%lf %lf", &arg1, &arg2);
            printf("Результат: %f\n", derivative_one_sided(arg1, arg2));
        } else if (command == 2) {
            scanf("%lf %lf", &arg1, &arg2);
            printf("Результат: %f\n", area_rectangle(arg1, arg2));
        } else {
            printf("Неизвестная команда\n");
        }
    }

    return 0;
}