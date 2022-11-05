#include <iostream>


struct point{
    float pos[2];

    point(){
        std::cout<<"Podaj X: ";
        std::cin>>pos[0];
        std::cout<<"Podaj Y: ";
        std::cin>>pos[1];
    }

    point(std::string X_name,std::string Y_name){
        std::cout<<"Podaj "<<X_name<<": ";
        std::cin>>pos[0];
        std::cout<<"Podaj "<<Y_name<<": ";
        std::cin>>pos[1];
    }

    point(float X,float Y){
        pos[0]=X;
        pos[1]=Y; 
    }

    float* print(){
        return pos;
    }
    
    void edit(float X, float Y){
        pos[0]=X;
        pos[1]=Y;
    }

};
