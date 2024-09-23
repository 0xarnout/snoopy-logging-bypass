#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>

static int (*original_execve)(const char *, char *const [], char *const []);
static int (*original_execv)(const char*, char *const []);


void __attribute__((constructor)) find_original_symbols() {
    void *handle;
    handle = dlopen("libc.so.6", RTLD_NOW | RTLD_LOCAL);
    if (handle == NULL) {
        fprintf(stderr, "%s\n", dlerror());
        return;
    }
    original_execve = dlsym(handle, "execve");
    original_execv = dlsym(handle, "execv");
    if (original_execv == NULL || original_execv == NULL) {
        fprintf(stderr, "%s\n", dlerror());
    }
}

int execve(const char *pathname, char *const argv[], char *const envp[]) {
    return (*original_execve)(pathname, argv, envp);
}

int execv(const char* pathname, char *const argv[]) {
    return (*original_execv)(pathname, argv);
}
