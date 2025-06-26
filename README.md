Minishell (42 Project)

Minishell is a simplified Unix shell implemented in C as part of the 42 school curriculum. The goal of the project is to understand how a real shell works by rebuilding key components such as parsing, executing commands, managing environment variables, and handling signals.
Objectives

    Recreate a shell similar to Bash (without using system()).

    Parse and execute commands typed by the user.

    Handle redirections (<, >, >>) and pipes (|).

    Implement basic built-in commands:
    cd, echo, env, exit, export, pwd, unset.

    Manage environment variables and expansions ($VAR, $?).

    Properly handle quoting (' and ") and escapes.

    Manage signals like SIGINT (Ctrl+C) and SIGQUIT (Ctrl+).

What We Learned

    Lexing and parsing user input.

    Process creation (fork, execve, pipe, dup2).

    File descriptor management.

    Handling signals and terminal behavior.

    Implementing a basic shell from scratch using only allowed functions.
