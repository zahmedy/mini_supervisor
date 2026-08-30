#include <unistd.h>
#include <iostream>

int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        std::cout << "Fork failed \n";
        return -1;
    }
    else if (pid == 0)
    {
        pid_t child_pid = getpid();
        std::cout << "New fork with pid id: " << child_pid << "\n";
        std::cout << "Ran sleep: " << "\n";
        execlp("sleep", "sleep", "20", (char *)nullptr);
    }
    else
    {
        std::cout << "I forked myself and ran sleep with my child, peace out!\n";
    }

    return 0;
}