
# Go Fish Card Game

## Overview

This project is a implementation of the classic card game "Go Fish," developed in C. The game is designed for one human player and one computer player. It utilizes basic UNIX software development tools, including `gcc`, `gdb`, and `make`.

## Features

- Text-based interface mimicking the gameplay of Go Fish.
- Randomized shuffling of a standard 52-card deck using the `rand()` function.
- Error handling for invalid player inputs.
- Ability to play multiple rounds until the player chooses to quit.

## Game Rules

1. Each player starts with seven cards.
2. Players take turns asking each other for cards of a specific rank.
3. If the opponent has the requested cards, they must hand them over; otherwise, the player must "go fish" and draw from the pool.
4. A player who collects all four cards of a rank forms a "book."
5. The game continues until one player collects seven books.

## Requirements

- C compiler (e.g., `gcc`)
- Make utility

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/gofish.git
   cd gofish
   ```

2. **Build the Project**:
   To compile the project, run:
   ```bash
   make
   ```

3. **Run the Game**:
   Start the game by executing:
   ```bash
   ./gofish
   ```

4. **Clean Up**:
   To remove object files and the executable, use:
   ```bash
   make clean
   ```

5. **Debug Mode**:
   To build the project with debugging symbols, run:
   ```bash
   make debug
   ```

## Structure

The project consists of multiple C source files and corresponding header files organized as follows:

```
gofish/
├── src/
│   ├── card.c
│   ├── player.c
│   ├── deck.c
│   ├── game.c
│   └── main.c
├── include/
│   ├── card.h
│   ├── player.h
│   ├── deck.h
│   └── game.h
├── Makefile
└── partner.txt
```


## License

This project is for educational purposes and is not licensed for commercial use.

## Acknowledgments

Special thanks to the course instructor, Prof. David Irwin of ECE 322 at UMass Amherst, for providing the project guidelines and template files.
