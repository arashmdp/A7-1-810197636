#include "Network.h"
#include "Commands.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    Network* network = new Network();
    string line;
    while(getline(cin,line)){
        detectCommands(line,network);
    }
}