#include <stdio.h>
#include <string.h>

struct op {
    char l;
    char r[20];
} op[10], pr[10];

int main() {
    int i, j, k, n, z = 0, m, a, q;
    char *p, *l;
    char temp, t;
    char *tem;

    printf("Enter the Number of Values: ");
    scanf("%d", &n);

    // Input the left and right parts of the expressions
    for (i = 0; i < n; i++) {
        printf("left: ");
        scanf(" %c", &op[i].l);  // space before %c to consume leftover newline
        printf("right: ");
        scanf(" %s", op[i].r);
    }

    // Display intermediate code
    printf("\nIntermediate Code\n");
    for (i = 0; i < n; i++) {
        printf("%c = %s\n", op[i].l, op[i].r);
    }

    // Dead code elimination: Remove expressions whose results are never used
    for (i = 0; i < n - 1; i++) {
        temp = op[i].l;
        int used = 0;
        for (j = 0; j < n; j++) {
            p = strchr(op[j].r, temp);
            if (p) {
                used = 1;
                break;
            }
        }
        if (used) {
            pr[z].l = op[i].l;
            strcpy(pr[z].r, op[i].r);
            z++;
        }
    }
    // Always keep the last statement (usually the output)
    pr[z].l = op[n - 1].l;
    strcpy(pr[z].r, op[n - 1].r);
    z++;

    printf("\nAfter Dead Code Elimination\n");
    for (k = 0; k < z; k++) {
        printf("%c = %s\n", pr[k].l, pr[k].r);
    }

    // Common subexpression elimination
    for (m = 0; m < z; m++) {
        tem = pr[m].r;
        for (j = m + 1; j < z; j++) {
            p = strstr(pr[j].r, tem);
            if (p) {
                t = pr[j].l;
                pr[j].l = pr[m].l;
                // Replace occurrences of pr[j].l with pr[m].l in other expressions
                for (i = 0; i < z; i++) {
                    l = strchr(pr[i].r, t);
                    while (l) {
                        a = l - pr[i].r;
                        pr[i].r[a] = pr[m].l;
                        l = strchr(pr[i].r, t); // Search again in case multiple occurrences
                    }
                }
            }
        }
    }

    printf("\nAfter Common Subexpression Elimination\n");
    for (i = 0; i < z; i++) {
        printf("%c = %s\n", pr[i].l, pr[i].r);
    }

    // Remove duplicate expressions with same left side and right side
    for (i = 0; i < z; i++) {
        for (j = i + 1; j < z; j++) {
            q = strcmp(pr[i].r, pr[j].r);
            if ((pr[i].l == pr[j].l) && (q == 0)) {
                pr[i].l = '\0'; // Mark for removal
            }
        }
    }

    printf("\nOptimized Code\n");
    for (i = 0; i < z; i++) {
        if (pr[i].l != '\0') {
            printf("%c = %s\n", pr[i].l, pr[i].r);
        }
    }

    return 0;
}

