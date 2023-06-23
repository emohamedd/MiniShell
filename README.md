# Minishell

Welcome to Minishell, The Giga Project  developed as part of the 42 Network curriculum. Minishell is a simplified shell implementation, providing a command-line interface where users can interact with the operating system by executing various commands.

## Features

Minishell comes with the following features:

1. **Command Execution**: Users can execute a wide range of commands, including both built-in commands and external commands available in the system.
2. **Built-in Commands**: Minishell supports several built-in commands such as `cd`, `echo`, `pwd`, `export`, and `unset`, which provide additional functionality.
3. **Redirection and Pipes**: Minishell supports input/output redirection and pipes, allowing users to redirect command input and output streams, as well as chaining multiple commands together.
4. **Signal Handling**: Minishell handles various signals such as `Ctrl-C` and `Ctrl-\`, providing a graceful termination of running commands.
5. **Environment Variables**: Users can manage environment variables, set new variables, and modify existing ones using the built-in commands.
6. **Command History**: Minishell provides a command history feature, allowing users to navigate through previously executed commands using the arrow keys.

## Getting Started

To get started with Minishell, follow these steps:

1. Clone the Minishell repository from the official 42 Network GitHub repository:

   ```bash
   git clone https://github.com/emohamedd/MiniShell.git
    ```
    ```bash
    cd minishell
    ```
    ```bash
    make
    ```
    ```bash
    ./minishell
    ```
## Usage

Minishell provides a command-line interface where you can enter and execute commands. It supports various features and syntax that you can utilize:

**Executing Commands**: Simply enter a command and press Enter to execute it. For example:

    ```bash
   ls -l
    ```

**Built-in Commands**: Minishell supports several built-in commands. Here are a few examples:
    Changing the current working directory:
     ```bash
   cd /path/to/directory
    ```
     ```bash
   echo Hello, world!
    ```
     ```bash
   ls -l
    ```
**Redirection and Pipes**: Minishell allows you to redirect input/output and chain commands using pipes. Here are a few examples:
Redirecting output to a file:
    ```bash
    ls -l > output.txt
     ```
Piping the output of one command as input to another command:
     ```bash
   cat file.txt | grep "pattern"
     ```
**Signal Handling**: Minishell handles signals such as Ctrl-C and Ctrl-\ to terminate running commands or exit Minishell gracefully.

**Environment Variables**: You can manage environment variables using the built-in commands. For example:
    ```bash
    export MY_VAR=my_value
     ```
    ```bash
   export PATH=$PATH:/new/path
     ```
**Command History:** Minishell keeps track of command history, allowing you to navigate through previously executed commands using the arrow keys.
