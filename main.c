// To-Do-List CLI app in C Language
// This project uses Singly Linked List Data Structure.

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct task task;
typedef struct node node;

static int last_used_task_id = 0;

struct task
{
    int task_id;
    char task_name[40];
    char task_desc[100];
    bool task_status;
};

struct node
{
    struct task task_data;
    struct node *next;
};

// head of the linked list containing all tasks
struct node *head = NULL;

node *create_node(task *task_ref);
void destroy_node(node **node_pref);
node *get_last_node();
void display_task(task *task_ref);
void add_task(task *task_ref);
node *get_task_by_id(int task_id);
void update_task(int task_id);
void remove_task(int task_id);
void show_tasks();

void welcome();
void show_menu_options();
void take_string_input(const char prompt_msg[], char dest[], int max_char_input);
void exit_message();

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    // helper variables
    task task_h;
    int prompt = -1;
    int task_id_h = -1;

    welcome();

    while (1)
    {
        show_menu_options();

        if (scanf("%d", &prompt) != 1)
        {
            fprintf(stderr, "Error: Failed to read input.\n");
            // Handle the error condition appropriately, e.g., exit the program or prompt the user again
            exit(EXIT_FAILURE);
        }
        getchar();

        switch (prompt)
        {
        case 1:
            // add a new task

            const char msg1[] = "Enter the Task Name (not more than 39 chars): ";
            take_string_input(msg1, task_h.task_name, 40); // Increased by 1 to accommodate null terminator

            const char msg2[] = "Enter the Task Description (not more than 99 chars): ";
            take_string_input(msg2, task_h.task_desc, 100); // Increased by 1 to accommodate null terminator

            // fetch new task id
            task_h.task_id = last_used_task_id + 1;
            last_used_task_id++;
            task_h.task_status = false;

            // add task to linked list
            add_task(&task_h);
            break;
        case 2:
            // mark a task done
            show_tasks();

            printf("Enter the Task Id of the Task you want to mark as Done: ");
            if (scanf("%d", &task_id_h) != 1)
            {
                fprintf(stderr, "Error: Failed to read input.\n");
                // Handle the error condition appropriately, e.g., exit the program or prompt the user again
                exit(EXIT_FAILURE);
            }
            update_task(task_id_h);
            break;
        case 3:
            // show all tasks
            show_tasks();
            break;
        case 4:
            // remove a task
            printf("Enter the Task Id: ");
            if (scanf("%d", &task_id_h) != 1)
            {
                fprintf(stderr, "Error: Failed to read input.\n");
                // Handle the error condition appropriately, e.g., exit the program or prompt the user again
                exit(EXIT_FAILURE);
            }

            remove_task(task_id_h);
            break;
        case 5:
            printf("\033[2J\033[1;1H"); // Clear screen and move cursor to (1,1)
            break;
        case 0:
            // exit the menu
            break;
        }

        if (prompt == 0)
        {
            exit_message();
            break;
        }
    }
    return 0;
}

node *create_node(task *task_ref)
{
    assert(task_ref != NULL); // (1)

    node *new_node = (node *)malloc(sizeof(node));
    assert(new_node != NULL); // (2)

    new_node->task_data = *task_ref;
    new_node->next = NULL;

    return new_node;
}

void destroy_node(node **node_pref)
{
    assert(node_pref != NULL); // (3)

    if (*node_pref != NULL)
        free(*node_pref);
}

node *get_last_node()
{
    if (head == NULL)
        return NULL;

    if (head->next == NULL)
        return head;

    node *curr = head;
    while (curr->next != NULL)
        curr = curr->next;
    return curr;
}

void display_task(task *task_ref)
{
    assert(task_ref != NULL); // (4)
    const char NOT_DONE[] = "Not Done";
    const char DONE[] = "Done";

    printf("\n");
    printf("************************************************************************\n");
    printf("Task Id: %d\n", task_ref->task_id);
    printf("Task Name: %s\n", task_ref->task_name);
    printf("Task Description: %s\n", task_ref->task_desc);
    printf("Task Status: %s\n", (task_ref->task_status == false ? NOT_DONE : DONE));
    printf("************************************************************************\n");
}

