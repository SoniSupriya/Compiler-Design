#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 0, j = 0, no = 0, tmpch = 90;  // tmpch = 'Z'
char str[100], left[15], right[15];

void findopr();
void explore();
void fleft(int);
void fright(int);

struct exp {
    int pos;
    char op;
} k[15];

int main() {
    printf("\t\tINTERMEDIATE CODE GENERATION\n\n");
    printf("Enter the Expression: ");
    scanf("%s", str);
    printf("\nThe Intermediate Code:\n");
    findopr();
    explore();
    return 0;
}

void findopr() {
    char ops[] = ":/*+-";
    int idx = 0;

    for (int op_idx = 0; ops[op_idx] != '\0'; op_idx++) {
        for (i = 0; str[i] != '\0'; i++) {
            if (str[i] == ops[op_idx]) {
                k[j].pos = i;
                k[j].op = str[i];
                j++;
            }
        }
    }
}

void explore() {
    int count = j; // number of operators found
    for (i = 0; i < count; i++) {
        fleft(k[i].pos);
        fright(k[i].pos);
        str[k[i].pos] = tmpch--;
        printf("\t%c := %s %c %s\n", str[k[i].pos], left, k[i].op, right);
    }

    // Final assignment (e.g., a := T1)
    fright(-1);
    if (count == 0) {
        fleft(strlen(str));
        printf("\t%s := %s\n", right, left);
        exit(0);
    }
    printf("\t%s := %c\n", right, str[k[count - 1].pos]);
}

void fleft(int x) {
    int w = 0, flag = 0;
    x--;
    while (x != -1 && str[x] != '+' && str[x] != '-' && str[x] != '*' && str[x] != '/' && str[x] != '=' && str[x] != ':') {
        if (str[x] != '$' && flag == 0) {
            left[w++] = str[x];
            left[w] = '\0';
            str[x] = '$';  // Mark as processed
            flag = 1;
        }
        x--;
    }
}

void fright(int x) {
    int w = 0, flag = 0;
    x++;
    while (x != -1 && str[x] != '+' && str[x] != '-' && str[x] != '*' && str[x] != '/' && str[x] != '=' && str[x] != ':' && str[x] != '\0') {
        if (str[x] != '$' && flag == 0) {
            right[w++] = str[x];
            right[w] = '\0';
            str[x] = '$';  // Mark as processed
            flag = 1;
        }
        x++;
    }
}

