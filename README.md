# 💻 Programming - CS Project

## ℹ️ About

This is a small project developed in the programming class, at the first cycle of my computer science bachelors course.

The project consists of a small program that initially asks for the defending and attacking player names, then the defender player place the boats and finally, the attacking player tries to sink every boat. The game has two rounds where the players switch positions.

Please note that the program itself is written in Portuguese.

## 🗃️ Installation

To install this project on your machine, clone the repository using HTTPS, SSH or GitHub CLI into a local directory or, alternatively, download the files directly.

## ⚙️ Automated Compilation and Execution (using Makefile)

- **Note:** Make sure to have both *C compiler* and *make* installed: `sudo apt install build-essential`.

After cloning the repository, access the folder named "**src**" (source code) and follow the instructions bellow:

| Compile | Compile and execute   | Execute                                                                                 |
|:-------:|:---------------------:|:---------------------------------------------------------------------------------------:|
| `make`  | `make execute`        | `make execute` (ignores the compilation process if the output file is already existing) |

## 🔧 Manual Compilation and Execution:

- **Note:** Make sure to have the *C compiler* installed: `sudo apt install build-essential`.

After cloning the repository, access the folder named "**src**" (source code) and follow the instructions bellow:

1. **Create the "*dist*" folder:** `mkdir -p ../dist` (`-p` is to ignore in case the directory already exists);
2. **Compiling:** `gcc -o ../dist/game.exe main.c`;
3. **Executing:** `../dist/game.exe`.

## 🧹 Clean output files from the compilation process (using Makefile)

Run `make clean` at the "**src**" (source code) folder to remove every output file. This command will remove every file whose extension is ".o" ".exe" or ".out" as well as the "*dist*" folder.
