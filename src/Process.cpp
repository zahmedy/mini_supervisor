#include "../include/mini_supervisor/Process.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fcntl.h>
#include <sys/wait.h>
#include <cerrno>

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
        return 0;
    }
}
//
// Start ends
//

//
// Wait begins
//
int Process::wait()
{
    int status;
    constexpr int WAIT_ERROR = -100;

    pid_t result = waitpid(pid_, &status, 0);

    // if the parent got signaled, restart waitpid to conintue waiting for child
    if (result == -1 && errno == EINTR)
    {
        while (result == -1 && errno == EINTR)
        {
            result = waitpid(pid_, &status, 0);
        }
    }

    if (result < 0)
        return WAIT_ERROR;

    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }

    if (WIFSIGNALED(status))
    {
        return -WTERMSIG(status);
    }

    return -1;
}
//
// Wait ends
//

//
// RUn begins
//
int Process::run()
{
    int stat = Process::start();
    if (stat < 0)
    {
        // if the command itself failed to start, just return
        std::cout << "Unrunable command, exiting..." << "\n";
        return stat;
    }
    int waited = Process::wait();
    int restartCount_ = 0;
    while (restartCount_ < limit_)
    {
        // -100 is madeup error to indiacte waitpid failed
        if (waited == -100)
        {
            std::cout << "Waitpid failed, exiting..." << "\n";
            break;
        }
        else if (waited < 0)
        {
            std::cout << "Process got signal: restarting..";
            restartCount_ += 1;
            stat = Process::start();
            if (stat < 0)
            {
                return stat;
            }
            waited = Process::wait();
        }
        else
        {
            break;
        }
    }
    return waited;
}