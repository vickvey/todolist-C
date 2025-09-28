# TodoList CLI - A Systems Programming Journey in C

> 🎯 **From Concept to Code**: A complete command-line todo manager built from scratch using pure C and fundamental data structures.

A hands-on exploration of low-level programming concepts, demonstrating how to build production-ready software using only the C standard library. This project showcases manual memory management, file I/O pipelines, and robust CLI design patterns.

## 🚀 Quick Start

```bash
git clone https://github.com/vickvey/todolist-C.git
cd todolist-C
gcc main.c database.c -o todolist
./todolist
```

## ✨ Features & Capabilities

| Feature              | Implementation                         | Learning Focus                      |
| -------------------- | -------------------------------------- | ----------------------------------- |
| **Task Management**  | Add, update, view, delete operations   | Linked list traversal algorithms    |
| **Data Persistence** | Binary + text file storage             | File I/O and serialization patterns |
| **Memory Safety**    | Manual allocation with leak prevention | Understanding heap management       |
| **Input Validation** | Buffer overflow protection             | Defensive programming practices     |
| **Cross-Platform**   | Standard C libraries only              | Portable system programming         |

## 🏗️ Architecture Deep Dive

### Core Data Pipeline

```
User Input → Validation → Linked List → Memory Management → File Persistence
     ↓            ↓            ↓              ↓                ↓
  CLI Menu    Buffer Guard   Dynamic Nodes   malloc/free    Binary I/O
```

### Memory Architecture

**Runtime Structure:**

```
head → [Task Node] → [Task Node] → [Task Node] → NULL
         ↓             ↓             ↓
    [task_data]   [task_data]   [task_data]
    [next ptr]    [next ptr]    [next ptr]
```

**Storage Strategy:**

- **task-data.dat**: Binary serialization of task structs (efficient storage)
- **last-used-id.txt**: Human-readable ID counter (debugging friendly)

### File I/O Pipeline

**Save Operation:**

1. Write ID counter to text file for debugging visibility
2. Serialize linked list nodes to binary format
3. Use `fwrite()` for efficient bulk data transfer
4. Maintain data integrity with error handling

**Load Operation:**

1. Read ID counter from text file
2. Deserialize binary data into memory structures
3. Reconstruct linked list pointers dynamically
4. Handle missing files gracefully (empty list initialization)

## 🔧 Implementation Highlights

### Smart Memory Management

```c
// Strategic allocation with immediate validation
struct node *new_node = malloc(sizeof(struct node));
if (new_node == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
}
```

### Robust Input Handling

```c
// Prevents buffer overflow attacks
void take_string_input(const char prompt[], char dest[], int max_chars) {
    // Implementation ensures safe string handling
}
```

### Modular Design Pattern

```
todo.h          → Shared interface definitions
main.c          → CLI logic & linked list operations
database.c      → Persistence layer & file I/O
```

## 📊 Technical Specifications

| Aspect               | Implementation                    | Rationale                            |
| -------------------- | --------------------------------- | ------------------------------------ |
| **Data Structure**   | Singly Linked List                | O(1) insertion, dynamic sizing       |
| **Storage Format**   | Binary + Text Hybrid              | Performance + debuggability          |
| **Memory Model**     | Manual allocation/deallocation    | Full control over memory usage       |
| **Error Handling**   | Assertions + graceful degradation | Development safety + user experience |
| **Platform Support** | POSIX + Windows compatible        | Maximum portability                  |

## 🎓 Learning Outcomes

### **Systems Programming Fundamentals**

- **Memory Management**: Understanding heap allocation, preventing leaks, debugging with assertions
- **File I/O Mastery**: Binary vs text formats, serialization strategies, error recovery
- **Data Structure Implementation**: Building linked lists from scratch, handling edge cases

### **Software Engineering Practices**

- **Modular Architecture**: Clean separation of concerns, header file organization
- **Error Handling**: Defensive programming, graceful failure modes
- **CLI Design**: User experience considerations, input validation patterns

### **Performance & Optimization**

- **Space Efficiency**: Minimal memory footprint with dynamic allocation
- **I/O Optimization**: Binary storage for fast reads/writes
- **Algorithm Analysis**: Understanding traversal costs and optimization opportunities

## 🛠️ Development Journey

**Phase 1: Core Implementation** (~4 hours)

- Basic CRUD operations
- Linked list management
- Simple CLI interface

**Phase 2: Persistence & Polish** (~ongoing)

- File I/O pipeline design
- Error handling improvements
- Code documentation and cleanup

**Phase 3: Production Readiness**

- Cross-platform testing
- Memory leak validation
- User experience enhancements

## 🔄 Usage Examples

```bash
# Compile and run
gcc main.c database.c -o todolist
./todolist

# Interactive menu system guides you through:
# 1. Add Task    → Creates new task with auto-incremented ID
# 2. Mark Done   → Updates task status by ID
# 3. View Tasks  → Displays all tasks with status indicators
# 4. Remove Task → Deletes task and reorganizes list
# 5. Clear Screen → Utility for better UX
# 0. Exit        → Saves data and terminates safely
```

## 🚀 Extension Ideas

**Immediate Enhancements:**

- Task editing capabilities
- Priority levels and sorting
- Due date management
- Search and filtering

**Advanced Features:**

- Export to CSV/JSON formats
- Multi-user support with file locking
- Command-line argument parsing
- Configuration file support

## 🧪 Testing & Validation

**Memory Safety:**

```bash
# Recommended testing with valgrind (Linux/Mac)
valgrind --leak-check=full --track-origins=yes ./todolist
```

**Cross-Platform Compatibility:**

- ✅ Linux (GCC, Clang)
- ✅ macOS (Apple Clang)
- ✅ Windows (MinGW, MSVC)

## 📝 Author's Note

This project represents a journey back to fundamentals—understanding how high-level abstractions work under the hood. In an era of frameworks and managed languages, building something from scratch in C provides invaluable insights into memory management, system calls, and performance considerations that make you a more thoughtful programmer regardless of your primary stack.

**Key Insight**: The gap between "working code" and "production-ready software" taught me more about software engineering than any theoretical course ever could.

---

## 📫 Connect & Contribute

**Author:** Vivek Kumar ([GitHub](https://github.com/vickvey))  
**License:** MIT - Feel free to fork, modify, and learn!  
**Contributions:** Bug reports, feature suggestions, and improvements are welcome!

> 💡 **For Learning:** Fork this repo and experiment with the code—it's designed to be educational and hackable!
