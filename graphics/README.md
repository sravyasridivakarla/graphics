# Instructions for compiling on mac command line:

install homebrew if you do not already have it:
```sh
$/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" 
```
install freeglut:
```sh
$ brew install freeglut
```
compile:
```sh
$ g++ HelloGraphics.cpp -lglut -framework OpenGL
```
execute:
```sh
$ ./a.out
```
