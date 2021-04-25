# Grandma's password generator

The program generates the most optimal password consisting of 4 english words taken from a dictionary -  a list of words in a file.

## How to build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run

```bash
cd bin 
```

There is two ways to run the program:

1. 
   
   ```bash
   ./grandmas_password_generator
   ```

This way uses a dictionary provided by the wordlist/words package.

https://en.wikipedia.org/wiki/Words_(Unix)

**BUT** There is no guarantee that it always works because location of the file depends on Linux distribution. This program was tested on *Manjaro*.

2. 
   
   ```bash
   ./grandmas_password_generator path/to/words/file
   ```

Your custom dictionary must contain one word per line. The folder 'examples' contains example dictionaries. 

File *words_alpha.txt* was taken [this repository](https://github.com/dwyl/english-words) (maybe i should include this like a submodule but i decided to take the easy way :) )
