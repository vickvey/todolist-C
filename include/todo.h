#ifndef TODO_H
#define TODO_H

#include <stdbool.h>

#define LIST_DATA_FILENAME "task-data.dat"
#define LAST_USED_ID_FILE "last-used-id.txt"

// Data structure definitions
typedef struct task task;
typedef struct node node;

struct task {
    int task_id;
    char task_name[40];
    char task_desc[100];
    bool task_status;
};

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
