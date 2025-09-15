#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int label[20];
int no = 0;

// Function prototype
int check_label(int k);

int main() {
    FILE *fp1, *fp2;
    char fname[100], op[10], ch;
    char operand1[20], operand2[20], result[20];
    int i = 0, j = 0;

    printf("\nEnter filename of the intermediate code: ");
    scanf("%s", fname);  // no & for arrays

    fp1 = fopen(fname, "r");
    fp2 = fopen("target.txt", "w");
    if (fp1 == NULL || fp2 == NULL) {
        printf("\nError opening the file");
        exit(0);
    }

    // Read till fscanf can read the first word (opcode)
    while (fscanf(fp1, "%s", op) == 1) {
        i++;

        // Print label if exists
        if (check_label(i))
            fprintf(fp2, "\nlabel#%d:\n", i);

        if (strcmp(op, "print") == 0) {
            fscanf(fp1, "%s", result);
            fprintf(fp2, "\tOUT %s\n", result);
        }
        else if (strcmp(op, "goto") == 0) {
            fscanf(fp1, "%s", operand1);
            fprintf(fp2, "\tJMP label#%s\n", operand1);
            label[no++] = atoi(operand1);
        }
        else if (strcmp(op, "[]=") == 0) {
            fscanf(fp1, "%s %s %s", operand1, operand2, result);
            fprintf(fp2, "\tSTORE %s[%s], %s\n", operand1, operand2, result);
        }
        else if (strcmp(op, "uminus") == 0) {
            fscanf(fp1, "%s %s", operand1, result);
            fprintf(fp2, "\tLOAD -%s, R1\n", operand1);
            fprintf(fp2, "\tSTORE R1, %s\n", result);
        }
        else {
            // Operators: * + - / % =
            switch (op[0]) {
                case '*':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tMUL R1, R0\n");
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '+':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tADD R1, R0\n");
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '-':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tSUB R1, R0\n");
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '/':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tDIV R1, R0\n");
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '%':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tMOD R1, R0\n");  // assuming MOD is supported
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '=':
                    fscanf(fp1, "%s %s", operand1, result);
                    fprintf(fp2, "\tSTORE %s, %s\n", operand1, result);
                    break;

                case '>':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tJGT %s, label#%s\n", operand2, result);
                    label[no++] = atoi(result);
                    break;

                case '<':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tJLT %s, label#%s\n", operand2, result);
                    label[no++] = atoi(result);
                    break;

                default:
                    printf("Unknown operation: %s\n", op);
            }
        }
    }

    fclose(fp1);
    fclose(fp2);

    // Print the generated target code
    fp2 = fopen("target.txt", "r");
    if (fp2 == NULL) {
        printf("Error opening the target file\n");
        exit(0);
    }

    while ((ch = fgetc(fp2)) != EOF) {
        putchar(ch);
    }
    fclose(fp2);

    return 0;
}

int check_label(int k) {
    for (int i = 0; i < no; i++) {
        if (k == label[i]) {
            return 1;
        }
    }
    return 0;
}

