#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "contract.h"

#ifdef __APPLE__
  #define LIB_DERIV "./libderivative.dylib"
  #define LIB_AREA "./libarea.dylib"
#else
  #define LIB_DERIV "./libderivative.so"
  #define LIB_AREA "./libarea.so"
#endif

typedef double (*func_t)(double, double);

int main() {
    int command;
    double arg1, arg2;
    void *handle_deriv, *handle_area;
    func_t derivative_func, area_func;
    char *error;

    // Загружаем объекты из обеих библиотек
    handle_deriv = dlopen(LIB_DERIV, RTLD_LAZY);
    if (!handle_deriv) {
        fprintf(stderr, "dlopen error (derivative): %s\n", dlerror());
        return 1;
    }

    handle_area = dlopen(LIB_AREA, RTLD_LAZY);
    if (!handle_area) {
        fprintf(stderr, "dlopen error (area): %s\n", dlerror());
        dlclose(handle_deriv);
        return 1;
    }

    // Ставим по умолчанию одностороннюю разность и площадь прямоугольника
    derivative_func = (func_t)dlsym(handle_deriv, "derivative_one_sided");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "dlsym error (derivative_one_sided): %s\n", error);
        goto fail;
    }

    area_func = (func_t)dlsym(handle_area, "area_rectangle");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "dlsym error (area_rectangle): %s\n", error);
        goto fail;
    }

    while (1) {
        printf("Введите команду: ");
        scanf("%d", &command);

        // Ввод -1 для выхода
        if (command == -1) {
            printf("Завершение программы.\n");
            break;
        } 
        // 0 - переключаемся на central + triangle
        else if (command == 0) {
            derivative_func = (func_t)dlsym(handle_deriv, "derivative_central");
            if ((error = dlerror()) != NULL) {
                fprintf(stderr, "dlsym error (derivative_central): %s\n", error);
                goto fail;
            }

            area_func = (func_t)dlsym(handle_area, "area_triangle");
            if ((error = dlerror()) != NULL) {
                fprintf(stderr, "dlsym error (area_triangle): %s\n", error);
                goto fail;
            }
            printf("Переключились на central и triangle.\n");
        } 
        // 1 - вызываем derivative_func
        else if (command == 1) {
            scanf("%lf %lf", &arg1, &arg2);
            printf("Результат: %f\n", derivative_func(arg1, arg2));
        } 
        // 2 - вызываем area_func
        else if (command == 2) {
            scanf("%lf %lf", &arg1, &arg2);
            printf("Результат: %f\n", area_func(arg1, arg2));
        } else {
            printf("Неизвестная команда\n");
        }
    }

fail:
    dlclose(handle_area);
    dlclose(handle_deriv);
    return 0;
}