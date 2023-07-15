#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#define PAUSE_BEFORE    1
#define PAYLOAD         "\x90\x90\xc3"

int main(int argc, char** argv) {
    unsigned char shc[] = PAYLOAD;
    size_t sz = sizeof(shc);
    void *alloc;

    printf("[*] Allocating memory region ...\n");
    alloc = mmap(NULL, sz, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (alloc == MAP_FAILED) {
        printf("[-] Failed to allocate memory! (%lx)\n", errno);
        return 1;
    }
    printf("[+] Allocated RWX of size %lx bytes @ %p ... \n", sz, alloc);

    printf("[*] Copying shellcode to memory region ...\n");
    memcpy(alloc, shc, sz - 1);
    printf("[+] Copied shellcode!\n");

#if PAUSE_BEFORE
    printf("[!] Press <ENTER> to launch shellcode!\n");
    getchar();
#endif

    printf("[*] Launching shellcode ... \n");
    ((void (*)()) alloc)();

    printf("[+] All done, exiting ... \n");
    return 0;
}