void add_task(task *task_ref)
{
    assert(task_ref != NULL); // (5)

    node *last_node = get_last_node();
    if (last_node == NULL)
    {
        head = create_node(task_ref);
        assert(head != NULL); // (6)
    }
    else
    {
        // here last_node is valid
        last_node->next = create_node(task_ref);
        assert(last_node->next != NULL); // (7)
    }
}

node *get_task_by_id(int task_id)
{
    if (head == NULL)
        return NULL;

    node *curr = head;
    while (curr != NULL)
    {
        if (curr->task_data.task_id == task_id)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void update_task(int task_id)
{
    node *req_node = get_task_by_id(task_id);
    if (req_node == NULL)
    {
        fprintf(stdout, "Invalid Task Id!!.\n");
        return;
    }
    // here req_node is found
    req_node->task_data.task_status = true;
    fprintf(stdout, "Marked Task with Task Id %d as done!!\n", task_id);
}

void remove_task(int task_id)
{
    if (head == NULL)
    {
        fprintf(stdout, "There are no tasks to remove!!\n");
        return;
    }
    // atleast 1 node exists

    if (head->task_data.task_id == task_id)
    {
        // head node is the node to be deleted
        node *curr = head;
        head = head->next;
        free(curr);
        printf("Task with Task Id %d is removed.\n", task_id);
        return;
    }

    if (head->next == NULL)
    {
        fprintf(stdout, "Invalid Task Id!!.\n");
        return;
    }
    // atleast 2 nodes exist

    if (head->next->task_data.task_id == task_id)
    {
        // 2nd node to be deleted
        node *temp = head->next;
        head->next = head->next->next;
        temp->next = NULL;
        free(temp);
        printf("Task with Task Id %d is removed.\n", task_id);
        return;
    }

    node *prev = head;
    node *curr = prev->next;

    while (curr != NULL)
    {
        if (curr->task_data.task_id == task_id)
        {
            // here delete node
            prev->next = curr->next;
            curr->next = NULL;
            free(curr);
            printf("Task with Task Id %d is removed.\n", task_id);
            return;
        }

        curr = curr->next;
        prev = prev->next;
    }

    fprintf(stdout, "Invalid Task Id!!.\n");
}

void show_tasks()
{
    if (head == NULL)
    {
        fprintf(stdout, "No Tasks to show!!\n");
        return;
    }

    node *curr = head;
    while (curr != NULL)
    {
        display_task(&curr->task_data);
        curr = curr->next;
    }
}

void welcome()
{
    printf("\n");
    printf("Welcome to To-Do-List CLI App!!\n");
    printf("You can keep log of your tasks and make your day productive.\n");
    printf("Enjoy the App :)\n");
}

void show_menu_options()
{
    printf("\n");
    printf("Press 1: to add a new task.\n");
    printf("Press 2: to mark a task as done.\n");
    printf("Press 3: to show all tasks.\n");
    printf("Press 4: to remove a task.\n");
    printf("Press 5: to clear the screen.\n");
    /// TODO: add more later

    printf("Press 0: to exit the program.\n");
}

void exit_message()
{
    printf("\n");
    printf("Thank you for using this application!!\n");
}

void take_string_input(const char prompt_msg[], char dest[], int max_char_input)
{
    assert(prompt_msg != NULL && dest != NULL);

    printf("%s\n", prompt_msg); // Print the prompt message with a newline
    // Read the input
    if (fgets(dest, max_char_input, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input or end of file reached.\n");
        return;
    }

    // Remove newline character if present
    size_t len = strlen(dest);
    if (len > 0 && dest[len - 1] == '\n')
    {
        dest[len - 1] = '\0';
    }
    else
    {
        clear_input_buffer(); // Clear excess characters from the input buffer
    }
}
