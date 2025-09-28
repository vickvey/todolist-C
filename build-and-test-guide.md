# 🛠️ Build and Test Guide

## Quick Compilation

```bash
# Basic compilation
gcc main.c database.c -o todolist

# With debugging symbols (recommended for development)
gcc -g -Wall -Wextra main.c database.c -o todolist

# With optimizations (for production)
gcc -O2 -Wall main.c database.c -o todolist
```

## Running the Application

```bash
# Linux/Mac
./todolist

# Windows
todolist.exe
```

## Testing Checklist

### ✅ Basic Functionality

- [ ] Add new tasks with various name/description lengths
- [ ] Mark tasks as completed
- [ ] View all tasks (empty list, single task, multiple tasks)
- [ ] Remove tasks (first, middle, last in list)
- [ ] Clear screen functionality
- [ ] Exit and restart (data persistence)

### ✅ Edge Cases

- [ ] Very long task names/descriptions (should be truncated)
- [ ] Empty task names/descriptions
- [ ] Invalid menu selections
- [ ] Non-numeric input for IDs
- [ ] Operating on non-existent task IDs
- [ ] Memory cleanup (no leaks)

### ✅ File Operations

- [ ] First run (no existing data files)
- [ ] Subsequent runs (loading existing data)
- [ ] File permissions (read/write access)
- [ ] Corrupt data file handling

## Memory Testing (Linux/Mac)

```bash
# Install valgrind
sudo apt install valgrind  # Ubuntu/Debian
brew install valgrind      # macOS

# Run memory leak check
valgrind --leak-check=full --track-origins=yes ./todolist
```

## Cross-Platform Compilation

### Windows (MinGW)

```bash
gcc main.c database.c -o todolist.exe
```

### Windows (MSVC)

```cmd
cl main.c database.c /Fe:todolist.exe
```

### macOS

```bash
clang main.c database.c -o todolist
```

## Expected Output Example

```
╔══════════════════════════════════════════════════════════════╗
║                     📝 TODO LIST MANAGER                     ║
║                   Built with C & Love ❤️                     ║
╠══════════════════════════════════════════════════════════════╣
║  🚀 Welcome to your personal productivity companion!         ║
║  📋 Manage tasks efficiently with our CLI interface          ║
║  💾 All data is automatically saved for you                  ║
╚══════════════════════════════════════════════════════════════╝

🌟 Starting fresh! No previous tasks found.
```

## Files Created by Application

- `task-data.dat` - Binary file containing task data
- `last-used-id.txt` - Text file with the last used ID counter

## Common Issues and Solutions

### Compilation Errors

- **Missing stdio.h**: Ensure all source files are in same directory
- **Undefined reference**: Make sure to compile both .c files together

### Runtime Issues

- **Segmentation fault**: Usually indicates memory access issues - run with valgrind
- **File permission errors**: Ensure write permissions in working directory
- **Input buffer issues**: Fixed with proper `clear_input_buffer()` calls

### Data Persistence Issues

- **Tasks not saving**: Check file write permissions
- **Tasks not loading**: Verify data files exist and are readable
- **Corrupted data**: Delete .dat and .txt files to start fresh
