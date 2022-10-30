#include <iostream>
#include <thread>
#include "pump.cpp"
#include "clenup.cpp"

void turn_namefiles_content_into_function(){
    system("calculate_coeficients.py");
}

void hide(){
    system("CLS");
}

void show(){
    start:
    std::cout<<"1. Run\n";
    std::cout<<"2. Fast run\n";
    std::cout<<"3. Cleanup\n";
    std::cout<<"4. End\n";
    int c;
    std::cin>>c;
    switch (c)
    {
        case 1:{
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
            std::cin>>input[3];

            pump pump1(name,input[0],input[1] ,input[2] ,input[3]);     
            pump1.store_to_namefile(pump1.create_HQ_file());
            pump1.store_to_namefile(pump1.create_PQ_file());

            // std::thread python(turn_namefiles_content_into_function);
            // python.join();
            break;
        }
        case 2:{
            std::string name;
            float input[4];
            name="80-250-1";
            input[0]=2;
            input[1]=91;
            input[2]=147;
            input[3]=3000;

            pump pump1(name,input[0],input[1] ,input[2] ,input[3]);     
            pump1.store_to_namefile(pump1.fast_create_HQ_file());
            pump1.store_to_namefile(pump1.fast_create_PQ_file());

            // std::thread python(turn_namefiles_content_into_function);
            // python.join();
            break;
        }
        case 3:
            cleanup();
            break;
        
        case 4:
            goto end;
            break;
    }

    hide();
    goto start;

    end:
    getchar();
}


