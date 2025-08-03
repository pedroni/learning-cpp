# Learning C++ on Udemy

The goal in learn C++ is to eventually be good enough at C++ so that I can work on the Forsaken World codebase while understand what I'm doing. The `C++98` standard is being used here because I want to learn on the constraints of an older environment.

## Using AI to learn

There's a `CLAUDE.md` file, though this file is often used to code with Claude Code, it's here as a base prompt to copy paste on an AI chat and not to vibe-code.

## Executing commands

### Compiling and run once

> Note the `g++-15` this is to use the homebrew g++ version. Using the clang from Apple doesn't work well with `-std=c++98`. One simple trick to check if its working is doing `std::to_string(5)` in a file to see if it fails. `std::to_string` was not available back then.

```sh
g++-15 -std=c++98 -o main.o main.cpp && ./main.o
```

### Compiling and run on every edit

```sh
# any name
bash -c 'fswatch -o "$1" | xargs -n1 -I{} sh -c "clear && g++-15 -std=c++98 -o main.o \"$1\" && ./main.o"' _ binary-tree.cpp
```
