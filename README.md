# Learning C++ on Udemy

## Executing commands

```sh
fswatch -o main.cpp | xargs -n1 -I{} sh -c 'clear && g++ -std=c++98 -o main.o main.cpp && ./main.o'
```
