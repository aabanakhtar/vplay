//
// Created by aabanakhtar on 9/29/25.
//
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <project_name>" << std::endl;
    }

    std::string project_name = "";
    std::cout << "Loading Project: " << project_name << std::endl;
    return 0;
}