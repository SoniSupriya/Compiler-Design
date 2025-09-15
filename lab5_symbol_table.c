#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int x = 0, n, i = 0, j = 0;
    void *mypointer, *T4Tutorials_address[100]; // Increased size for safety
    char ch, c;
    char T4Tutorials_Array2[100]; // Stores input expression

    printf("Input the expression ending with $ sign:\n");
    while ((c = getchar()) != '$' && i < 100) {
        T4Tutorials_Array2[i++] = c;
    }
    n = i - 1;

    printf("\nGiven Expression: ");
    for (i = 0; i <= n; i++) {
        printf("%c", T4Tutorials_Array2[i]);
    }

    printf("\n\nSymbol Table Display\n");
    printf("Symbol\tAddress\t\tType\n\n");

    for (j = 0; j <= n; j++) {
        c = T4Tutorials_Array2[j];
        if (isalpha(c)) {
            mypointer = malloc(sizeof(char));
            T4Tutorials_address[x] = mypointer;
            printf("%c\t%p\tIdentifier\n\n", c, mypointer);
            x++;
        } else if (c == '+' || c == '-' || c == '*' || c == '=') {
            mypointer = malloc(sizeof(char));
            T4Tutorials_address[x] = mypointer;
            printf("%c\t%p\tOperator\n\n", c, mypointer);
            x++;
        }
    }

    // Free allocated memory
    for (i = 0; i < x; i++) {
        free(T4Tutorials_address[i]);
    }

    return 0;
}

