
//Core functionality:
//1. Open a .txt file and show contents page by page
//2. Cursor support:
    //a. allow cursor movements
    //b. allow edits (add/delete) at given cursor location
//3. Save the current .txt
//4. Exit from editor

//1. To open a .txt, and show contents, etc.
//  a. seems best way out is mmap, as then we can code against a buffer which abstracts away the file
//  b. yet to figure out how to tell OS to "save" to disk? Does it save at its own discretion as
//      I modify the buffer?

#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <filesystem>

int main(int argc, char** argv) {
    assert(argc == 2 && argv);

    std::filesystem::path file_path{argv[1]};
    auto abs_file_path = std::filesystem::absolute(file_path);

    //open the file and map its descriptor to buffer
    if(FILE* file = std::fopen(abs_file_path.c_str(), "r+")) {
        int file_desc = fileno(file);

        // Seek to the end of the file
        if (fseek(file, 0, SEEK_END) != 0) {
            perror("Failed to seek to the end of the file");
            fclose(file);
            return 1;
        }

        // Get the current file position, which is the file size
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        char* file_buf = (char*)mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_desc, 0);
        for(int i = 0; i < file_size; ++i) {
            std::cout<<file_buf[i];
        }
    }
}