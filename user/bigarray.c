#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define ARRAY_SIZE (1 << 16)
#define MAX_CHILDREN 16


int
main(int argc, char *argv[]) {
    int num_children = 4;
    int *arr = malloc(ARRAY_SIZE * sizeof(int));
    if (arr == 0) {
        printf("Memory allocation failed\n");
        exit(1, "");
    }

    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = i;
    }

    int pids[MAX_CHILDREN];
    int child_index = forkn(num_children, pids);

    if (child_index < 0) {
        printf("forkn failed\n");
        free(arr);
        exit(1, "");
    }

    if (child_index == 0) {
        // Parent process
        int statuses[MAX_CHILDREN];
        int finished = 0;
        if (waitall(&finished, statuses) != 0) {
            printf("waitall failed\n");
            free(arr);
            exit(1, "waitall failed");
        }
        if (finished != num_children) {
            printf("Expected %d children, but got %d\n", num_children, finished);
            free(arr);
            exit(1, "waitall count mismatch");
        }

        int total_sum = 0;
        for (int i = 0; i < finished; i++) {
            total_sum += statuses[i];
        }

        printf("Parent: total sum is %d\n", total_sum);
        free(arr);
        exit(0, " Done");

    } else {
        // Child process
        int start = (child_index - 1) * (ARRAY_SIZE / num_children);
        int end = child_index * (ARRAY_SIZE / num_children);
        int sum = 0;
        for (int i = start; i < end; i++) {
            sum += arr[i];
        }
        printf("Child %d (PID %d): partial sum = %d\n", child_index, getpid(), sum);
        free(arr);
        exit(sum, "");
    }
}

















