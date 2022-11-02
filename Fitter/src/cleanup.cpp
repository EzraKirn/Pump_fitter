#include <iostream>
#include <fstream>
#include <vector>

void cleanup(){
    std::vector<std::string> file_names;
    std::fstream file("file_names.txt");
    while(!file.eof()){
        std::string tmp;
        std::getline(file,tmp);
        file_names.push_back(tmp);
    }
    file.close();
    std::remove("file_names.txt");

    for(std::string c:file_names){
        std::remove(c.c_str());
    }
}