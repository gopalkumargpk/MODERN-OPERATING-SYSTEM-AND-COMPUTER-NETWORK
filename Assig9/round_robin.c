#include <stdio.h>

int main() {
    int n = 5; // number of processes (fixed as per your question)
    
    int at[] = {4, 0, 6, 2, 1}; // Arrival Time: P1, P2, P3, P4, P5
    int bt[] = {7, 5, 3, 9, 4}; // Burst Time: P1, P2, P3, P4, P5
    int rt[5], ct[5], done[5] = {0};

    int tq = 3;  // Time Quantum
    int time = 0, completed = 0;
    
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && rt[i] > 0) {
                executed = 1;
                
                int run = (rt[i] > tq) ? tq : rt[i];
                time += run;
                rt[i] -= run;

                if (rt[i] == 0) {
                    done[i] = 1;
                    ct[i] = time;
                    completed++;
                }
            }
        }

        if (!executed) {
            time++;
        }
    }

    // Display Results
    float sumTAT = 0, sumWT = 0;
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    
    for (int i = 0; i < n; i++) {
        int tat = ct[i] - at[i];
        int wt = tat - bt[i];

        sumTAT += tat;
        sumWT += wt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat, wt);
    }

    printf("\nAverage Turnaround Time = %.2f", sumTAT/n);
    printf("\nAverage Waiting Time = %.2f\n", sumWT/n);

    return 0;
}
