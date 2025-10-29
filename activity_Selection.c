#include <stdio.h>
#include <stdlib.h> // Include for better practice, though not strictly needed here

// --- Data Structure ---

struct ActivityEvent {
    int start_time;
    int finish_time;
};

// --- Sorting Function (O(n^2) Bubble/Selection Sort) ---

void sort_events_by_finish_time(struct ActivityEvent event_array[], int count) {
    int i, j;
    struct ActivityEvent temp_swap;
    
    // This is an O(n^2) sort, which works but is slow for large N.
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (event_array[j].finish_time < event_array[i].finish_time) {
                temp_swap = event_array[j];
                event_array[j] = event_array[i];
                event_array[i] = temp_swap;
            }
        }
    }
}

// --- Greedy Algorithm Implementation ---

void select_maximum_activities(int start_times[], int finish_times[], int count) {
    struct ActivityEvent all_events[count];
    
    // 1. Combine and prepare data
    for (int i = 0; i < count; i++) {
        all_events[i].start_time = start_times[i];
        all_events[i].finish_time = finish_times[i];
    }
    
    // 2. Sort by finish time (the crucial greedy step)
    sort_events_by_finish_time(all_events, count);
    
    printf("\nOptimal Set of Selected Activities:\n");
    
    // 3. Select the first activity
    int last_selected_index = 0;
    printf("Start: %d, Finish: %d\n", all_events[last_selected_index].start_time, all_events[last_selected_index].finish_time);
    
    // 4. Iterate through the rest
    for (int current_index = 1; current_index < count; current_index++) {
        // If the current activity starts AFTER or AT the time the last activity finished
        if (all_events[current_index].start_time >= all_events[last_selected_index].finish_time) {
            printf("Start: %d, Finish: %d\n", all_events[current_index].start_time, all_events[current_index].finish_time);
            last_selected_index = current_index;
        }
    }
}

// --- Main Execution ---

int main() {
    int initial_start_times[] = {5, 1, 3, 0, 5, 8};
    int initial_finish_times[] = {9, 2, 4, 6, 7, 9};
    int total_activities = sizeof(initial_start_times) / sizeof(initial_start_times[0]);
    
    printf("All Activities Provided:\n");
    printf("Start times: ");
    for(int i = 0; i < total_activities; i++) printf("%d ", initial_start_times[i]);
    printf("\nFinish times: ");
    for(int i = 0; i < total_activities; i++) printf("%d ", initial_finish_times[i]);
    printf("\n");
    
    select_maximum_activities(initial_start_times, initial_finish_times, total_activities);
    
    return 0;
}
