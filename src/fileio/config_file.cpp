#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <map>

namespace{
std::map<std::string, std::string> mProperties;

std::string& trim(std::string &s)
{
    if (s.empty())
    {
        return s;
    }

    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);

    return s;
}

void readProperties()
{
    std::ifstream file("config.txt");
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::istringstream iss(line);
            std::string key;
            std::string value;
            if (getline(iss, key, '=') && getline(iss, value))
            {
                key = trim(key);
                value = trim(value);
                mProperties[key] = value;
            }
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file:" << "\n";
    }
}

}

int main()
{
    readProperties();
    std::cout << "key1: " << mProperties["key1"] << "\n";
    std::cout << "key2: " << mProperties["key2"] << "\n";
    std::cout << "key3: " << mProperties["key3"] << "\n";
    ::exit(0);
}