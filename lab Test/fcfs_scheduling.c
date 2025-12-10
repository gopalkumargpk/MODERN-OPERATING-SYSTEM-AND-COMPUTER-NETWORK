#include <stdio.h>

struct Process {
    int id, at, bt, ct, tat, wt;
};

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter AT & BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Sorting by Arrival Time
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    int totalTAT = 0, totalWT = 0;

    printf("\nGantt Chart: ");
    for(int i = 0; i < n; i++) {
        if(time < p[i].at) {
            printf("| Idle ");
            time = p[i].at;
        }
        time += p[i].bt;
        p[i].ct = time;
        printf("| P%d ", p[i].id);
    }
    printf("|\n");

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nTotal TAT = %d", totalTAT);
    printf("\nTotal WT = %d", totalWT);
    printf("\nAverage TAT = %.2f", (float)totalTAT / n);
    printf("\nAverage WT = %.2f\n", (float)totalWT / n);

    return 0;
}
