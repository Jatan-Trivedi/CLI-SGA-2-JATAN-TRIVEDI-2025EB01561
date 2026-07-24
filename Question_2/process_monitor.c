#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

void sigchld_handler(int sig) {
    // Reap all terminated child processes to prevent zombies
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    // Register signal handler to prevent zombie processes
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) {
        // Child process: Simulates an infinite unresponsive task
        printf("[Child] PID %d running...\n", getpid());
        while (1) {
            sleep(1);
        }
    } 
    else {
        // Parent process: Monitors execution
        printf("[Parent] Monitoring child PID %d...\n", pid);
        sleep(3); // Monitor period

        // Check if child is still running and terminate if unresponsive
        if (waitpid(pid, NULL, WNOHANG) == 0) {
            printf("[Parent] Child %d unresponsive. Sending SIGKILL...\n", pid);
            kill(pid, SIGKILL);
        }

        // Wait to cleanly reclaim resources
        waitpid(pid, NULL, 0);
        printf("[Parent] Process cleanup complete.\n");
    }

    return 0;
}
