#include <stdio.h>

int findLCM(int a, int b) {
    int res = (a > b) ? a : b;
    while (1) {
        if (res % a == 0 && res % b == 0) return res;
        res++;
    }
}

int main() {
    int n, i, lcm = 1;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst[n], period[n], rem[n];
    printf("Enter the CPU burst times:\n");
    for (i = 0; i < n; i++) scanf("%d", &burst[i]);

    printf("Enter the time periods:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &period[i]);
        lcm = (i == 0) ? period[i] : findLCM(lcm, period[i]);
        rem[i] = 0;
    }

    printf("\nLCM = %d\n", lcm);
    printf("Rate Monotone Scheduling:\nPID\tBurst\tPeriod\n");
    for (i = 0; i < n; i++) printf("%d\t%d\t%d\n", i + 1, burst[i], period[i]);

    printf("\nScheduling occurs for %d ms\n", lcm);

    int last_pid = -1;
    for (int t = 0; t < lcm; t++) {

        for (i = 0; i < n; i++) {
            if (t % period[i] == 0) rem[i] = burst[i];
        }

        int selected = -1;
        int min_p = 10000;

        for (i = 0; i < n; i++) {
            if (rem[i] > 0 && period[i] < min_p) {
                min_p = period[i];
                selected = i;
            }
        }

        if (selected != last_pid) {
            if (selected == -1) printf("%dms onwards: CPU is idle\n", t);
            else printf("%dms onwards: Process %d running\n", t, selected + 1);
            last_pid = selected;
        }

        if (selected != -1) rem[selected]--;
    }
    return 0;
}
