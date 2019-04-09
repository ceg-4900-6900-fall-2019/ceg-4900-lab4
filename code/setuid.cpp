#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

using std::cout; using std::endl; using std::string;
 
int main(int argc, char** argv)
{
    if (argc == 1 ) {
        cout << "Use this program to execute commands as another user.\n";
        cout << "Example: ./setuid [commands] \n";
        return 0;
    }
    std::string str;
    for(int i = 1; i < argc; i++){
        str = str + " " + argv[i];
    }
    cout << "Running: " << str << "\n";
    const char *command = str.c_str();
    std::system(command);
    return 0;
}
