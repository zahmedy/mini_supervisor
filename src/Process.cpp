#include "../include/mini_supervisor/Process.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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

int start(std::string cmd)
{
    std::stringstream ss(cmd);
    std::string arg;
    std::vector<std::string> args;
    while (ss >> arg)
    {
        args.push_back(arg);
    }
    if (args.empty())
        return -1;

    // convert to C style args
    std::vector<char *> argv;
    for (auto &s : args)
    {
        argv.push_back(const_cast<char *>(s.c_str()));
    }
    // add null pointer at the end
    argv.push_back(nullptr);

    pid_t pid = fork();

    if (pid < 0)
    {
        return -1;
    }
    else if (pid == 0)
    {
        // Child process: Replace address space with target binary
        execvp(argv[0], argv.data());

        // if execvp return an error has occured
        _exit(127);
    }
    else
    {
        // Parent process: Wait for child
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}