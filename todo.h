#ifndef TODO_H
#define TODO_H

#include <stdbool.h>

// File configuration constants
#define LIST_DATA_FILENAME "task-data.dat"
#define LAST_USED_ID_FILE "last-used-id.txt"

// Data structure definitions
typedef struct task task;
typedef struct node node;

/**
 * Task structure - holds all information about a single task
 * 
 * Fields:
 * - task_id: Unique identifier for the task
 * - task_name: Short name/title for the task (max 39 chars + null terminator)
 * - task_desc: Detailed description (max 99 chars + null terminator)
 * - task_status: Boolean flag - true for completed, false for pending
 */
struct task {
    int task_id;
    char task_name[40];
    char task_desc[100];
    bool task_status;
};

/**
 * Node structure - represents a single element in the linked list
 * 
 * Fields:
 * - task_data: The actual task information stored in this node
 * - next: Pointer to the next node in the list (NULL for last node)
 */
struct node {
    struct task task_data;
    struct node *next;
};

// Global variables (defined in main.c)
extern struct node *head;     // Head pointer to the linked list
extern int last_used_id;      // Counter for assigning unique task IDs

// Function prototypes for linked list operations (main.c)
node *create_node(task *task_ref);
void destroy_node(node **node_pref);
node *get_last_node();
void display_task(task *task_ref);
void add_task(task *task_ref);
node *get_task_by_id(int task_id);
void update_task(int task_id);
void remove_task(int task_id);
void show_tasks();

// Function prototypes for UI operations (main.c)
void welcome();
void show_menu_options();
void take_string_input(const char prompt_msg[], char dest[], int max_char_input);
void exit_message();
void clear_input_buffer();

// Function prototypes for data persistence operations (database.c)
void save_data(const char filename[], struct node *head, int last_used_id);
void load_data(const char filename[], struct node **head_ref, int *last_used_id_ref);
int count_tasks();

#endif /* TODO_H */