# Learning C++ on Udemy

## Executing commands

```sh
# main.cpp
fswatch -o main.cpp | xargs -n1 -I{} sh -c 'clear && g++ -std=c++98 -o main.o main.cpp && ./main.o'

# any name
bash -c 'fswatch -o "$1" | xargs -n1 -I{} sh -c "clear && g++ -std=c++98 -o main.o \"$1\" && ./main.o"' _ binary-tree.cpp
```
