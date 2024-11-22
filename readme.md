# Philosophers

## Objective

The **Philosophers** project introduces a classic concurrency problem to teach the basics of threading and synchronization in C. The goal is to simulate philosophers dining at a table while following strict rules to avoid race conditions and deadlocks.

This project helped us learn and apply concepts like:

- **Creating and managing threads** with the `pthread` library.
- Using **mutexes** to control access to shared resources (forks).
- Preventing **race conditions** by ensuring **thread-safe data handling**.
- Implementing **deadlock prevention** techniques.
- Managing precise action timing with **gettimeofday**.
- Cleaning up resources properly to avoid memory leaks.

## Project Overview

In this simulation:

- Philosophers cycle through three states:
  - **Eating**
  - **Sleeping**
  - **Thinking**
- Each philosopher has a fork on their left and right.

### Rules:
- To eat, a philosopher must pick up **both forks** (mutexes).
- After eating, they must put the forks back.
- Philosophers cannot starve; they must eat within a specified time.

We implemented this simulation using **threads** for each philosopher and additional **monitoring threads** to ensure the rules are followed.

## What We Did

### Input Validation
- Checked that the program starts with valid arguments (e.g., number of philosophers, times for actions).

### Initialization
- Allocated memory for philosophers and forks.
- Set up mutexes and shared data structures.

### Thread Management
- Created threads for philosophers to perform their routines.
- Added a monitoring thread (doctor) to check for starving philosophers.
- Optionally used a waiter thread to track if all philosophers have eaten enough.

### Philosopher Actions
- Simulated philosophers alternating between eating, sleeping, and thinking.
- Used mutexes to control fork usage and avoid race conditions.

### Logging
- Logged actions like "eating," "sleeping," "thinking," and "death" in a thread-safe way.

### Time Management
- Used `gettimeofday` and a custom `simulate_action` function to handle precise timing for actions.

### Cleanup
- Freed all allocated memory and destroyed mutexes to prevent resource leaks.

## What We Learned

### Threading Basics
- Learned how to create and manage threads using `pthread_create` and `pthread_join`.

### Mutexes
- Used mutexes to synchronize access to shared resources.
- Gained an understanding of initializing, locking, and unlocking mutexes.

### Concurrency Challenges
- Developed strategies to avoid deadlocks and race conditions.
- Designed systems to ensure thread safety.

### Time Management
- Learned to manage precise timing for delays in the simulation.

### Resource Management
- Practiced allocating and freeing resources dynamically.
- Ensured proper cleanup to avoid memory leaks or dangling mutexes.

## How to Run the Project

### Requirements
- A **Unix-based system** with support for `pthread`.
- A **C compiler** that supports the flags `-Wall -Wextra -Werror`.

### Compilation
To compile the program, run:
```bash
make
```

This will generate the `philo` executable.

### Usage
Run the program with the following syntax:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- `<number_of_philosophers>`: Number of philosophers (and forks).
- `<time_to_die>`: Time (in ms) a philosopher can live without eating.
- `<time_to_eat>`: Time (in ms) a philosopher takes to eat.
- `<time_to_sleep>`: Time (in ms) a philosopher takes to sleep.
- `[number_of_times_each_philosopher_must_eat]` (optional): Simulation ends when all philosophers eat this many times.

### Examples

**Run with mandatory arguments:**
```bash
./philo 5 800 200 200
```
This starts a simulation with 5 philosophers.

**Run with the optional argument:**
```bash
./philo 5 800 200 200 3
```
This runs the simulation until each philosopher eats 3 times.

### Cleanup
To clean object files and the binary:
```bash
make fclean
```
