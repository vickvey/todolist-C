#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node node;
typedef struct task task;

const char LIST_DATA_FILENAME[] = "task-data.dat";
const char LAST_USED_ID_FILE[] = "last-used-id.txt";

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

struct node *head = NULL; // head node of the lists
static int last_used_id = 1;

void save_data(const char filename[], struct node *head, int last_used_id);
void load_data(const char filename[], struct node **head_ref, int *last_used_id_ref);

int count_tasks();

int main() {

    return 0;
}

int count_tasks()
{
    if(head == NULL) return 0;

    node *curr = head;
    int count = 0;
    while (curr != NULL)
    {
        curr = curr->next;
        count++;
    }
    return count;
}

void save_data(const char filename[], struct node *head, int last_used_id) {
    assert(filename != NULL); // (1)

    // save the last_used_id first in a last-used-id.txt file
    FILE *file = NULL;
    file = fopen(LAST_USED_ID_FILE, "w");
    if(file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d\n", last_used_id); // write last_used_id in file
    fclose(file);


    // now save the linked list data
    file = fopen(LIST_DATA_FILENAME, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while(head != NULL) {
        fwrite(head, sizeof(node), 1, file);
        head = head->next;
    }

    fclose(file);
}

// function to read the linked list data from the file
struct node *read_list_data(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct node *head = NULL;
    struct node *current = NULL;
    struct node temp;

    while (fread(&temp, sizeof(struct node), 1, file) == 1) {
        struct node *new_node = malloc(sizeof(struct node));
        if (new_node == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        new_node->task_data = temp.task_data;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = current->next;
        }
    }

    fclose(file);
    return head;
}