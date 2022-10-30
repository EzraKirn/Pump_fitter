#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <vector>
#include <thread>
#include "src\UI.cpp"

#define GRAVITY 9.81
#define WATER_DENSITY 998

std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

void generate_dataset(){
    std::fstream file;
    file.open("file_names.txt");
    std::vector<std::string> names;
    std::vector< std::vector<float> > coef;    

    for (std::string line;std::getline(file,line);)
    {
        names.push_back(line);
    }

    file.close();

    for(std::string S : names){
        file.open(S.c_str());
        std::vector<float> vec;
        for (std::string line;std::getline(file,line);)
            {
                vec.push_back(std::stof(line));
            }
        coef.push_back(vec);
        file.close();
    }
    
    //     std::cout<<"\n";
    //     std::cout<<"\n";

    // for(std::vector<float> c : coef){
    //     for(float d : c){
    //         std::cout<<d<<"\n";
    //     }
    //     std::cout<<"\n";
    //}

}

int main(){
        show();
    return 0;
}