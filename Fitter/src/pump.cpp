#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <vector>
#include <algorithm>
#include "point.cpp"
#include <boost/math/tools/polynomial_gcd.hpp>
#include <boost/math/tools/polynomial.hpp>
using std::string;
using std::cout;
// using std::abs;
// using std::pair;

// using namespace boost::math;
// using namespace boost::math::tools; // for polynomial
using boost::lexical_cast;


// using namespace boost::math::tools; // for polynomial



#define GRAVITY 9.81
#define WATER_DENSITY 998

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
    std::vector<std::vector<float>> equasion;

    std::vector<point> work_points;
    point work_point;

    public:
    pump(std::string name ,float iHg_d ,float iHd_d ,float iQ_d ,float in ):
        File_name_storage("file_names.txt"),
        Hg_d(iHg_d),
        Hd_d(iHd_d),
        Q_d(iQ_d),
        n(in),
        R((iHd_d-iHg_d)/(pow(iQ_d,2))),
        work_point(0,0)
    {
        this-> name=name;
    }

    void store_to_namefile(std::string name){//zapisuje podaną nazwę pliku do pliku file_names(pliki z tej listy zostaną przerobione prze python na wspóczynniki wielominów a na końcu usunięte) 
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
            file<<*p.print()<<"\n";
            // std::cout<<*p.print()<<"\n";
            file<<*(p.print()+1)<<"\n";
            // std::cout<<*(p.print()+1)<<"\n";
        }
        
        file.close();
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
            file<<*p.print()<<"\n";
            file<<*(p.print()+1)<<"\n";
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
            QH_points.push_back(*pt);
            delete pt;
        }

        std::ofstream file;
        std::string current_name=name+"_HQ.txt";
        file.open(current_name.c_str());
        for (point p : QH_points)
        {   
            file<<*(p.print())<<"\n";
            // cout<<*(p.print())<<"\n";
            file<<*(p.print()+1)<<"\n";
            // cout<<*(p.print()+1)<<"\n"; 
        }
        
        file.close();

        std::ofstream name_file;

        name_file.close();
        return current_name;
    }

    std::string fast_create_PQ_file(){
        std::vector<point> PQ_points;
        for(int i = 0; i < 4 ; i++){
            float X=i;
            float Y=i;
            point *pt = new point(X,Y);
            PQ_points.push_back(*pt);
            delete pt;
        }

        std::ofstream file;
        std::string current_name=name+"_PQ.txt";
        file.open(current_name.c_str());
        for (point p : PQ_points)
        {   
            file<<*(p.print())<<"\n";
            //cout<<*(p.print())<<"\n";
            file<<*(p.print()+1)<<"\n";
            //cout<<*(p.print()+1)<<"\n"; 
            // for (size_t i = 0; i < 2; i++)
            // {
            //     file<<*(p.print()+i)<<"\n";
            // }  
        }
        
        file.close();

        std::ofstream name_file;

        name_file.close();
        return current_name;

    }

    void store_coef_to_vector(){//spisuje współczynniki z plików do odpowiednich wektorów
        std::fstream file;
        std::string tmp;

        file.open((name+"_HQ.txt").c_str());
        while (std::getline(file , tmp)){
            HQ_equasion.push_back(std::stof(tmp));
        }
        file.close();
        std::reverse(HQ_equasion.begin(),HQ_equasion.end());

        file.open((name+"_PQ.txt").c_str());
        while (std::getline(file , tmp)){
            PQ_equasion.push_back(std::stof(tmp));
        }
        file.close();
        std::reverse(PQ_equasion.begin(),PQ_equasion.end());

        dHuQ_equasion.push_back(Hg_d);
        dHuQ_equasion.push_back(0);
        dHuQ_equasion.push_back(R);        
    }

    float value_of_H(float Q){
        boost::math::tools::polynomial<float> f(HQ_equasion.begin(),HQ_equasion.end());
        return f.evaluate(Q);
    }

    float value_of_dHu(float Q){
        boost::math::tools::polynomial<float> f(dHuQ_equasion.begin(),dHuQ_equasion.end());
        return f.evaluate(Q);
    }
    
    float value_of_P(float Q){
        boost::math::tools::polynomial<float> f(PQ_equasion.begin(),PQ_equasion.end());
        return f.evaluate(Q);
    }
    
    float value_of_Ph(float Q){
        return (WATER_DENSITY*GRAVITY*(Q/3600)*value_of_H(Q))/1000;
    }
    
    float value_of_ni(float Q){
        return value_of_Ph(Q)/value_of_P(Q);
    }
    
    float value_of_e(float Q){
        return value_of_P(Q)/(Q*1000);
    }
    
    std::string generate_dataset(){
        std::ofstream data;
        data.open(("dataset_"+name+".csv").c_str());
        data<<"Q"<<","<<"H"<<","<<"P"<<","<<"Ph"<<","<<"ni"<<","<<"e"<<","<<"dHu"<<"\n";
        for (float i = 0; i < 300; i+=0.1)
        {   
            float data_H=value_of_H(i);
            float data_dHu=value_of_dHu(i);
            float data_P=value_of_P(i);
            float data_Ph=value_of_Ph(i);
            float data_ni=value_of_ni(i);
            float data_e=value_of_e(i);
                        

            if(!(data_H<=data_dHu+0.1 && data_H>=data_dHu-0.1))
            {
                data<<i<<","<<data_H<<","<<data_P<<","<<data_Ph<<","<<data_ni<<","<<data_e<<","<<data_dHu<<"\n";
            }
            else{
                data<<i<<","<<data_H<<","<<data_P<<","<<data_Ph<<","<<data_ni<<","<<data_e<<","<<data_dHu<<","<<"Punkt pracy"<<"\n";
                point *wp = new point(i,data_dHu);
                work_points.push_back(*wp);
                delete wp;
            }
        }
        data.close();
        float sum_Q, sum_H;
        for(point p : work_points){
            sum_Q+=*(p.print());
            sum_H+=*(p.print()+1);
        }

        work_point.edit(sum_Q/work_points.size(),sum_H/work_points.size());
        std::cout<<"punkt pracy to : ("<<*(work_point.print())<<" , "<<*(work_point.print()+1)<<")"<<std::endl;

        getchar();
        return "dataset_"+name+".csv";
    }

    float score_work_point_accuracy(){
        float weight_work_point_accuracy;
        cout<<"Podaj wagę(miedzu 0 i 1) dla: \nDokładność doboru: ";
        std::cin>>weight_work_point_accuracy;

        std::ofstream data_file;
        data_file.open("dataset_"+name+".csv",std::ios_base::app);
        data_file<<"\n\n"<<"Dokładność doboru"<<","<< 10/std::sqrt( std::pow (std::abs(Hd_d-*(work_point.print())),2) + std::pow( std::abs(Hd_d-*(work_point.print()+1)),2)) <<","<<"Waga"<<","<<weight_work_point_accuracy<<"\n";
        data_file.close();
        
        return 10/std::sqrt( std::pow (std::abs(Hd_d-*(work_point.print())),2) + std::pow( std::abs(Hd_d-*(work_point.print()+1)),2))*weight_work_point_accuracy;
    }
  
    float score_efficiency_in_wanted_work_point(){
        float weight_efficiency_in_wanted_work_point;
        cout<<"Sprawność dal założonego punktu pracy: ";
        std::cin>>weight_efficiency_in_wanted_work_point;

        std::ofstream data_file;
        data_file.open("dataset_"+name+".csv",std::ios_base::app);
        data_file<<"Sprawność dal założonego punktu pracy"<<","<< value_of_ni(Q_d) <<","<<"Waga"<<","<<weight_efficiency_in_wanted_work_point<<"\n";
        data_file.close();

        return (value_of_ni(Q_d))*weight_efficiency_in_wanted_work_point;
    }

    float score_power_per_cubic_meater_in_wanted_work_point(){
        float weight_power_per_cubic_meater_in_wanted_work_point;
        cout<<"Moc na metr sześcienny przepływu: ";
        std::cin>>weight_power_per_cubic_meater_in_wanted_work_point;

        std::ofstream data_file;
        data_file.open("dataset_"+name+".csv",std::ios_base::app);
        data_file<<"Moc na metr sześcienny przepływu"<<","<<1/value_of_e(Q_d)<<","<<"Waga"<<"," <<weight_power_per_cubic_meater_in_wanted_work_point<<"\n";
        data_file.close();
        return 1/value_of_e(Q_d)*weight_power_per_cubic_meater_in_wanted_work_point;
    }

    void goodnes(){
        std::vector<float> score;
        score.push_back(score_work_point_accuracy());
        score.push_back(score_efficiency_in_wanted_work_point());
        score.push_back(score_power_per_cubic_meater_in_wanted_work_point());
        float sc=0;
        for (float s : score){
            sc+=s;
        }

        cout<<"\nPompa uzyskała ocenę dobroci doboru: "<<sc<<std::endl;
        
        std::ofstream data_file;
        data_file.open("dataset_"+name+".csv",std::ios_base::app);
        data_file<<"Ocena doboru"<<","<<sc;
        data_file.close();
    }
    
};
 