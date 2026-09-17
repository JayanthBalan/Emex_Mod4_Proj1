
# Arbitrary Precision Calculator

## Description

This project implements an Arbitrary Precision Calculator using Doubly Linked Lists.

It performs arithmetic operations on numbers larger than standard C data types can store.

## Operations

- Addition
- Subtraction
- Multiplication
- Division

## Data Structure

Each digit is stored in a node of a Doubly Linked List. This allows the calculator to handle numbers of arbitrary length and perform carry and borrow operations.

## Compilation

```bash
make
```

## Execution

```bash
./apc <operand\1> <operator> <operand\2>
```

Example:

```bash
./apc 123456789 + 987654321
```

Output:

```text
1111111110
```

For multiplication:

```bash
./apc 2222 "*" 435
```

## Clean

```bash
make clean
```

## Files

```text
include/     Header files
src/         Source files
Makefile     Compilation
run-prog.sh  Test script
```

## Testing

> The shell scripts runs user-provided or default input values for all 4 operations of the program.

```bash
bash run-prog.sh 1234 4321
bash run-prog.sh
```
