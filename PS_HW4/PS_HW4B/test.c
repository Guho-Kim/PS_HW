// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #define MAX_PROCESSORS 5
// #define MAX_TASKS 30000

// typedef struct {
//     int taskID;
//     int computationTime;
//     int deadline;
//     int processorID;
// } Task;

// void assignTasks(Task tasks[], int numTasks) {
//     int processorLoad[MAX_PROCESSORS] = {0};  // Tracks the load of each processor
//     int i, j;

//     // Sort tasks based on earliest deadline (EDF)
//     for (i = 0; i < numTasks - 1; i++) {
//         for (j = 0; j < numTasks - i - 1; j++) {
//             if (tasks[j].com > tasks[j + 1].deadline) {
//                 // Swap tasks
//                 Task temp = tasks[j];
//                 tasks[j] = tasks[j + 1];
//                 tasks[j + 1] = temp;
//             }
//         }
//     }

//     // Assign tasks to processors
//     for (i = 0; i < numTasks; i++) {
//         int selectedProcessor = -1;
//         int minLoad = MAX_TASKS + 1;

//         // Find the processor with the minimum load
//         for (j = 0; j < MAX_PROCESSORS; j++) {
//             if (processorLoad[j] < minLoad) {
//                 minLoad = processorLoad[j];
//                 selectedProcessor = j;
//             }
//         }

//         // Assign the task to the selected processor
//         tasks[i].processorID = selectedProcessor + 1;
//         processorLoad[selectedProcessor] += tasks[i].computationTime;
//     }
// }

// void printTaskMapping(Task tasks[], int numTasks) {
//     printf("Task\tProcessor\n");
//     printf("----\t---------\n");
//     for (int i = 0; i < numTasks; i++) {
//         printf("%d\t%d\n", tasks[i].taskID, tasks[i].processorID);
//     }
// }

// int main() {
//     int numTasks;
//     Task tasks[MAX_TASKS];

//     // printf("Enter the number of tasks (between 10 and 30): ");
//     // scanf("%d", &numTasks);
//     numTasks=10;

//     // if (numTasks < 10 || numTasks > 30) {
//     //     printf("Invalid number of tasks. Please try again.\n");
//     //     return 1;
//     // }

//     // Generate random task data
//     // for (int i = 0; i < numTasks; i++) {
//     //     tasks[i].taskID = i + 1;
//     //     tasks[i].computationTime = rand() % 1000 + 1;
//     //     tasks[i].deadline = rand() % 1000 + 1;
//     // }

//     tasks[0].taskID = 1;
//     tasks[0].deadline = 1000;
//     tasks[0].computationTime =300;
    
//     tasks[1].taskID = 2;
//     tasks[1].deadline = 1000;
//     tasks[1].computationTime =20;

//     tasks[2].taskID = 3;
//     tasks[2].deadline = 1000;
//     tasks[2].computationTime =200;
    
//     tasks[3].taskID = 4;
//     tasks[3].deadline = 1000;
//     tasks[3].computationTime =888;

//     tasks[4].taskID = 5;
//     tasks[4].deadline = 1000;
//     tasks[4].computationTime =500;

//     tasks[5].taskID = 6;
//     tasks[5].deadline = 1000;
//     tasks[5].computationTime =630;

//     tasks[6].taskID = 7;
//     tasks[6].deadline = 1000;
//     tasks[6].computationTime =530;

//     tasks[7].taskID = 8;
//     tasks[7].deadline = 1000;
//     tasks[7].computationTime =400;

//     tasks[8].taskID = 9;
//     tasks[8].deadline = 1000;
//     tasks[8].computationTime =500;

//     tasks[9].taskID = 10;
//     tasks[9].deadline = 1000;
//     tasks[9].computationTime =420;






//     // printf("\nGenerated Task Data:\n");
//     // printf("Task\tComputation Time\tDeadline\n");
//     // printf("----\t----------------\t--------\n");
//     // for (int i = 0; i < numTasks; i++) {
//     //     printf("%d\t%d\t\t%d\n", tasks[i].taskID, tasks[i].computationTime, tasks[i].deadline);
//     // }

//     assignTasks(tasks, numTasks);

//     printf("\nTask-Processor Mapping:\n");
//     printTaskMapping(tasks, numTasks);

//     return 0;
// }


#include<stdio.h>
int main(){
    printf("%d\n",1<2);
    printf("%c\n",(1<2)+64);
    printf("%hd\n",1<2);

    if(2) printf("2 is true\n");
    if(-1) printf("-1 is true\n");
    if(1.1) printf("1.1 is true\n");
    if(0.0) printf("0.0 is true\n");
    if(0.1) printf("0.1 is true\n");
    if(0) printf("0 is true\n");
    if(1) printf("1 is true\n");
    if(NULL) printf("null is true\n");

    return 0;
}