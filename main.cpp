#include "string"
#include <iostream>
#include "ann.h"
#include <fstream>
#include "cmath"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 7) //5
    {
        printf("Error: not enough arguments");
        exit(0);
    }

    Ann ai =  Ann();
    ai.set_alpha(0.01);
    ai.create_structure(argv[5]);
    ai.initialize_weights(argv[6]);
    ai.backpropogation(argv[1],argv[2], stoi(argv[7]));
    ai.Test_inputs(argv[3],argv[4]);

}
//  toy_trainInput.txt toy_trainOutput.txt toy_testInput.txt toy_testOutput.txt toy_structure.txt toy_weights.txt 1