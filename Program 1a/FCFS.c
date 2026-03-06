#include<stdio.h>
struct Processes
{
    int ID,AT,BT,CT,TAT,WT;
};
int main()
{
    int n;
    printf("Number of processes:");
    scanf("%d",&n);
    struct Processes p[n];
    for(int i=0;i<n;i++)
    {
        p[i].ID=i+1;
        printf("Arrival time of P%d:",p[i].ID);
        scanf("%d",&p[i].AT);
        printf("Burst time of P%d:",p[i].ID);
        scanf("%d",&p[i].BT);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].AT>p[j+1].AT)
            {
                struct Processes temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    int time_passed=0,sumTAT=0,sumWT=0;
    for (int i=0;i<n;i++)
    {
        if(time_passed<p[i].AT)
        {
            time_passed=p[i].AT;
        }
        p[i].CT=time_passed+p[i].BT;
        p[i].TAT=p[i].CT-p[i].AT;
        p[i].WT=p[i].TAT-p[i].BT;
        time_passed=p[i].CT;
        sumTAT+=p[i].TAT;
        sumWT+=p[i].WT;
    }
    printf("ID\tAT\tBT\tCT\tTAT\tWT");
    for (int i=0;i<n;i++)
    {
        printf("\n%d\t%d\t%d\t%d\t%d\t%d",p[i].ID,p[i].AT,p[i].BT,p[i].CT,p[i].TAT,p[i].WT);
    }
    printf("\nAverage TAT:%.2f\n",(float)sumTAT/n);
    printf("Average WT:%.2f",(float)sumWT/n);
}
