# Learning C++

The goal in learn C++ is to eventually be good enough at C++ so that I can work on the Forsaken World codebase while understand what I'm doing. The `C++98` standard is being used here because I want to learn on the constraints of an older environment.

## Using AI to learn

There's a `CLAUDE.md` and it's here as a base prompt to copy paste on an AI chat so that it can act as a professor and answer questions relating to C++. It's not here to vibe-code, using Claude Code.

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

## Whiteboard

Some solutions were first discovered using a "whiteboard" approach. When seeing a `.cpp` file you might encounted a `.pdf` file that contains the whiteboard final file for that specific problem.

For the Whiteboard I'm using an iPad Air (4th generation) with a "WB" Pencil, and the Notes+ app.

## Resources

These are links that helped me learn and understand DSA and C++.

- [C++ Data Structures & Algorithms + LEETCODE Exercises](https://www.udemy.com/course/data-structures-algorithms-cpp), Scott Barret
- [Binary Tree Algorithms for Technical Interviews](https://www.youtube.com/watch?v=fAAZixBzIAI), freeCodeCamp.org, Alvin Zablan
