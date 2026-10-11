
# Mini Linux Shell in C++

A lightweight command-line shell implemented in C++ that replicates basic Linux terminal functionality. The project supports built-in commands for file and directory management and executes external programs using Linux system calls such as `fork()`, `execvp()`, and `waitpid()`.

It demonstrates core operating system concepts, including process creation, program execution, process synchronization, command parsing, and filesystem operations.

## Features

- **Built-in commands:** Supports `cd`, `pwd`, `mkdir`, `ls`, `rm`, and `exit`.
- **External command execution:** Runs external programs using `fork()` and `execvp()`.
- **Process management:** Uses `waitpid()` to wait for child processes to complete.
- **Filesystem operations:** Uses the C++17 filesystem library for directory navigation and file management.
- **Interactive terminal:** Displays the current working directory as the shell prompt.
- **Input handling:** Reads commands interactively and handles end-of-file input, such as Ctrl+D on Linux.

## Technologies Used

- C++
- Linux / POSIX system calls
- C++17 Standard Library
- Filesystem library
- Process management

## Supported Commands

| Command | Description | Example |
|---|---|---|
| `pwd` | Displays the current working directory | `pwd` |
| `cd` | Changes the current working directory | `cd Documents` |
| `mkdir` | Creates a new directory | `mkdir projects` |
| `ls` | Lists entries in the current directory | `ls` |
| `rm` | Removes a file or an empty directory | `rm notes.txt` |
| `exit` | Terminates the shell | `exit` |
| External commands | Executes available programs | `date`, `whoami`, `cat notes.txt` |

**Note:** The current implementation supports basic space-separated arguments. It does not yet support shell features such as pipes, input/output redirection, quoted arguments, wildcard expansion, or background execution.

## Project Structure

```text
Mini-Linux-Shell/
├── main.cpp
└── README.md
```

- `main.cpp` — Contains the shell implementation, built-in commands, input parsing, and external process execution.
- `README.md` — Project documentation.

## Prerequisites

- A Linux operating system or compatible POSIX environment.
- A C++ compiler with C++17 support, such as GCC.
- Basic knowledge of terminal commands and C++ programming.

## Installation and Execution

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/mini-linux-shell.git
cd mini-linux-shell
```

Replace the repository URL with your actual GitHub repository URL.

### 2. Compile the Program

```bash
g++ -std=c++17 main.cpp -o minishell
```

### 3. Run the Shell

```bash
./minishell
```

The shell displays the current working directory followed by a `$` prompt.

### 4. Try the Commands

```bash
pwd
mkdir test_folder
cd test_folder
pwd
ls
cd ..
rm test_folder
date
whoami
exit
```

These commands demonstrate directory navigation, directory creation and removal, working-directory inspection, and external program execution.

**Caution:** The `rm` command can permanently delete files or empty directories. Test the shell in a dedicated directory when experimenting.

## How It Works

### 1. Command Input and Parsing

The shell reads user input using `getline()` and splits the input into tokens using `stringstream`. The first token is treated as the command, while the remaining tokens are treated as arguments.

### 2. Built-in Command Execution

The shell checks whether the command matches a supported built-in command. If it does, the corresponding C++ function executes it.

- `pwd` uses `filesystem::current_path()` to display the current directory.
- `cd` changes the working directory.
- `mkdir` creates a directory.
- `ls` iterates over directory entries.
- `rm` removes a file or empty directory.
- `exit` terminates the shell loop.

Built-in commands execute within the shell process. This is especially important for `cd`, because changing the working directory of a child process would not change the shell's own directory.

### 3. Process Creation Using `fork()`

For commands that are not built-ins, the shell calls `fork()` to create a child process.

- The parent process remains responsible for the shell.
- The child process prepares the command and its arguments for execution.

### 4. Program Execution Using `execvp()`

The child process calls `execvp()` to replace its process image with the requested external program. The function searches for the executable using the `PATH` environment variable when the command does not specify a path.

If execution fails, the program displays an error message.

### 5. Process Synchronization Using `waitpid()`

The parent process calls `waitpid()` to wait for the child process to finish before displaying the next prompt. This provides sequential execution of external commands.

## Operating System Concepts Demonstrated

| Concept | Implementation |
|---|---|
| Command interpretation | Tokenization and command dispatch |
| Process creation | `fork()` |
| Program execution | `execvp()` |
| Process synchronization | `waitpid()` |
| Filesystem management | C++17 `std::filesystem` |
| Working directory management | `current_path()` |
| Parent-child process relationship | Parent waits for child completion |
| Environment-based executable lookup | `PATH` through `execvp()` |

## Limitations

- Supports only simple, whitespace-separated command parsing.
- Does not implement pipes, redirection, command chaining, or background jobs.
- Does not support quoted strings containing spaces.
- The `ls` command lists only the current directory and does not accept a path argument.
- The `rm` command removes a single file or empty directory; recursive deletion is not implemented.
- Error handling and exit-status reporting can be improved.
- It relies on POSIX process APIs and is intended for Linux or a compatible environment.

## Future Improvements

- Add support for quoted arguments and more robust command parsing.
- Implement input/output redirection and pipes.
- Support background processes using `&`.
- Add command history and arrow-key navigation.
- Implement commands such as `clear`, `help`, and `echo`.
- Improve error handling and display meaningful system error messages.
- Support environment-variable expansion and command chaining.
- Add automated tests for built-in commands and process execution.

## Learning Outcomes

Through this project, I explored:

- How command-line shells interpret and execute user input.
- How operating systems create processes and execute programs.
- The difference between built-in commands and external programs.
- How parent and child processes interact.
- How filesystem operations can be implemented using modern C++.
- How Linux system calls support basic shell functionality.

## Conclusion

The Mini Linux Shell in C++ project demonstrates the fundamental working principles of a command-line shell. By implementing built-in filesystem commands and external program execution through `fork()`, `execvp()`, and `waitpid()`, it provides practical experience with C++ programming and operating system concepts.

The project serves as a foundation for developing a more advanced shell with features such as pipes, redirection, command history, and background process management.

## License

Choose a license before publishing the project publicly. The MIT License is one option for an open-source project.
