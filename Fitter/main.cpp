#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <vector>
#include <thread>
#include "src\pump.cpp"
#include "src\cleanup.cpp"
#include "src\spline.h"





std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

void turn_namefiles_content_into_function(){
    system("src\\calculate_coeficients.py");
}

int main(){
    // start:
    // std::cout<<"1. Run\n";
    // std::cout<<"2. Fast run\n";
    // std::cout<<"3. Cleanup\n";
    // std::cout<<"4. End\n";
    // int c;
    // std::cin>>c;
    // switch (c){
    //     case 1:{
    //         std::string name;
    //         float input[4];
    //         std::cout<<"Podaj dane wejiowe"<<"\n";
            
    //         std::cout<<"Nawa pompy: ";
    //         std::cin>>name;

    //         std::cout<<"Hg: ";
    //         std::cin>>input[0];

    //         std::cout<<"Hd: ";
    //         std::cin>>input[1];

    //         std::cout<<"Q: ";
    //         std::cin>>input[2];

    //         std::cout<<"n: ";
    //         std::cin>>input[3];

    //         pump pump1(name,input[0],input[1] ,input[2] ,input[3]);     
    //         pump1.store_to_namefile(pump1.create_HQ_file());
    //         pump1.store_to_namefile(pump1.create_PQ_file());

    //         std::thread python(turn_namefiles_content_into_function);
    //         python.join();
    //         pump1.store_coef_to_vector();
    //         pump1.store_to_namefile(pump1.generate_dataset());
    //         pump1.goodnes();
    //         getchar();
    //         getchar();
    //         break;
    //     }
    //     case 2:{
    //         std::string name;
    //         float input[4];
    //         name="80-250-1";
    //         input[0]=2;
    //         input[1]=91;
    //         input[2]=147;
    //         input[3]=3000;

    //         pump pump1(name,input[0],input[1] ,input[2] ,input[3]);     
    //         pump1.store_to_namefile(pump1.fast_create_HQ_file());
    //         pump1.store_to_namefile(pump1.fast_create_PQ_file());

    //         std::thread python(turn_namefiles_content_into_function);
    //         python.join();
    //         pump1.store_coef_to_vector();
    //         pump1.store_to_namefile(pump1.generate_dataset());
    //         pump1.goodnes();
    //         getchar();
    //         getchar();
    //         break;
    //     }
    //     case 3:
    //         cleanup();
    //         break;
        
    //     case 4:
    //         goto end;
    //         break;
    // }
    // goto start;

    // end:
    // getchar();
    
    // std::cout<<glm::pow(2,2);

    std::vector<double> X={0,1,2,3};
    std::vector<double> Y={0,0,1,1};

    tk::spline s(X,Y);
    std::cout<<s(1.3);

    return 0;
}