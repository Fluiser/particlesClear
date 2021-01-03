#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <atomic>
#include <thread>
#include <vector>
#include <stdio.h>

char* null;
long long chunk;

long long toNumber(const char* str)
{
    size_t num = 0;
    try {
        std::stringstream stream(str);
        stream >> num;
    } catch(std::exception err) {
        std::cout << err.what() << "\n";
        num = 0;
    }
    return num;
}

void trashFile(std::string path)
{
    std::fstream file(path, std::fstream::in | std::fstream::out | std::fstream::app | std::fstream::binary);
    if(file.is_open()) {
        while(true)
        {
            try {
                file.write(null, 1024);
            } catch (std::exception& err) {
                file.close();
            	std::cout << err.what() << "\n";
            	std::remove(path.c_str());
            	break; 
            }
        }
    } else {
        std::cout << "Can't open file [" << path << "\n";
    }
}

int main(int argc, char** argv)
{
    long threadSize = 0;
    std::string path = "";
    std::vector<std::thread> threads;

    for(size_t i = 0; i < argc; ++i)
    {
        std::string str(argv[i]);
        if(i+1 < argc) {
            if (str == "--threads") threadSize = toNumber(argv[i + 1]);
            if (str == "--path") path = argv[i + 1];
            if (str == "--chunk") chunk = toNumber(argv[i + 1]);
        }
    }

    if(threadSize <= 0) threadSize = 1;
    if(!path.size() || path == ".") path = "temp";
    if(chunk <= 0) chunk = 1048576; // 1mb
    else chunk = chunk*1024*1024;

    std::cout << "threads: " << threadSize << "\npath: " << path << "\nchunk: " << (chunk/1024/1024) << "mb\n";

    null = (char*)malloc(chunk);
    if(null == nullptr) {
    	std::cout << "Can't allocate memory\n";
    	return 1;
    }

    for(size_t i = 0; i < threadSize; ++i)
    {
        threads.push_back(std::thread(trashFile, path + std::to_string(i)));
    }

waiter:
    if(threads.size()) {
        auto &thread = threads.back();
        thread.join();
        threads.pop_back();
        goto waiter;
    }
    free(null);
    std::cout << "END\n";
    return 0;
}
