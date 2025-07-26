# Learning C++ on Udemy

## Executing commands

```sh
fswatch -o main.cpp | xargs -n1 -I{} sh -c 'clear && g++ -std=c++11 -o main.o main.cpp && ./main.o'
```
