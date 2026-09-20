# minish

A tiny Unix shell written in C, built from scratch for learning process creation, argument parsing, file descriptors, redirection, and program execution.

> **minish is a learning project, not a replacement for Bash, Zsh, or other full-featured shells.**

---

## Demo

![minish demo](assets/demo.gif)

---

## ✨ Features

Currently, minish supports:

* Running external commands
* Command-line arguments
* `fork()` for creating child processes
* `execvp()` for executing commands
* `waitpid()` for waiting for child processes
* Basic command parsing
* Interactive shell prompt
* Output redirection using `>`
* File creation and truncation using `open()`
* File descriptor duplication using `dup2()`

Example:

```text
minish $ ls -l
minish $ pwd
minish $ fastfetch
minish $ echo "hello world" > output.txt
```

Output redirection works by redirecting the child process's standard output to a file before executing the requested program.

---

## 🚧 Not Supported Yet

The initial versions intentionally keep things simple.

minish does **not** currently support:

* Pipes (`|`)
* Input redirection (`<`)
* Append redirection (`>>`)
* Background processes (`&`)
* Environment variable expansion
* Quoting and escaping
* Command history
* Tab completion
* Shell scripting
* Built-in commands such as `cd`

These may be explored in future versions.

## 🛠️ Building

Clone the repository:

```bash
git clone https://github.com/nilesh-padiyar/minish.git
cd minish
```

Compile with GCC/Clang and GNU Make:

```bash
make
```

Then run:

```bash
./minish
```

---

## 💻 Usage

Start minish:

```text
$ ./minish

minish $
```

Enter any command available on your system:

```text
minish $ ls
minish $ pwd
/home/user

minish $ fastfetch
```

### Output Redirection

minish supports basic output redirection using `>`:

```text
minish $ echo "hello world" > hello.txt
```

The command's standard output is redirected to `hello.txt` instead of the terminal.

For example:

```text
minish $ cat hello.txt
hello world
```

If the specified file does not exist, minish creates it. If it already exists, its contents are truncated before the command runs.

To exit, use:

```text
minish $ exit
```

## 🧠 Why I Built This

This project was created primarily to understand how a Unix shell works internally.

Instead of using a library or framework that abstracts away process management, minish works directly with POSIX system calls such as:

```text
fork()
execvp()
waitpid()
open()
dup2()
```

Building a shell was a practical way to learn how processes are created, how programs are executed, how file descriptors work, and how a shell can modify a child process's standard streams before execution.

---

## 📚 What I Learned

While building minish, I worked with:

* Process creation
* Process synchronization
* `fork()` / `exec()` workflow
* `argc` / `argv`
* Argument parsing
* POSIX system calls
* File descriptors
* Standard input/output file descriptors
* Output redirection
* `open()` and file access flags
* `dup2()` and file descriptor duplication
* Error handling in C
* Memory management
* GCC warning flags and strict compilation

---

The roadmap is intentionally open-ended. The goal is to use each feature as an opportunity to learn more about Unix and systems programming.

## 📌 Version

**v0.2.0** — Basic output redirection

minish v0.2.0 builds on the basic process execution model by adding output redirection:

> **Parse a command → create a child process → redirect its stdout → execute it → wait for it to finish.**

The goal remains the same: keep the implementation small while learning the underlying Unix mechanisms.

---

## 📄 License

This project is licensed under the MIT License. See [`LICENSE`](LICENSE) for details.

---

