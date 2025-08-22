# CS 107 Generic C Vector Assignment

A test-driven development implementation of a generic vector data structure in C, demonstrating dynamic memory management, void pointers, and function pointers.

## Learning Objectives

By completing this assignment, you will learn:

- **Dynamic Memory Management**: Practice with `malloc()`, `realloc()`, and `free()`
- **Generic Programming in C**: Using `void*` pointers to create type-agnostic data structures
- **Function Pointers**: Implementing callbacks for custom comparison and cleanup operations
- **Test-Driven Development (TDD)**: Writing tests first, then implementing functionality
- **C Programming Best Practices**: Memory safety, error handling, and modular design

## Project Structure

```
cs_107_generic_c_vector_tdd/
├── src/
│   ├── vector.h          # Vector interface and type definitions
│   ├── vector.c          # Vector implementation
│   └── main.c            # Example usage and demonstrations
├── tests/
│   ├── test_vector.h     # Test function declarations
│   ├── test_vector.c     # Test implementations
│   └── test_runner.c     # Test execution framework
├── Makefile             # Build configuration
└── README.md           # This file
```

## Core Data Structure

The generic vector is implemented using the following structure:

```c
typedef struct {
    void *data;           // Pointer to the actual data array
    size_t size;          // Number of elements currently stored
    size_t capacity;      // Total allocated capacity
    size_t elem_size;     // Size of each element in bytes
    void (*free_fn)(void *); // Optional cleanup function for elements
} vector_t;
```

## Key Features

### 1. Generic Storage
- Stores any data type using `void*` pointers
- Element size specified at creation time
- Type safety maintained through consistent element size

### 2. Dynamic Resizing
- Automatic capacity expansion when needed
- Efficient doubling strategy for amortized O(1) insertions
- Memory shrinking capabilities to optimize space usage

### 3. Memory Management
- Proper allocation and deallocation of internal storage
- Optional cleanup functions for complex data types
- Protection against memory leaks and double-free errors

## Core Functions

### Creation and Destruction
```c
vector_t *vector_new(size_t elem_size, void (*free_fn)(void *));
void vector_free(vector_t *v);
```

### Element Access
```c
void *vector_get(vector_t *v, size_t index);
void vector_set(vector_t *v, size_t index, void *elem);
```

### Modification Operations
```c
void vector_push_back(vector_t *v, void *elem);
void vector_pop_back(vector_t *v);
void vector_insert(vector_t *v, size_t index, void *elem);
void vector_remove(vector_t *v, size_t index);
```

### Utility Functions
```c
size_t vector_size(vector_t *v);
size_t vector_capacity(vector_t *v);
bool vector_empty(vector_t *v);
void vector_clear(vector_t *v);
```

## Test-Driven Development Approach

### 1. Test Categories

**Basic Operations Tests**
- Vector creation and initialization
- Element insertion and retrieval
- Size and capacity management

**Edge Case Tests**
- Empty vector operations
- Boundary index access
- Memory allocation failures

**Memory Management Tests**
- Proper cleanup of resources
- Custom free function usage
- Memory leak prevention

**Complex Data Type Tests**
- Storing structs and pointers
- String storage and management
- Nested data structure handling

### 2. Running Tests

```bash
# Compile and run all tests
make test

# Run specific test categories
make test-basic
make test-memory
make test-edge-cases

# Run with memory debugging
make test-valgrind
```

## Implementation Challenges

### 1. Memory Layout Understanding
- Calculate byte offsets for array indexing
- Properly handle element copying with `memcpy()`
- Manage alignment requirements for different data types

### 2. Generic Function Design
- Use `void*` parameters effectively
- Implement type-safe wrapper macros
- Handle variable element sizes consistently

### 3. Error Handling
- Validate input parameters
- Handle allocation failures gracefully
- Provide meaningful error messages

## Example Usage

### Basic Integer Vector
```c
#include "vector.h"

int main() {
    // Create vector for integers
    vector_t *v = vector_new(sizeof(int), NULL);
    
    // Add elements
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        vector_push_back(v, &values[i]);
    }
    
    // Access elements
    for (size_t i = 0; i < vector_size(v); i++) {
        int *elem = (int*)vector_get(v, i);
        printf("Element %zu: %d\n", i, *elem);
    }
    
    // Cleanup
    vector_free(v);
    return 0;
}
```

### String Vector with Custom Cleanup
```c
void string_free(void *str) {
    char **s = (char**)str;
    free(*s);
}

int main() {
    vector_t *v = vector_new(sizeof(char*), string_free);
    
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    
    vector_push_back(v, &str1);
    vector_push_back(v, &str2);
    
    // Strings will be automatically freed when vector is destroyed
    vector_free(v);
    return 0;
}
```

## Build Instructions

### Prerequisites
- GCC compiler
- Make utility
- Valgrind (optional, for memory debugging)

### Compilation
```bash
# Build the main program
make

# Build with debug symbols
make debug

# Build optimized release version
make release

# Clean build artifacts
make clean
```

### Compilation Flags
- `-Wall -Wextra`: Enable comprehensive warnings
- `-std=c99`: Use C99 standard
- `-g`: Include debugging information
- `-O2`: Optimization for release builds

## Memory Safety

### Best Practices Demonstrated
1. **Always check return values** from memory allocation functions
2. **Match every malloc with free** to prevent memory leaks
3. **Set pointers to NULL** after freeing to avoid double-free errors
4. **Validate parameters** before using them in functions
5. **Use valgrind** to detect memory errors during development

### Common Pitfalls to Avoid
- Accessing freed memory
- Buffer overruns when copying elements
- Forgetting to update size/capacity counters
- Memory leaks in error paths

## Assignment Milestones

### Phase 1: Basic Structure
- [ ] Implement `vector_new()` and `vector_free()`
- [ ] Add basic `push_back()` and `get()` functions
- [ ] Write tests for creation and basic operations

### Phase 2: Core Functionality
- [ ] Implement all CRUD operations
- [ ] Add dynamic resizing logic
- [ ] Handle edge cases and error conditions

### Phase 3: Advanced Features
- [ ] Add custom cleanup function support
- [ ] Implement memory optimization strategies
- [ ] Create comprehensive test suite

### Phase 4: Polish and Documentation
- [ ] Add performance benchmarks
- [ ] Complete error handling
- [ ] Finalize documentation and examples

## Learning Resources

### C Programming Concepts
- Dynamic memory allocation (`malloc`, `realloc`, `free`)
- Pointer arithmetic and void pointers
- Function pointers and callbacks
- Memory layout and alignment

### Software Engineering Practices
- Test-driven development methodology
- Modular design and separation of concerns
- Error handling strategies
- Code documentation and readability

## Assessment Criteria

Your implementation will be evaluated on:

1. **Correctness** (40%): All tests pass and functionality works as specified
2. **Memory Safety** (25%): No memory leaks, proper error handling
3. **Code Quality** (20%): Clean, readable, well-structured code
4. **Test Coverage** (15%): Comprehensive tests covering edge cases

## Getting Help

- Review lecture materials on dynamic memory management
- Study the provided test cases to understand expected behavior
- Use debugging tools like `gdb` and `valgrind`
- Attend office hours for conceptual questions
- Collaborate with classmates on understanding, not implementation

## Submission Guidelines

1. Ensure all tests pass
2. Run valgrind to verify no memory errors
3. Include a brief reflection on challenges faced
4. Submit via the course management system before the deadline

---

**Happy Coding!** This assignment will give you hands-on experience with some of the most important concepts in systems programming. Take your time to understand each concept thoroughly, as these skills form the foundation for more advanced topics in computer science.
