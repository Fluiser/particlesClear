# particlesClear
For clean deleted particles from disk.</br>
If you bad dude and need to clean the disk, then this 'utility' can help you.</br>
> **Please, don't use this code on SSD if you don't understand what it doing.</br>
This can shorten its lifespan.**</br>

Compilation: `g++ main.cpp -o main -std=c++17`</br>
> Flags:</br>

  `--threads \<number\>` - Set threads count for trashing your disk.</br>
  `--path \<directory\>` - Set directory for temp files.</br>
  `--chunk <count mb>` - Set chunk size for filling.</br>

> Example:</br>
  `g++ main.cpp -o main -std=c++17 &&`</br>`./main --threads 4 --path D:/trashFile --chunk 8`
