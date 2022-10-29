#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <vector>
#include <thread>


#define GRAVITY 9.81
#define WATER_DENSITY 998


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

    float* print(){
        return pos;
    }
};


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

};

void turn_namefiles_content_into_function(){
    system("python\\calculate_coeficients.py");
}

std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

void collect_data(){
    std::string name;

    
    std::cout<<"Podaj nazwę pompy(bez znaków specjalnych): \n";
    std::getline(std::cin,name);


    std::ofstream file;

    std::string name_HQ=name+"_HQ.txt";
    std::cout<<"Podaj nazwę punkty z charakterystyki Q(H)\n";
    file.open(name_HQ.c_str());
    for (size_t i = 0; i < 12 ; i++)
    {   
        float x;
        if (i%2==0)
        {
            std::cout<<"Podaj Q"<<floor(i/2)<<": ";
            std::cin>>x;
            file<<x<<"\n";
            x=0;
        }
        else{
            std::cout<<"Podaj H"<<floor(i/2)<<": ";
            std::cin>>x;
            file<<x<<"\n";
            x=0;
        }
    }
    std::cout<<"\n";
    file.close();


    std::cout<<"Podaj nazwę punkty z charakterystyki P(H)\n";
    std::string name_P=name+"_P.txt";
    file.open(name_P.c_str());
    for (size_t i = 0; i < 4 ; i++)
    {   
        float x;
        if (i%2==0)
        {
            std::cout<<"Podaj Q: "<<ceil(i/2);
            std::cin>>x;
            file<<x<<"\n";
            x=0;
        }
        else{
            std::cout<<"Podaj P: "<<ceil(i/2);
            std::cin>>x;
            file<<x<<"\n";
            x=0;
        }
    }
    std::cout<<"\n";
    file.close();

    file.open("file_names.txt", std::ios_base::app);
    file<<name_HQ.c_str()<<"\n";
    file<<name_P.c_str()<<"\n";
    file.close();
    getchar();
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
    std::thread t1(turn_namefiles_content_into_function);
    t1.join();

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