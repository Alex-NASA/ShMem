#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Define the size of the shared memory object
    const int SIZE = 4096;
    // Name of the shared memory object
    const char* name = "shared_memory_example";
    // Shared memory file descriptor
    int shm_fd;
    // Pointer to the shared memory object
    void* ptr;
    
    // Create the shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Configure the size of the shared memory object
    ftruncate(shm_fd, SIZE);

    // Memory map the shared memory object
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Write to the shared memory object
    sprintf(ptr, "Hello, Shared Memory!");

    // Read from the shared memory object
    printf("Shared Memory Content: %s\n", (char*)ptr);

    // Clean up
    if (shm_unlink(name) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
