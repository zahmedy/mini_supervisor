#include "../include/mini_supervisor/Process.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fcntl.h>
#include <sys/wait.h>

Process::Process(std::string procName, std::string procCommand, int restartLimit)
    : name_(procName), command_(procCommand), limit_(restartLimit) {}

Process::~Process() {}

std::string Process::get_name() const
{
    return name_;
}

std::string Process::get_command() const
{
    return command_;
}

int Process::get_limit() const
{
    return limit_;
}

int Process::get_pid() const
{
    return pid_;
}

//
// Start begins
//
int Process::start()
{
    std::stringstream ss(command_);
    std::string arg;
    std::vector<std::string> args;
    while (ss >> arg)
    {
        args.push_back(arg);
    }

    // convert to C style args for execvp
    std::vector<char *> argv;
    for (auto &s : args)
    {
        argv.push_back(const_cast<char *>(s.c_str()));
    }
    // add null pointer at the end
    argv.push_back(nullptr);

    int pipefd[2];
    if (pipe(pipefd) != 0)
    {
        return -1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return -1;
    }
    else if (pid == 0)
    {
        close(pipefd[0]);
        // Close write fd 1 if execution start
        // instead of waiting for exevp to finish
        fcntl(pipefd[1], F_SETFD, FD_CLOEXEC);
        // Child process: Replace address space with target binary
        execvp(argv[0], argv.data());

        write(pipefd[1], "f", 1);
        close(pipefd[1]);
        // if execvp return an error has occured
        _exit(127);
    }
    else
    {
        // parent
        pid_ = pid;
        char buf;
        close(pipefd[1]);
        int rv = read(pipefd[0], &buf, 1);
        if (rv == 1)
        {
            return -1;
        }
        close(pipefd[0]);
        return Process::wait();
    }
}
//
// Start ends
//

int Process::wait()
{
    int status;
    pid_t result = waitpid(pid_, &status, 0);
    std::cout << status << "\n.";
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}