/*
 * 吉陵基地
 * RSQ LC 2022-2023 制造
*/

#ifndef DECITHINK_CONFIGURE_H
#define DECITHINK_CONFIGURE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>



class Configure {
public:
    std::string Strategic_Formation,FileName;
    std::vector<int>Kicker_Action_Order;
    std::vector<int>NonKicker_Action_Order;
    Configure()
    { }
    Configure(std::string Filename)
    {
        FileName = Filename;
        parse();
    }
    bool parse()
    {
        std::string line,n,t;
        std::vector<std::string> FileData;
        std::ifstream fin;
        fin.open(("Setting/"+FileName+".set").c_str());

        if(!fin.is_open()) {
            std::cout<<"\n## Cannot Open File!!!! ##\n";
            exit(EXIT_FAILURE);
            return false;
        }
        while(getline(fin, line)) {
           FileData.push_back(line);
        }

        Strategic_Formation = FileData[0].erase(0 , 10);
        n = FileData[1].erase(0 , 16);
        n = n.erase(n.size()-1 , n.size()-2);
        t = FileData[2].erase(0 , 19);
        t = t.erase(t.size()-1 , t.size()-2);
        /*
         * Flags
         * Block = B
         * ChaseBall = C
         * Dribble = D
         * Mark = M
         * Pass = P
         * Shoot = S
         * Strategic Movement = s
         * Tackle = T
         * Trap = t
         * Unmark = U
         */
        for(auto i : n)
        {
            if(i==',')
                continue;
            if(i=='S')
                Kicker_Action_Order.push_back(1);
            if(i=='P')
                Kicker_Action_Order.push_back(2);
            if(i=='D')
                Kicker_Action_Order.push_back(3);
        }

        for(auto i : t)
        {
            if(i==',')
                continue;
            if(i=='B')
                NonKicker_Action_Order.push_back(1);
            if(i=='M')
                NonKicker_Action_Order.push_back(2);
            if(i=='T')
                NonKicker_Action_Order.push_back(3);
            if(i=='t')
                NonKicker_Action_Order.push_back(4);
            if(i=='C')
                NonKicker_Action_Order.push_back(5);
            if(i=='U')
                NonKicker_Action_Order.push_back(6);
            if(i=='S')
                NonKicker_Action_Order.push_back(7);
        }

        return true;
    }
    bool CreateConfigureFile(std::string Filename, std::string Formation, std::string KickerActionFlags , std::string NonKickerFlags)
    {
        std::ofstream fout((Filename+".set").c_str());
        if(!fout.is_open()) {
            std::cout<<"\n## Cannot Create File!!!! ##\n";
            exit(EXIT_FAILURE);
            return false;
        }

        fout<<"Formation="<<Formation<<std::endl;
        fout<<"Kicker Actions={"<<KickerActionFlags<<"}"<<std::endl;
        fout<<"NonKicker Actions={"<<NonKickerFlags<<"}"<<std::endl;

        fout.close();


        return true;
    }
};


#endif //DECITHINK_CONFIGURE_H
