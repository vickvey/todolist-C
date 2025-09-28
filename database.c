#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"  // Shared header

// Forward declaration for read_list_data (used in load_data)
struct node *read_list_data(const char *filename);

void save_data(const char filename[], struct node *head, int last_used_id) {
    assert(filename != NULL);

    // Save the last_used_id first in a last-used-id.txt file
    FILE *file = fopen(LAST_USED_ID_FILE, "w");
    if (file == NULL) {
        printf("❌ Error: Could not create/open %s for writing!\n", LAST_USED_ID_FILE);
        printf("💡 Make sure you have write permissions in this directory.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", last_used_id);
    fclose(file);
    printf("📝 ID counter saved: %d\n", last_used_id);

    // Now save the linked list data (only task_data, not pointers)
    file = fopen(LIST_DATA_FILENAME, "wb");
    if (file == NULL) {
        printf("❌ Error: Could not create/open %s for writing!\n", LIST_DATA_FILENAME);
        printf("💡 Make sure you have write permissions in this directory.\n");
        exit(EXIT_FAILURE);
    }

    int tasks_saved = 0;
    struct node *current = head;
    while (current != NULL) {
        size_t written = fwrite(&current->task_data, sizeof(struct task), 1, file);
        if (written != 1) {
            printf("❌ Error: Failed to write task data to file!\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        tasks_saved++;
        current = current->next;
    }

    fclose(file);
    printf("💾 Tasks saved: %d task(s) written to %s\n", tasks_saved, LIST_DATA_FILENAME);
}

void load_data(const char filename[], struct node **head_ref, int *last_used_id_ref) {
    assert(head_ref != NULL);
    assert(last_used_id_ref != NULL);
    
    // Load last_used_id
    FILE *id_file = fopen(LAST_USED_ID_FILE, "r");
    if (id_file != NULL) {
        if (fscanf(id_file, "%d", last_used_id_ref) != 1) {
            *last_used_id_ref = 0;  // Default if read fails
            printf("⚠️  Warning: Could not read ID counter, starting from 0\n");
        } else {
            printf("🔄 Loaded ID counter: %d\n", *last_used_id_ref);
        }
        fclose(id_file);
    } else {
        *last_used_id_ref = 0;  // Default if file doesn't exist
        printf("🆕 No previous ID counter found, starting from 0\n");
    }

    // Load the list data
    *head_ref = read_list_data(LIST_DATA_FILENAME);
    
    // Provide user feedback about loaded data
    if (*head_ref != NULL) {
        int loaded_tasks = 0;
        struct node *current = *head_ref;
        while (current != NULL) {
            loaded_tasks++;
            current = current->next;
        }
        printf("📋 Loaded %d task(s) from %s\n", loaded_tasks, LIST_DATA_FILENAME);
    } else {
        printf("🌟 No previous tasks found, starting with empty list\n");
    }
}

int count_tasks()
{
    if (head == NULL) return 0;

    struct node *curr = head;  // Fixed: Added 'struct' keyword
    int count = 0;
    while (curr != NULL)
    {
        curr = curr->next;
        count++;
    }
    return count;
}

// function to read the linked list data from the file
struct node *read_list_data(const char *filename) {
    assert(filename != NULL);
    
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        // No file yet, return empty list (don't exit)
        return NULL;
    }

    struct node *head = NULL;
    struct node *current = NULL;
    struct task temp_task;  // Read into task struct (fixed to match save)
    int tasks_read = 0;

    while (fread(&temp_task, sizeof(struct task), 1, file) == 1) {
        struct node *new_node = malloc(sizeof(struct node));
        if (new_node == NULL) {
            printf("❌ Memory allocation failed while loading tasks!\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        
        new_node->task_data = temp_task;
        new_node->next = NULL;
        tasks_read++;

        if (head == NULL) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = current->next;
        }
    }

    fclose(file);
    
    if (tasks_read > 0) {
        printf("✅ Successfully loaded %d task(s) from storage\n", tasks_read);
    }
    
    return head;
}