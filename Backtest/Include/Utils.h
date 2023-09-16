//
// Created by TangShangtao on 2023/9/4.
//
#include <sstream>
#include <string>
#include <vector>


class StrUtils
{
public:
    static std::vector<std::string> SplitString(const std::string &str, char delimiter) 
    {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string token;
        
        while (std::getline(ss, token, delimiter)) 
        {
            result.push_back(token);
        }

        return result;
    }

};