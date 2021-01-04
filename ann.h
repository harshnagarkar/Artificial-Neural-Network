#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <cfloat>
#include <sstream>
#include <map>
#include "cmath"
#include <iostream>
#include <fstream>
#include "cmath"
#include <limits>
#ifndef ANN_H
#define ANN_H
using namespace std;


class Node

{
    public:
      vector<long double> weights;
      long double w;
      long double actFunc;
      long double delta;
    
    public:
        Node();
    vector<long double> get_weights();
    long double get_activation();
    long double get_delta();
    void set_weights(vector<long double> w);
    void set_activation(long double);
    void set_delta(long double d);
};

class Ann
{
    vector<vector<Node>> neural_net;
    vector<vector<long double>> input_vectors;
    vector<vector<long double>> computed_activations;
    vector<long double> outputs;
    long double alpha;
    int TP;
    int TN;
    int FP;
    int FN;
    public:
        Ann();
    void create_structure(string filename);
    void initialize_weights(string filename);
    void initilize_output_delta(int answer);
    long double activation_function(Node node, int layer, int index);
    long double delta_function(Node node, int layer, int index);
    long double output_activation(long double x, long double y);
    void update_weights(long double alpha);
    void initialize_input(vector<long double> data);
    void backpropogation(string filename, string outputfilename, int iterations);
    void set_alpha(long double a);
    void Test_inputs(string filename, string outfile);
    long double calculate_distance(long double x1, long double x2);
    void store_activations_values();
    void reset_activations_values();
    // Node Ann::get_weights(Node n);
};

#endif // NODE_H