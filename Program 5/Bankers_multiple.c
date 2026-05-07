#include <stdio.h>

int main()
{
    int n, m;
    int i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int allocation[n][m];
    int request[n][m];
    int available[m];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    int finish[n];
    int work[m];

    // Initialize Work = Available
    for(i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    // Initialize Finish[]
    for(i = 0; i < n; i++)
    {
        int flag = 0;

        for(j = 0; j < m; j++)
        {
            if(allocation[i][j] != 0)
            {
                flag = 1;
                break;
            }
        }

        if(flag == 1)
            finish[i] = 0;
        else
            finish[i] = 1;
    }

    // Deadlock Detection Algorithm
    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > work[j])
                        break;
                }

                if(j == m)
                {
                    for(j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = 1;
                }
            }
        }
    }

    int deadlock = 0;

    printf("\n");

    for(i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            printf("Process P%d is deadlocked\n", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
    {
        printf("No Deadlock Detected\n");
    }

    return 0;
}