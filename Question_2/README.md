# Question 2: Process Monitoring & Zombie Prevention

## Conceptual Explanations

* **Process Creation (`fork()`):** 
  I used the `fork()` system call to create a new child process that simulates a heavy web server workload. This allows the parent process to run concurrently and act as a monitor.
* **Zombie Prevention (`waitpid()` & `SIGCHLD`):**
  I implemented an asynchronous signal handler for `SIGCHLD` that executes `waitpid(-1, NULL, WNOHANG)`. This ensures the parent immediately reaps the exit status of terminated children in the background, preventing them from lingering as zombie processes.
* **Signal Handling for Unresponsive Processes (`kill()`):**
  The parent process uses a timeout mechanism to monitor the child's execution state. If the child process remains stuck in an infinite loop, the parent forcefully terminates it by sending a `SIGKILL` signal via the `kill()` system call.

## Executed Commands
* `gcc process_monitor.c -o process_monitor`: Compiled the C source code into an executable.
* `./process_monitor`: Executed the compiled program.
