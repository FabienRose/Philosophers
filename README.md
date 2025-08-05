# Philosophers

A C implementation of the dining philosophers problem using POSIX threads, demonstrating synchronization and resource management in concurrent programming.

## Installation

Clone the repository and compile with make:

```bash
git clone https://github.com/FabienRose/philosophers.git
cd philosophers
make
```

## Usage

Run the program with the required arguments:

```bash
# Basic usage (5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep)
./philo 5 800 200 200

# With optional number of times each philosopher must eat
./philo 5 800 200 200 7
```

### Arguments

1. `number_of_philosophers` - Number of philosophers (and forks)
2. `time_to_die` - Time in milliseconds before a philosopher dies of starvation
3. `time_to_eat` - Time in milliseconds it takes for a philosopher to eat
4. `time_to_sleep` - Time in milliseconds it takes for a philosopher to sleep
5. `number_of_times_each_philosopher_must_eat` - Optional: stops simulation when all philosophers have eaten this many times

### Examples

```bash
# 4 philosophers, die after 410ms, eat for 200ms, sleep for 200ms
./philo 4 410 200 200

# 5 philosophers with eating limit of 3 times each
./philo 5 800 200 200 3
```

## Features

- **Thread Safety**: Uses POSIX mutexes to prevent race conditions
- **Death Detection**: Monitor thread continuously checks for philosopher starvation
- **Resource Management**: Proper cleanup of threads and mutexes
- **Deadlock Prevention**: Implements fork picking strategy to avoid deadlocks
- **Real-time Output**: Timestamped status messages for each philosopher action

## Project Structure

```
philosophers/
├── main.c          # Main program entry point
├── philo.h         # Header file with structures and function declarations
├── actions.c       # Philosopher cycle and eating/sleeping functions
├── monitor.c       # Death detection and simulation monitoring
├── set.c           # Initialization and setup functions
├── cleanup.c       # Memory cleanup and mutex destruction
├── utils.c         # Utility functions (time, atoi)
└── Makefile        # Build configuration
```

## License

This project is part of the 42 curriculum and follows the 42 coding standards.
