
#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
namespace fs = filesystem;

// Splits a raw input line into tokens (command + arguments)
vector<string> parseInput(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// --- Built-in command implementations ---

void cmd_pwd() {
    cout << fs::current_path().string() << endl;
}

void cmd_cd(const vector<string>& args) {
    if (args.size() < 2) {
        cout << "cd: missing argument" << endl;
        return;
    }
    try {
        fs::current_path(args[1]); // throws if path is invalid
    } catch (const fs::filesystem_error& e) {
        cout << "cd: " << args[1] << ": No such directory" << endl;
    }
}

void cmd_mkdir(const vector<string>& args) {
    if (args.size() < 2) {
        cout << "mkdir: missing argument" << endl;
        return;
    }
    if (!fs::create_directory(args[1])) {
        cout << "mkdir: failed to create '" << args[1] << "'" << endl;
    }
}

void cmd_ls() {
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        cout << entry.path().filename().string() << "  ";
    }
    cout << endl;
}

void cmd_rm(const vector<string>& args) {
    if (args.size() < 2) {
        cout << "rm: missing argument" << endl;
        return;
    }
    try {
        if (!fs::remove(args[1])) {
            cout << "rm: '" << args[1] << "' not found" << endl;
        }
    } catch (const fs::filesystem_error& e) {
        cout << "rm: cannot remove '" << args[1] << "': " << e.what() << endl;
    }
}

// Executes any command that isn't a built-in, using fork + execvp
void executeExternal(const vector<string>& args) {
    pid_t pid = fork();

    if (pid < 0) {
        cout << "fork failed" << endl;
        return;
    }

    if (pid == 0) {
        // Child process: build argv array for execvp
        vector<char*> argv;
        for (const auto& arg : args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr); // execvp requires a null-terminated array

        execvp(argv[0], argv.data());

        // execvp only returns if it failed
        cout << args[0] << ": command not found" << endl;
        exit(1);
    } else {
        // Parent process: wait for child to finish
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    string line;

    while (true) {
        cout << fs::current_path().string() << " $ ";

        if (!getline(cin, line)) break; // handles Ctrl+D / EOF
        if (line.empty()) continue;

        vector<string> args = parseInput(line);
        const string& cmd = args[0];

        if (cmd == "exit") {
            break;
        } else if (cmd == "pwd") {
            cmd_pwd();
        } else if (cmd == "cd") {
            cmd_cd(args);
        } else if (cmd == "mkdir") {
            cmd_mkdir(args);
        } else if (cmd == "ls") {
            cmd_ls();
        } else if (cmd == "rm") {
            cmd_rm(args);
        } else {
            executeExternal(args);
        }
    }

    return 0;
}
