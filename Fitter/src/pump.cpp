#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <vector>
#include "point.cpp"


class pump{

    const char* File_name_storage;

    std::string name;
    const float Hg_d ;
    const float Hd_d ;
    const float Q_d;
    const float n;
    const float R;

    std::vector<float> HQ_equasion;
    std::vector<float> PQ_equasion;
    std::vector<float> dHuQ_equasion;

    public:
    pump(std::string name ,float iHg_d ,float iHd_d ,float iQ_d ,float in ):
        File_name_storage("file_names.txt"),
        Hg_d(iHg_d),
        Hd_d(iHd_d),
        Q_d(iQ_d),
        n(in),
        R((iHd_d-iHg_d)/(pow(iQ_d,2)))
    {
        this-> name=name;
    }

    void store_to_namefile(std::string name){//zapisuje podaną nazwę pliku do pliky file_names(pliki z tej listy zostaną przerobione prze python na wspóczynniki wielominów) 
        std::ofstream name_file;
        name_file.open(File_name_storage, std::ios_base::app);
        name_file<<name<<"\n";
        name_file.close();
    }

    std::string create_HQ_file(){//tworzy plik z punktami z krzywej H(Q), zwraca nazę pliku w formacie "nazwa pompy+HQ.txt"
        std::vector<point> QH_points;
        for(int i = 0; i < 6 ; i++){
            std::string X="Q";
            std::string Y="H";
            X+=std::to_string(i);
            Y+=std::to_string(i);
            point *pt = new point(X,Y);
            QH_points.push_back(*pt);
            delete pt;
        }

        std::ofstream file;
        std::string current_name=name+"_HQ.txt";
        file.open(current_name.c_str());
        for (point p : QH_points)
        {   
            for (size_t i = 0; i < 2; i++)
            {
                file<<*p.print()+i<<"\n";
            }  
        }
        
        file.close();

        std::ofstream name_file;

        name_file.close();
        return current_name;
    }

    std::string create_PQ_file(){
           std::vector<point> PQ_points;
        for(int i = 0; i < 2 ; i++){
            std::string X="Q";
            std::string Y="P";
            X+=std::to_string(i);
            Y+=std::to_string(i);
            point *pt = new point(X,Y);
            PQ_points.push_back(*pt);
            delete pt;
        }

        std::ofstream file;
        std::string current_name=name+"_PQ.txt";
        file.open(current_name.c_str());
        for (point p : PQ_points)
        {   
            for (size_t i = 0; i < 2; i++)
            {
                file<<*p.print()+i<<"\n";
            }  
        }
        
        file.close();

        std::ofstream name_file;

        name_file.close();
        return current_name;

    }

    std::string fast_create_HQ_file(){//tworzy plik z punktami z parabolą(użytkownik nic nie wpisuje), zwraca nazę pliku w formacie "nazwa pompy+HQ.txt"
        std::vector<point> QH_points;
        for(int i = 0; i < 6 ; i++){
            float X=i+1;
            float Y=pow(X,2);
            point *pt = new point(X,Y);
            X=0;
            Y=0;
            QH_points.push_back(*pt);
            delete pt;
        }

        std::ofstream file;
        std::string current_name=name+"_HQ.txt";
        file.open(current_name.c_str());
        for (point p : QH_points)
        {   
            for (size_t i = 0; i < 2; i++)
            {
                file<<*(p.print()+i)<<"\n";
            }  
        }
        
        file.close();

        std::ofstream name_file;

        name_file.close();
        return current_name;
    }

    std::string fast_create_PQ_file(){
           std::vector<point> PQ_points;
        for(int i = 0; i < 2 ; i++){
            float X=i+1;
            float Y=X;
            point *pt = new point(X,Y);
            // for (size_t i = 0; i < 2; i++)
            // {
            //     std::cout<<*(pt->print()+i)<<"\n";
            // }  
            X=0;
            Y=0;
            PQ_points.push_back(*pt);
            delete pt;
        }

        std::ofstream file;
        std::string current_name=name+"_PQ.txt";
        file.open(current_name.c_str());
        for (point p : PQ_points)
        {   
            for (size_t i = 0; i < 2; i++)
            {
                file<<*(p.print()+i)<<"\n";
            }  
        }
        
        file.close();

        std::ofstream name_file;

        name_file.close();
        return current_name;

    }

};
