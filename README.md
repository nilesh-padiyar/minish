# minish

A tiny Unix shell written in C, built from scratch for learning process creation, argument parsing, and program execution.

> **minish is a learning project, not a replacement for Bash, Zsh, or other full-featured shells.**

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

Example:

```text
minish >>> ls -l
minish >>> pwd
minish >>> fastfetch
minish >>> htop
```

---

## 🚧 Not Supported Yet

The first version intentionally keeps things simple.

minish does **not** currently support:

* Pipes (`|`)
* Input/output redirection (`>`, `<`, `>>`)
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

minish >>>
```

Enter any command available on your system:

```text
minish >>> ls
minish >>> pwd
/home/user

minish >>> fastfetch
```

To exit, use:

```text
minish >>> exit
```

## 🧠 Why I Built This

This project was created primarily to understand how a Unix shell works internally.

Instead of using a library or framework that abstracts away process management, minish works directly with POSIX system calls such as:

```text
fork()
execvp()
waitpid()
```

Building a shell was a practical way to learn how processes are created, how programs are executed, and how a parent process interacts with its children.

---

## 📚 What I Learned

While building minish, I worked with:

* Process creation
* Process synchronization
* `fork()` / `exec()` workflow
* `argc` / `argv`
* Dynamic argument parsing
* POSIX system calls
* File descriptors
* Error handling in C
* Memory management
* GCC warning flags and strict compilation

---

## 🗺️ Roadmap

Possible future features:

* [ ] Built-in commands
* [ ] Pipes
* [ ] Input/output redirection
* [ ] Background processes
* [ ] Environment variables
* [ ] Quoting and escaping
* [ ] Command history
* [ ] Tab completion
* [ ] Signal handling
* [ ] Better parser

The roadmap is intentionally open-ended. The goal is to use each feature as an opportunity to learn more about Unix and systems programming.

## 📌 Version

**v0.1.0** — Basic command execution

minish v0.1.0 focuses on one thing:

> **Type a command → create a process → execute it → wait for it to finish.**

Nothing fancy. Just the fundamentals.

---

## 📄 License

This project is licensed under the MIT License. See [`LICENSE`](LICENSE) for details.

---
