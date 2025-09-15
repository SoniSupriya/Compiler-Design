#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[20], stack[20];

int main() {
    // Parsing table and size arrays
    char m[5][6][3] = {
        {"tb", " ",  " ",  "tb", " ",  " "},
        {" ",   "+tb", " ",  " ",  "n",  "n"},
        {"fc",  " ",  " ",  "fc", " ",  " "},
        {" ",   "n",  "*fc", "a",  "n",  "n"},
        {"i",   " ",  " ",  "(e)", " ",  " "}
    };
    
    int size[5][6] = {
        {2, 0, 0, 2, 0, 0},
        {0, 3, 0, 0, 1, 1},
        {2, 0, 0, 2, 0, 0},
        {0, 1, 3, 0, 1, 1},
        {1, 0, 0, 3, 0, 0}
    };
    
    int i, j, k, n, str1, str2;

    printf("\nEnter the input string: ");
    scanf("%s", s);
    strcat(s, "$");  // Append $ to mark end of input
    
    n = strlen(s);
    stack[0] = '$';
    stack[1] = 'e';
    i = 1; // stack pointer
    j = 0; // input pointer
    
    printf("\nStack\tInput\n");
    printf("______\n\n");

    while ((stack[i] != '$') && (s[j] != '$')) {
        if (stack[i] == s[j]) {
            i--;
            j++;
        }

        // Map stack top symbol to row index str1
        switch (stack[i]) {
            case 'e': str1 = 0; break;
            case 'b': str1 = 1; break;
            case 't': str1 = 2; break;
            case 'f': str1 = 4; break;
            case 'c': str1 = 3; break;
            default:
                printf("\nERROR: Invalid stack symbol '%c'\n", stack[i]);
                exit(1);
        }

        // Map input symbol to column index str2
        switch (s[j]) {
            case 'i': str2 = 0; break;
            case '+': str2 = 1; break;
            case '*': str2 = 2; break;
            case '(': str2 = 3; break;
            case ')': str2 = 4; break;
            case '$': str2 = 5; break;
            default:
                printf("\nERROR: Invalid input symbol '%c'\n", s[j]);
                exit(1);
        }

        // If no production in parsing table
        if (m[str1][str2][0] == '\0' || m[str1][str2][0] == ' ') {
            printf("\nERROR\n");
            exit(0);
        }
        else if (m[str1][str2][0] == 'n') {
            // 'n' means pop the stack symbol without pushing anything
            i--;
        }
        else if (m[str1][str2][0] == 'i') {
            // 'i' means push 'i' on stack
            stack[i] = 'i';
        }
        else {
            // Push the production onto the stack in reverse order
            for (k = size[str1][str2] - 1; k >= 0; k--) {
                stack[i] = m[str1][str2][k];
                i++;
            }
            i--;
        }

        // Print stack and remaining input
        for (k = 0; k <= i; k++) {
            printf("%c", stack[k]);
        }
        printf("\t");
        for (k = j; k <= n; k++) {
            printf("%c", s[k]);
        }
        printf("\n");
    }
    printf("\nSUCCESS\n");
    return 0;
}

