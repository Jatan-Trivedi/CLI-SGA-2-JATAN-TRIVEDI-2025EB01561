# Question 3: Secure File Processing Utility

## System Call Explanations

* **`open()`**: Initializes a direct file access descriptor (`fd`) with read/write flags (`O_CREAT | O_RDWR | O_TRUNC`) to create `employee.dat` securely at the system level.
* **`write()`**: Directly commits the binary bytes of the `Employee` structs to disk storage without the overhead of buffered standard C library functions.
* **`lseek()`**: Repositions the read/write byte pointer directly to specific offsets (e.g., skipping the first struct). This is the key to updating specific records efficiently without having to rewrite the entire file.
* **`read()`**: Extracts the targeted byte chunks from the file descriptor directly back into our memory buffer (`temp` struct) so we can verify the update.
* **`close()`**: Safely releases the kernel file resources and file descriptor once processing is complete.

## Executed Commands
* `gcc file_utility.c -o file_utility`: Compiled the C code into an executable.
* `./file_utility`: Executed the program to create, update, and read the employee records.
