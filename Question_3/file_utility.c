#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct Employee {
    int id;
    char name[20];
    float salary;
};

int main() {
    int fd;
    struct Employee e1 = {101, "Alice", 50000.0};
    struct Employee e2 = {102, "Bob", 60000.0};
    struct Employee update_e = {102, "Bob", 65000.0};
    struct Employee temp;

    // 1. Create and Open File using low-level system call
    fd = open("employee.dat", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0) { 
        perror("open failed"); 
        return 1; 
    }

    // 2. Write initial employee records
    write(fd, &e1, sizeof(struct Employee));
    write(fd, &e2, sizeof(struct Employee));

    // 3. Update specific record without rewriting entire file (Modify record 2)
    off_t offset = 1 * sizeof(struct Employee); // Skip first record
    lseek(fd, offset, SEEK_SET);
    write(fd, &update_e, sizeof(struct Employee));

    // 4. Retrieve record efficiently using lseek and read
    lseek(fd, offset, SEEK_SET);
    read(fd, &temp, sizeof(struct Employee));

    printf("Retrieved Updated Record: ID=%d, Name=%s, Salary=%.2f\n", 
           temp.id, temp.name, temp.salary);

    close(fd);
    return 0;
}
