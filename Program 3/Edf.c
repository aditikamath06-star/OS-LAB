#include <stdio.h>


int findGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int findLCM(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a * b) / findGCD(a, b);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst[n], period[n], deadline[n], rem[n], abs_deadline[n];

    for (i = 0; i < n; i++) {
        printf("Process %d - Burst, Deadline, and Period: ", i + 1);
        scanf("%d %d %d", &burst[i], &deadline[i], &period[i]);
        rem[i] = 0;
        abs_deadline[i] = 0;
    }


    int limit = period[0];
    for (i = 1; i < n; i++) {
        limit = findLCM(limit, period[i]);
    }


    printf("\nPID\tBurst\tDeadline\tPeriod\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\n", i + 1, burst[i], deadline[i], period[i]);
    }
    printf("Scheduling occurs for %d ms\n\n", limit);

    for (int t = 0; t < limit; t++) {

        for (i = 0; i < n; i++) {
            if (t % period[i] == 0) {
                rem[i] = burst[i];
                abs_deadline[i] = t + deadline[i];
            }
        }

        int selected = -1;
        int min_deadline = 100000;

        for (i = 0; i < n; i++) {
            if (rem[i] > 0) {
                if (abs_deadline[i] < min_deadline) {
                    min_deadline = abs_deadline[i];
                    selected = i;
                }
            }
        }


        if (selected == -1) {
            printf("%dms: CPU is idle.\n", t);
        } else {
            printf("%dms: Task %d is running.\n", t, selected + 1);
            rem[selected]--;
        }
    }

    return 0;
}
