#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <vector>
#include <thread>
#include "src\clenup.cpp"
#include "src\pump.cpp"

#define GRAVITY 9.81
#define WATER_DENSITY 998

void turn_namefiles_content_into_function(){
    system("calculate_coeficients.py");
}


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
    std::string name;
    float input[4];
    std::cout<<"Podaj dane wejiowe"<<"\n";
    
    std::cout<<"Nawa pompy: ";
    std::cin>>name;

    std::cout<<"Hg: ";
    std::cin>>input[0];

    std::cout<<"Hd: ";
    std::cin>>input[1];

    std::cout<<"Q: ";
    std::cin>>input[2];

    std::cout<<"n: ";
    std::cin>>input[2];

    pump pump1(name,input[0],input[1] ,input[2] ,input[3]);     
    pump1.store_to_namefile(pump1.create_HQ_file());
    pump1.store_to_namefile(pump1.create_PQ_file());

    std::thread python(turn_namefiles_content_into_function);
    python.join();

    //cleanup();
    // // std::cout<<"n: ";
    // // std::getline(std::cin, tmp);
    // // const float n_ini=std::stof(tmp);

    // // const float r=(Hd_ini-Hg_ini)/pow(Q_ini,2);

    // // collect_data();

    // generate_dataset();

    // std::fstream file("file_names.txt");
    // GotoLine(file,2);
    // std::string line;
    // file>>line;
    // std::cout<<line;
    return 0;
}