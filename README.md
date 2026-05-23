<div align="center">

```
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
```

**A minimal Unix shell built in C — 42 School Common Core**

[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Standard](https://img.shields.io/badge/Standard-C99-blue?style=flat-square)](https://en.wikipedia.org/wiki/C99)
[![School](https://img.shields.io/badge/School-42-black?style=flat-square)](https://www.42.fr/)

</div>

---

## Documentation

> Full study guide, module breakdowns, flow diagrams and theoretical notes are available on Notion:

<div align="center">

### **[Minishell — Full Documentation on Notion](https://www.notion.so/Minishell-22a6a32e0f348085ab83f76308f83a4d)**

*Covers: Lexer · Expander · Parser · Executor · Built-ins · Signals · Here-doc*

</div>

---

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Built-in Commands](#built-in-commands)
- [Execution Pipeline](#execution-pipeline)
- [Testing](#testing)
- [Authors](#authors)

---

## About the Project

**Minishell** is a simplified Unix shell implemented in C as part of the 42 School Common Core curriculum. The goal is to deeply understand how a real shell works internally — from reading user input all the way to executing processes, managing pipes, handling signals, and expanding variables.

The shell replicates the core behavior of **Bash**, including:

- Interactive prompt with command history
- Lexical analysis and tokenization
- Variable and `$?` expansion
- Pipeline execution with inter-process communication
- I/O redirections and here-documents
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- A complete set of built-in commands

---

## Features

| Feature | Description |
|---------|-------------|
| **Interactive prompt** | Built with `readline` — supports command history (up/down arrows) |
| **Lexer / Tokenizer** | Splits input into typed tokens, respects single and double quotes |
| **Variable expansion** | Expands `$VAR` and `$?`; single quotes prevent all expansion |
| **Word splitting** | Post-expansion splitting on IFS for unquoted tokens |
| **Pipelines** | Unlimited `cmd1 \| cmd2 \| cmd3 \| ...` chaining |
| **Redirections** | `<` `>` `>>` `<<` (here-doc) fully supported |
| **Built-in commands** | `echo` `cd` `pwd` `export` `unset` `env` `exit` |
| **Signal handling** | `SIGINT` (Ctrl+C) resets the prompt; `SIGQUIT` (Ctrl+\\) is ignored |
| **Quote handling** | Single quotes: fully literal. Double quotes: allow `$` expansion |
| **Here-doc** | `<<` reads stdin lines until delimiter; subprocess-based for signal safety |

---

## Architecture

The shell processes each command line through a **sequential pipeline of four stages**:

```
Input (readline)
      │
      ▼
  ┌───────┐      Splits text into a linked list of typed tokens
  │ LEXER │      Handles quotes, operators (| < > << >>), words
  └───┬───┘
      │ t_lexer list
      ▼
  ┌──────────┐   Expands $VAR, $? — applies word splitting
  │ EXPANDER │   Enforces quoting rules (single vs double quotes)
  └────┬─────┘
       │ t_lexer list (expanded)
       ▼
  ┌────────┐     Groups tokens into commands (t_parcer nodes)
  │ PARSER │     Opens file descriptors for redirections
  └────┬───┘     Launches here-doc subprocesses
       │ t_parcer list
       ▼
  ┌──────────┐   fork() + execve() per command
  │ EXECUTOR │   Connects commands via pipes with dup2()
  └──────────┘   Waits for children — updates $?
```

### Core Data Structures

```c
t_lexer   — doubly linked list node; one token (word, operator, pipe...)
t_parcer  — one complete command: argv[], infile fd, outfile fd, builtin name
t_shell   — global shell state: environment copy, last_status ($?)
t_mini    — container for a full pipeline: t_lexer*, t_parcer*, num_cmd
```

---

## Project Structure

```
Minishell/
└── minishell/
    ├── Makefile
    ├── include/
    │   └── minishell.h          ← All structs, enums, and prototypes
    └── src/
        ├── main.c               ← Entry point
        ├── prompt/              ← Main loop, readline, environment copy
        │   ├── prompt.c
        │   ├── aux_prompt.c
        │   ├── prompt_create.c
        │   └── utils_prompt.c
        ├── lexer/               ← Tokenizer (lexical analysis)
        │   ├── lexer.c
        │   ├── check_operators.c
        │   ├── aux_handler.c
        │   ├── check_handles.c
        │   └── lexer_quotes.c
        ├── expander/            ← Variable expansion + word splitting
        │   ├── expander.c
        │   ├── expander_check.c
        │   ├── expander_write.c
        │   ├── expander_vars.c
        │   ├── expander_tokens.c
        │   ├── expander_status.c
        │   ├── expander_utils.c
        │   └── expander_split/
        ├── parcer/              ← Parser: tokens -> command structures
        │   ├── parcer.c
        │   ├── parcer_aux.c
        │   ├── check_parcer_handle.c
        │   └── check_redirection.c
        ├── execute/             ← Executor: fork, execve, pipes
        │   ├── execute.c
        │   ├── execute_child.c
        │   ├── execute_aux.c
        │   ├── proccess_execve.c
        │   └── procces_execve_aux.c
        ├── built-ins/           ← Internal commands
        │   ├── built-ins.c
        │   ├── ft_echo.c
        │   ├── ft_env.c
        │   ├── ft_exit.c
        │   ├── ft_export.c
        │   ├── ft_pwd.c
        │   ├── ft_unset.c
        │   ├── aux_export.c
        │   └── ft_cd/
        ├── here_doc/            ← Here-document (<<) implementation
        │   ├── heredoc.c
        │   └── heredoc_aux.c
        ├── signals/             ← Signal handlers (SIGINT, SIGQUIT)
        │   └── signals.c
        └── utils/               ← Memory management, debug prints
            ├── ft_free.c
            └── prints.c
```

---

## Getting Started

### Prerequisites

- GCC or Clang
- GNU Make
- `readline` library

```bash
# Debian/Ubuntu
sudo apt-get install libreadline-dev

# macOS (Homebrew)
brew install readline
```

### Build

```bash
git clone https://github.com/alejagom-gafreire/Minishell.git
cd Minishell/minishell
make
```

### Run

```bash
./minishell
```

### Makefile Targets

| Target | Description |
|--------|-------------|
| `make` / `make all` | Compile the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Full recompile (`fclean` + `all`) |

---

## Built-in Commands

These commands are implemented **inside the shell** (no `fork` + `execve`):

| Command | Usage | Description |
|---------|-------|-------------|
| `echo` | `echo [-n] [args...]` | Print arguments. `-n` suppresses the trailing newline. Valid flags: `-n`, `-nn`, `-nnn`, `-n -n` |
| `cd` | `cd [path]` | Change directory. No args goes to `$HOME`; `-` goes to `$OLDPWD`. Updates `PWD` and `OLDPWD` |
| `pwd` | `pwd` | Print the current working directory |
| `export` | `export [NAME=value...]` | Set or update environment variables. No args prints the sorted env |
| `unset` | `unset [NAME...]` | Remove environment variables |
| `env` | `env` | Print all environment variables |
| `exit` | `exit [n]` | Exit the shell with optional exit code |

---

## Execution Pipeline

### Single Command
```bash
$ echo "Hello, World!"
Hello, World!
```

### Pipeline
```bash
$ ls -la | grep ".c" | wc -l
```
Each command runs in its own child process, connected by pipes.

### Redirections
```bash
$ cat < input.txt          # stdin from file
$ echo "hi" > output.txt   # stdout to file (truncate)
$ echo "hi" >> output.txt  # stdout to file (append)
$ cat << EOF               # here-doc: read until EOF delimiter
> line 1
> line 2
> EOF
```

### Variable Expansion
```bash
$ echo $USER               # expands to current user
$ echo "$HOME/projects"    # expands inside double quotes
$ echo '$PATH'             # literal — single quotes block expansion
$ echo $?                  # last command exit code
```

### Signal Behavior

| Signal | Key | In prompt | In child process |
|--------|-----|-----------|-----------------|
| `SIGINT` | `Ctrl+C` | Clears line, shows new prompt | Terminates the child (exit 130) |
| `SIGQUIT` | `Ctrl+\` | Ignored | Default behavior |
| `EOF` | `Ctrl+D` | Exits the shell cleanly | — |

---

## Testing

### Memory Leak Detection (Valgrind)

```bash
valgrind --leak-check=full          \
         --show-leak-kinds=all      \
         --track-origins=yes        \
         --track-fds=yes            \
         --trace-children=yes       \
         --verbose                  \
         --log-file=valgrind_log.txt \
         --suppressions=bash.supp   \
         ./minishell
```

> `--trace-children=yes` is essential to catch leaks inside forked child processes.  
> `--suppressions=bash.supp` filters out readline's known internal false positives.

### Quick Checks

```bash
# Pipeline
echo "foo bar baz" | grep bar | wc -w

# Redirections
cat < /etc/hostname > /tmp/test_out.txt
cat /tmp/test_out.txt

# Variable expansion
export MY_VAR="hello world"
echo "$MY_VAR"
echo '$MY_VAR'     # should print literal $MY_VAR

# Exit code
ls /nonexistent
echo $?            # should print 2

# Here-doc
cat << STOP
line one
line two
STOP
```

---

## Authors

<div align="center">

| <img src="https://github.com/alejogogi.png" width="90" style="border-radius:50%;"> | <img src="https://github.com/ByteGab.png" width="90" style="border-radius:50%;"> |
|:---:|:---:|
| **alejago** | **gafreire** |
| <a href="https://www.linkedin.com/in/alejandro-gomez-giron-5b840219b/"><img src="https://img.shields.io/badge/-LinkedIn-0A66C2?style=flat-square&logo=linkedin&logoColor=white" height="22"></a> <a href="https://github.com/alejogogi"><img src="https://img.shields.io/badge/-GitHub-24292F?style=flat-square&logo=github&logoColor=white" height="22"></a> <a href="https://profile.intra.42.fr/users/alejagom"><img src="https://img.shields.io/badge/-42-000000?style=flat-square&logo=42&logoColor=white" height="22"></a> | <a href="https://es.linkedin.com/in/gabrielfreiresimon"><img src="https://img.shields.io/badge/-LinkedIn-0A66C2?style=flat-square&logo=linkedin&logoColor=white" height="22"></a> <a href="https://github.com/ByteGab"><img src="https://img.shields.io/badge/-GitHub-24292F?style=flat-square&logo=github&logoColor=white" height="22"></a> <a href="https://profile.intra.42.fr/users/gafreire"><img src="https://img.shields.io/badge/-42-000000?style=flat-square&logo=42&logoColor=white" height="22"></a> |

*42 School — Common Core Project*

</div>

---

## Resources

- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [Writing a Shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Minishell — Medium Article](https://medium.com/@jamalaitchdid1/minishell-27cb18619782)
- [Minishell Function Documentation — HackMD](https://hackmd.io/@laian/B1A0_LSPn)
- [A Guide to Parsing: Algorithms and Terminology](https://tomassetti.me/guide-parsing-algorithms-terminology/)
- [Linux man-pages](https://man7.org/linux/man-pages/)

---

<div align="center">
<sub>Built with ☕ and a lot of <code>fork()</code> calls at 42 School</sub>
</div>
