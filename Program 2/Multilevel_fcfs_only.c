#include <stdio.h>

// Structure to represent a process
struct Process {
    int id;         // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int type;       // 1 for System Process, 2 for User Process
    int completed;  // Flag to check if process is completed (0 = no, 1 = yes)
};

int main() {
    int n, i;
    int completed_count = 0;
    int current_time = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d\n", p[i].id);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Enter Process Type (1 for System, 2 for User): ");
        scanf("%d", &p[i].type);
        p[i].completed = 0; // Initialize as not completed
    }

    // Scheduling Logic
    while (completed_count < n) {
        int selected_process = -1;
        int highest_priority_type = 3; // 1 is highest, 2 is lower
        int earliest_arrival = 999999; // Arbitrary large number

        // Find the appropriate process to execute
        for (i = 0; i < n; i++) {
            if (p[i].completed == 0 && p[i].at <= current_time) {
                // Check priority (System > User)
                if (p[i].type < highest_priority_type) {
                    highest_priority_type = p[i].type;
                    earliest_arrival = p[i].at;
                    selected_process = i;
                }
                // If priority is same, use FCFS (earliest arrival time)
                else if (p[i].type == highest_priority_type && p[i].at < earliest_arrival) {
                    earliest_arrival = p[i].at;
                    selected_process = i;
                }
            }
        }

        // If a process is found, execute it
        if (selected_process != -1) {
            current_time += p[selected_process].bt;
            p[selected_process].ct = current_time;
            p[selected_process].tat = p[selected_process].ct - p[selected_process].at;
            p[selected_process].wt = p[selected_process].tat - p[selected_process].bt;
            p[selected_process].completed = 1;
           
            total_tat += p[selected_process].tat;
            total_wt += p[selected_process].wt;
           
            completed_count++;
        } else {
            // If no process has arrived yet, increment time
            current_time++;
        }
    }

    // Output the results
    printf("\n--- Scheduling Results ---\n");
    printf("PID\tType\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               (p[i].type == 1 ? "SYS" : "USR"),
               p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}