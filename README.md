# simple_shell

A simple shell program that works in both interactive and non-interactive mode. Error handling is similar to `sh` (`/bin/sh`) command with the only difference that the program name is equivalent to `argv[0]` (`hsh`). 

## Requirements
Install cmake and Google Test
```bash
sudo apt-get install -y cmake libgtest-dev
```

## getting started
Run the following command to build and run `myshell` program
```bash
cmake --log-level=WARNING -B ./build . && make -s -C ./build
./build/myshell
```

## user stories
### interactive mode (version 0.0.0)
- Display a prompt `($)` and wait for the user to type a command. A command line always ends with a new line.
- The prompt is displayed again each time a command has to be executed.
- The command lines are simple, no semicolons. pipes, no redirections or any other advanced features.
- The command lines are made only of one word (no need to use `PATH`, implement built-ins, handle special characters, allow cursor movements or handle commands with arguments). No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- You have to handle the 'end-of-file' condition (`Ctrl+D`).

### interactive mode (version 0.1.0)
- Handle command line with arguments

### interactive mode (version 0.2.0)
- Handle the `PATH`.
- `fork` must not be called if the command doesn't exist.

### interactive mode (version 0.3.0)
- Implement the `exit` built-in, that exits the shell (Usage: `exit` and you do not have to handle any arguments to the built-in `exit`).

### interactive mode (version 0.4.0)
- Implement the `env` built-in, that prints the current environement

### interactive mode (version 0.1.1)
- Write your own `getline` function (`getline` is not allowed).
- Use a buffer to read many chars at once and call the least possible `read` system calls (You will need to use static variables).
- Cursor movement is not necessarily needed.

### interactive mode (version 0.2.1)
- Write your own `strtok` function (`strtok` is not allowed)

### interactive mode (version 0.4.1)
- Handle arguments for the built-in `exit` (Usage: `exit` `status`, wher `status` is an integer used to exit the shell)

### interactive mode (version 1.0.0)
- Implement the `setenv` and `unsetenv` built-in commands. `setenv` initializes a new environment variable, or modify an existing one and should print something on stderr on failure (Command syntax: `setenv VARIABLE VALUE`). `unsetenv` remove an environment variable and should print something on stderr on failure (Command syntax: `unsetenv VARIABLE`).
- Implement the built-in command `cd` (Command syntax: `cd DIRECTORY`). `cd` changes the current directory of the process. If no argument is given to `cd`, the command must be interpreted like `cd $HOME` and handle te command `cd -`. Remember to update the environment variable `PWD` when you change directory.
- Handle the commands separator `;`
- Handle the `&&` and `||` shell logical operators.
- Implement the `alias` built-in command (Usage: `alias [name[='value'] ...]`. `alias` prints a list of all aliases, one per line, in the form `name='value'`. `alias name [name2 ...]` prints the aliases `name`, `name2`, etc, 1 per line in the form `name='value'` and `alias name='value' [...]` defines an alias for each `name` whose `value` is given. If `name` is already an alias, replaces its value with `value`.
- Handle variables replacement
- Handle the `$?` variable
- Handle the `$$` variable
- Handle comments (`#`)

### noninteractive (version 1.0.0)
- Your shell can take a file as a command line argument (Usage: `simple_shell [filename]`)
- The file contains all the commands that your shell should run before exiting
- The file should contain one command per line
- In this mode the shell should not print a prompt and should not read from `stdin`
