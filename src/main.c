// To-Do-List CLI app in C Language
// This project uses Singly Linked List Data Structure.

#include "todo.h" // Shared header
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int last_used_id = 0; // Unified name, non-static to share

// head of the linked list containing all tasks
struct node *head = NULL; // Definition here

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
void take_string_input(const char prompt_msg[], char dest[],
                       int max_char_input);
void exit_message();

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int main() {
  // Load existing data at startup
  load_data(LIST_DATA_FILENAME, &head, &last_used_id);

  // helper variables
  task task_h;
  int prompt = -1;
  int task_id_h = -1;

  welcome();

  while (1) {
    show_menu_options();

    if (scanf("%d", &prompt) != 1) {
      printf("❌ Invalid input! Please enter a number.\n");
      clear_input_buffer();
      continue;
    }
    clear_input_buffer(); // Always clear buffer after scanf

    switch (prompt) {
    case 1:
      // add a new task
      printf("\n📝 ═══ Adding New Task ═══\n");

      const char msg1[] = "Enter the Task Name (max 39 chars): ";
      take_string_input(msg1, task_h.task_name, 40);

      const char msg2[] = "Enter the Task Description (max 99 chars): ";
      take_string_input(msg2, task_h.task_desc, 100);

      // fetch new task id
      task_h.task_id = last_used_id + 1;
      last_used_id++;
      task_h.task_status = false;

      // add task to linked list
      add_task(&task_h);
      printf("✅ Task #%d added successfully!\n", task_h.task_id);
      break;

    case 2:
      // mark a task done
      printf("\n✅ ═══ Mark Task as Done ═══\n");
      if (head == NULL) {
        printf("📋 No tasks available to mark as done.\n");
        break;
      }

      show_tasks();
      printf("\nEnter the Task ID to mark as Done: ");
      if (scanf("%d", &task_id_h) != 1) {
        printf("❌ Invalid input! Please enter a valid task ID.\n");
        clear_input_buffer();
        break;
      }
      clear_input_buffer();
      update_task(task_id_h);
      break;

    case 3:
      // show all tasks
      printf("\n📋 ═══ All Tasks ═══\n");
      show_tasks();
      break;

    case 4:
      // remove a task
      printf("\n🗑️  ═══ Remove Task ═══\n");
      if (head == NULL) {
        printf("📋 No tasks available to remove.\n");
        break;
      }

      show_tasks();
      printf("\nEnter the Task ID to remove: ");
      if (scanf("%d", &task_id_h) != 1) {
        printf("❌ Invalid input! Please enter a valid task ID.\n");
        clear_input_buffer();
        break;
      }
      clear_input_buffer();
      remove_task(task_id_h);
      break;

    case 5:
      printf("\033[2J\033[1;1H"); // Clear screen and move cursor to (1,1)
      printf("🧹 Screen cleared!\n");
      break;

    case 0:
      // Save data before exiting
      printf("\n💾 Saving your tasks...\n");
      save_data(LIST_DATA_FILENAME, head, last_used_id);
      printf("✅ Data saved successfully!\n");
      break;

    default:
      printf("❌ Invalid option! Please choose from 0-5.\n");
      break;
    }

    if (prompt == 0) {
      exit_message();
      break;
    }

    // Add a pause for better UX
    printf("\nPress Enter to continue...");
    getchar();
  }
  return 0;
}

node *create_node(task *task_ref) {
  assert(task_ref != NULL);

  node *new_node = malloc(sizeof(node));
  if (new_node == NULL) {
    printf("❌ Memory allocation failed!\n");
    exit(EXIT_FAILURE);
  }

  new_node->task_data = *task_ref;
  new_node->next = NULL;

  return new_node;
}

void destroy_node(node **node_ref) {
  assert(node_ref != NULL && *node_ref != NULL);

  free(*node_ref);
  *node_ref = NULL;
}

node *get_last_node() {
  if (head == NULL)
    return NULL;

  node *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  return current;
}

void display_task(task *task_ref) {
  assert(task_ref != NULL);

  const char *status_icon = task_ref->task_status ? "✅" : "⏳";
  const char *status_text = task_ref->task_status ? "COMPLETED" : "PENDING";

  printf("┌─ Task ID: %d ──────────────────────────\n", task_ref->task_id);
  printf("│ 📝 Name: %s\n", task_ref->task_name);
  printf("│ 📄 Description: %s\n", task_ref->task_desc);
  printf("│ %s Status: %s\n", status_icon, status_text);
  printf("└───────────────────────────────────────\n");
}

void add_task(task *task_ref) {
  assert(task_ref != NULL);

  node *new_node = create_node(task_ref);

  // if the linked list is empty
  if (head == NULL) {
    head = new_node;
    return;
  }

  // if the linked list is not empty
  node *last_node = get_last_node();
  last_node->next = new_node;
}

