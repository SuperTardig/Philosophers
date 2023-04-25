# philosophers
The goal of this 42 school project is to create a simulation that recreates the dining philosophers problem. The project introduces us to the basics of multithreading (and multiprocessing if doing the bonus) and the concept of data races. The mandatory part and the bonus part are suppose to do the exact same thing, with the difference being that the bonus uses multiprocessing instead of multithreading.
## Global
The global requirement for this project are the following:
  - One or more philosophers sit at a table
  - They need to eat, think and sleep
  - To eat, they need to take two forks
  - There is one fork per philosophers
  - The philosophers should try to not die
  - They do not speak to each other
  - Every change to the philosophers should be printed to the terminal. It is formatted this way: <timestamp_in_ms> <philosopher number> <action>
  - The message should not mixed up
## Mandatory
The mandatory requirement for this project are as followed:
  - Each philosopher should be a thread
  - The forks are placed between each philosophers
  - Each fork are protected by a mutex to prevent duplication
## Bonus
The bonus requirement for this project are as followed:
  - Each philosopher should be a process
  - The forks are placed in the middle of the table
  - The forks are represented by a semaphore
## Usage
To use the mandatory part of this project, you need to:
1. Clone this repository
2. Go to `philosophers_42/philo` and use `make`
3. Run `./philo <number of philosophers> <time to die> <time to eat> <time to sleep> [<number of times each philosophers must eat>]`

To use the bonus part of this project, you need to:
1. Clone this repository
2. Go to `philosophers_42/philo_bonus` and use `make`
3. Run `./philo_bonus <number of philosophers> <time to die> <time to eat> <time to sleep> [<number of times each philosophers must eat>]`
