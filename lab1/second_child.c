#include <stdio.h>

#define BUFFER_SIZE 1024


int main() {
    char input[BUFFER_SIZE];
    fgets(input, BUFFER_SIZE, stdin);
    for (int i = 0; input[i]; i++) {
        if (input[i] == ' ') {
            input[i] = '_';
        }
    }
    printf("%s", input);
    return 0;
}