node *get_task_by_id(int task_id) {
  node *current = head;
  while (current != NULL) {
    if (current->task_data.task_id == task_id) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void update_task(int task_id) {
  node *task_node = get_task_by_id(task_id);
  if (task_node == NULL) {
    printf("❌ Task with ID %d not found!\n", task_id);
    return;
  }

  if (task_node->task_data.task_status) {
    printf("ℹ️  Task '%s' is already completed!\n",
           task_node->task_data.task_name);
    return;
  }

  task_node->task_data.task_status = true;
  printf("✅ Task '%s' marked as completed!\n", task_node->task_data.task_name);
}

void remove_task(int task_id) {
  if (head == NULL) {
    printf("📋 Task list is empty!\n");
    return;
  }

  // if the task to be removed is the first task
  if (head->task_data.task_id == task_id) {
    node *temp = head;
    printf("🗑️  Removing task: '%s'\n", temp->task_data.task_name);
    head = head->next;
    destroy_node(&temp);
    printf("✅ Task removed successfully!\n");
    return;
  }

  // if the task to be removed is not the first task
  node *current = head;
  while (current->next != NULL) {
    if (current->next->task_data.task_id == task_id) {
      node *temp = current->next;
      printf("🗑️  Removing task: '%s'\n", temp->task_data.task_name);
      current->next = current->next->next;
      destroy_node(&temp);
      printf("✅ Task removed successfully!\n");
      return;
    }
    current = current->next;
  }

  printf("❌ Task with ID %d not found!\n", task_id);
}

void show_tasks() {
  if (head == NULL) {
    printf("\n📋 No tasks found! Your todo list is empty.\n");
    printf("💡 Tip: Use option 1 to add your first task.\n");
    return;
  }

  int total_tasks = 0;
  int completed_tasks = 0;

  node *current = head;

  printf("\n");
  while (current != NULL) {
    display_task(&current->task_data);
    printf("\n");
    total_tasks++;
    if (current->task_data.task_status) {
      completed_tasks++;
    }
    current = current->next;
  }

  printf("📊 Summary: %d total task(s) | %d completed | %d pending\n",
         total_tasks, completed_tasks, total_tasks - completed_tasks);
}

void welcome() {
  printf("╔══════════════════════════════════════════════════════════════╗\n");
  printf("║                     📝 TODO LIST MANAGER                     ║\n");
  printf("║                   Built with C & Love ❤️                     ║\n");
  printf("╠══════════════════════════════════════════════════════════════╣\n");
  printf("║  🚀 Welcome to your personal productivity companion!         ║\n");
  printf("║  📋 Manage tasks efficiently with our CLI interface          ║\n");
  printf("║  💾 All data is automatically saved for you                  ║\n");
  printf(
      "╚══════════════════════════════════════════════════════════════╝\n\n");

  // Show startup info
  if (head != NULL) {
    int task_count = count_tasks();
    printf("🔄 Loaded %d existing task(s) from previous session\n", task_count);
  } else {
    printf("🌟 Starting fresh! No previous tasks found.\n");
  }
  printf("\n");
}

void show_menu_options() {
  printf("\n╔═══════════════════════════════════════╗\n");
  printf("║               📋 MENU                 ║\n");
  printf("╠═══════════════════════════════════════╣\n");
  printf("║  1️⃣  ➕ Add New Task                 ║\n");
  printf("║  2️⃣  ✅ Mark Task as Done            ║\n");
  printf("║  3️⃣  📋 Show All Tasks               ║\n");
  printf("║  4️⃣  🗑️  Remove Task                 ║\n");
  printf("║  5️⃣  🧹 Clear Screen                 ║\n");
  printf("║  0️⃣  💾 Save & Exit                  ║\n");
  printf("╚═══════════════════════════════════════╝\n");
  printf("🎯 Choose an option (0-5): ");
}

void take_string_input(const char prompt_msg[], char dest[],
                       int max_char_input) {
  assert(prompt_msg != NULL);
  assert(dest != NULL);
  assert(max_char_input > 0);

  printf("%s", prompt_msg);

  if (fgets(dest, max_char_input, stdin) != NULL) {
    // Remove newline character if present
    size_t len = strlen(dest);
    if (len > 0 && dest[len - 1] == '\n') {
      dest[len - 1] = '\0';
    }

    // Check if input was too long
    if (strlen(dest) == max_char_input - 1 &&
        dest[max_char_input - 1] != '\0') {
      printf("⚠️  Warning: Input was truncated to fit the limit.\n");
      clear_input_buffer();
    }
  } else {
    printf("❌ Error reading input!\n");
    dest[0] = '\0'; // Set empty string as fallback
  }
}

void exit_message() {
  printf(
      "\n╔══════════════════════════════════════════════════════════════╗\n");
  printf("║                        👋 GOODBYE!                           ║\n");
  printf("╠══════════════════════════════════════════════════════════════╣\n");
  printf("║  ✅ All your tasks have been saved successfully              ║\n");
  printf("║  🚀 Thanks for using Todo List Manager!                     ║\n");
  printf("║  💡 Run './todolist' anytime to continue where you left off ║\n");
  printf("╚══════════════════════════════════════════════════════════════╝\n");
  printf("\n🎯 Stay productive! Your future self will thank you. ✨\n\n");
}
