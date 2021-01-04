#include "ann.h"
using namespace std;

vector<vector<long double>> output_vector = {{0.1, 0.9, 0.9, 0.1, 0.9, 0.9, 0.1, 0.9, 0.9, 0.1},
                                             {0.9, 0.1, 0.9, 0.9, 0.1, 0.9, 0.9, 0.1, 0.9, 0.9},
                                             {0.9, 0.9, 0.1, 0.9, 0.9, 0.1, 0.9, 0.9, 0.1, 0.9},
                                             {0.1, 0.1, 0.9, 0.9, 0.1, 0.1, 0.9, 0.9, 0.1, 0.1},
                                             {0.9, 0.1, 0.1, 0.9, 0.9, 0.1, 0.1, 0.9, 0.9, 0.1},
                                             {0.9, 0.9, 0.1, 0.1, 0.9, 0.9, 0.1, 0.1, 0.9, 0.9},
                                             {0.1, 0.9, 0.1, 0.1, 0.9, 0.1, 0.1, 0.9, 0.1, 0.1},
                                             {0.9, 0.1, 0.1, 0.9, 0.1, 0.1, 0.9, 0.1, 0.1, 0.9},
                                             {0.1, 0.1, 0.9, 0.1, 0.1, 0.9, 0.1, 0.1, 0.9, 0.1},
                                             {0.1, 0.9, 0.9, 0.9, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9}};

Node::Node()
{
    w = 0.01;
    actFunc = 0.0;
    delta = 0.0;
    weights = {};
}
vector<long double> Node::get_weights()
{
    // cout<<"The weight forst: "<<weights.size()<<endl;
    return weights;
}

long double Node::get_activation()
{
    return actFunc;
}

long double Node::get_delta()
{
    return delta;
}

void Node::set_delta(long double d)
{
    delta = d;
}

void Node::set_weights(vector<long double> w)
{
    weights = w;
}

void Node::set_activation(long double a)
{
    actFunc = a;
}

Ann::Ann()
{
    input_vectors = {};
    outputs = {};
}

void Ann::set_alpha(long double a)
{
    alpha = a;
}

void Ann::create_structure(string filename)
{
    string line;
    ifstream myfile(filename);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::vector<string> lineData;
            std::stringstream lineStream(line);
            int value;
            while (lineStream >> value)
            {
                // cerr<<value;
                vector<Node> data_list;
                for (int i = 0; i < value; i++)
                {
                    Node n;
                    data_list.push_back(n);
                    // n=*Nodepte
                }
                neural_net.push_back(data_list);
            }
            // cout << neural_net.at(neural_net.size() - 1).size() << endl;
        }
        myfile.close();
    }
    // cerr << "create structure closed";
}

void Ann::initialize_weights(string filename)
{
    string line;
    ifstream myfile(filename);
    if (myfile.is_open())
    {
        for (int n = 0; n < neural_net.size() - 1; n++)
        {
            for (int m = 0; m < neural_net.at(n).size(); m++)
            {
                // cout<<"here "<<endl;
                getline(myfile, line);
                stringstream lineStream(line);
                string value;
                vector<long double> old = {};
                while (lineStream >> value)
                { //  vector<long double> w = neural_net.at(n).at(m).get_weights();
                    // neural_net.at(n).at(m).set_weights(w.push_back(stold(value)));
                    // cerr
                    old.push_back(stold(value));
                }
                neural_net.at(n).at(m).set_weights(old);
                // cerr<<" "<<neural_net.at(n).at(m).get_weights().size()<<endl;
            }
        }
    }
}

void Ann::initialize_input(vector<long double> data)
{
    // cerr<<data.size()<<" "<<neural_net.at(0).size()<<endl;
    for (int i = 0; i < neural_net.at(0).size(); i++)
    {
        // cout << data[i] << " ";
        neural_net.at(0).at(i).set_activation(data[i]);
    }
    // cout << endl;
}

long double Ann::output_activation(long double x, long double y)
{
    return pow(x * x + y * y, 1 / 2);
}

// void store_train_input(){

// }
// void store_train_output(){

// }

void Ann::backpropogation(string filename, string outputfilename, int iterations)
{
    string line;
    string line2;
    ifstream myfile(filename);
    ifstream outfile(outputfilename);
    // cout << "file is opening:" << endl;
    if (myfile.is_open() && outfile.is_open())
    {
        // cout << "before while" << endl;
        while (getline(myfile, line))
        {
            stringstream lineStream(line);
            string value;
            int counter = 0;
            vector<long double> first;
            while (lineStream >> value)
            {
                first.push_back((stold(value)));
            }
            // cout << "size of first: " << first.size() << endl;
            input_vectors.push_back(first);
            getline(outfile, line2);
            int answer = stoi(line2);
            outputs.push_back(answer);
        }
    }
    for (int z = 0; z < iterations; z++)
    {
        // cout << "interation: " << z << endl;
        // cout << input_vectors.size() << endl;
        for (int ds = 0; ds < input_vectors.size(); ds++)
        {
            initialize_input(input_vectors.at(ds));
            // cout<<input_vectors.at(ds);
            // for(int i =0;i<input_vectors.at(ds).size();i++){
            //     // for(int j =0;j<input_vectors.at(i).size())
            //     cout<<input_vectors.at(ds).at(i)<<" ";
            // }
            // cout<<endl;

            for (int i = 1; i < neural_net.size(); i++)
            {
                // cout<<"--------------"<<i<<"-----------------------";
                for (int j = 0; j < neural_net.at(i).size(); j++)
                {
                    neural_net.at(i).at(j).set_activation(activation_function(neural_net.at(i).at(j), i, j));
                }
            }

            initilize_output_delta(outputs.at(ds));

            for (int j = neural_net.size() - 2; j >= 0; j--)
            {
                for (int n = 0; n < neural_net.at(j).size(); n++)
                {
                    // cout<<" ergreg "<<endl
                    neural_net.at(j).at(n).set_delta(delta_function(neural_net.at(j).at(n), j, n));
                }
            }
            // } while (std::getline(myfile, line));
            update_weights(alpha);

            // for (int i = 0; i < neural_net.at(0).at(0).get_weights().size(); i++)
            // {
            //     cout << showpoint << fixed << setprecision(12) << neural_net.at(0).at(0).get_weights().at(i) << " ";
            // }
            // cout << endl;
        }
    }
    for (int i = 0; i < neural_net.at(0).at(0).get_weights().size(); i++)
    {
        cout << showpoint << fixed << setprecision(12) << neural_net.at(0).at(0).get_weights().at(i) << " ";
    }
    cout << endl;
    // store_activations_values();
    // cout << neural_net.at(0).at(0).get_weights().size() << endl;
}

void Ann::Test_inputs(string filename, string outfile)
{
    string line;
    string line2;
    ifstream myfile(filename);
    ifstream outs(outfile);
    int total = 0;
    int correct = 0;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {

            // reset_activations_values();
            stringstream lineStream(line);
            vector<long double> first = {};
            string value;
            while (lineStream >> value)
            {
                first.push_back(stold(value));
            }
            initialize_input(first);
            for (int i = 1; i < neural_net.size(); i++)
            {
                for (int j = 0; j < neural_net.at(i).size(); j++)
                {
                    // cout<<"\n=================== "<<i<<endlW;
                    neural_net.at(i).at(j).set_activation(activation_function(neural_net.at(i).at(j), i, j));
                }
            }

            long double min_val = std::numeric_limits<long double>::infinity();
            int digits = 0;
            // cout<<sizeof(output_vector)/sizeof(output_vector[0])<<endl;
            for (int i = 0; i < output_vector.size(); i++)
            {
                long double change_distance = 0.0;
                for (int j = 0; j < neural_net.at(neural_net.size() - 1).size(); j++)
                {
                    // cout<<"iter"<<endl;
                    long double act = neural_net.at(neural_net.size() - 1).at(j).get_activation();
                    // cout<<"finished "<<endl;
                    change_distance += calculate_distance(output_vector[i][j], act);
                }
                if (change_distance < min_val)
                {
                    // cout<<change_distance<<" "<<min_val<<" "<<j<<endl;
                    min_val = change_distance;
                    digits = i;
                }
            }
            // cout << "finished----------" << endl;
            cout << digits << endl;
            getline(outs, line2);
            if (stoi(line2) == digits)
            {
                correct++;
            }
            total++;
            // for (int i = 0; i < neural_net.size(); i++)
            // {
            //     for (int j = 0; j < neural_net.at(i).size(); j++)
            //     {
            //         neural_net.at(i).at(j).set_activation(computed_activations.at(i).at(j));
            //         // cout<<"changing"<<endl;
            //     }
            // }
        }
    }
    // cout<<"reached";
    cout << (long double)correct / (long double)total << endl;
}

void Ann::store_activations_values()
{
    for (int i = 0; i < neural_net.size(); i++)
    {
        vector<long double> acts = {};
        for (int j = 0; j < neural_net.at(i).size(); j++)
        {
            // cout<<"\n=================== "<<i<<endlW;
            acts.push_back(neural_net.at(i).at(j).get_activation());
        }
        computed_activations.push_back(acts);
    }
}

void Ann::reset_activations_values()
{
    for (int i = 1; i < neural_net.size(); i++)
    {
        for (int j = 0; j < neural_net.at(i).size(); j++)
        {
            neural_net.at(i).at(j).set_activation(computed_activations.at(i).at(j));
        }
    }
}

long double Ann::activation_function(Node node, int layer, int index)
{
    // cout<<"layer: "<<layer<<endl;
    long double inj = neural_net.at(layer).at(index).w;
    // cout << "Before--- \n"
    //  << " " << index << " " << layer << " " << neural_net.at(layer - 1).at(0).get_weights().at(index) << endl;
    for (int i = 0; i < neural_net.at(layer - 1).size(); i++)
    {
        // cout<< "Before \n"<<i<<" "<<index<<" "<<layer<<endl;
        inj += neural_net.at(layer - 1).at(i).get_weights().at(index) * neural_net.at(layer - 1).at(i).get_activation();
        // cout << "after" << endl;
    }
    long double ac = (long double)1.000 / ((long double)1.000 + exp(((long double)-1.00) * inj));
    // cout << "f" << endl;
    return ac;
}

void Ann::initilize_output_delta(int answer)
{
    for (int i = 0; i < neural_net.at(neural_net.size() - 1).size(); i++)
    {
        long double activation = neural_net.at(neural_net.size() - 1).at(i).get_activation();
        long double y = output_vector[answer][i];
        neural_net.at(neural_net.size() - 1).at(i).set_delta(activation * (1 - activation) * (y - activation));
    }
}

long double Ann::delta_function(Node node, int layer, int index)
{
    long double delta = 0.0;
    // cout<<"err";
    for (int i = 0; i < neural_net.at(layer).at(index).get_weights().size(); i++)
    {
        // cout<<"err";
        delta += neural_net.at(layer).at(index).get_weights().at(i) * neural_net.at(layer + 1).at(i).get_delta();
    }
    delta = delta * node.get_activation() * ((long double)1 - node.get_activation());
    return delta;
}

long double Ann::calculate_distance(long double x2, long double x1)
{
    long double distance = sqrt(pow(x2 - x1, 2));
    return distance;
}

//prev+alpha*delta_current_node
void Ann::update_weights(long double alpha)
{
    for (int i = 0; i < neural_net.size() - 1; i++)
    {
        // cout << " " << endl;
        for (int j = 0; j < neural_net.at(i).size(); j++)
        {
            // cout << " 2" << endl;
            vector<long double> weight_vector = {};
            for (int wi = 0; wi < neural_net.at(i).at(j).get_weights().size(); wi++)
            {
                // cout << " 3" << endl;
                long double prev = neural_net.at(i).at(j).get_weights().at(wi);
                // cout << "f: " << neural_net.at(i).size() << endl;
                long double actFunc = neural_net.at(i).at(j).get_activation();
                // cout << " i+1: " << i + 1 << "j " << j;
                long double delta = neural_net.at(i + 1).at(wi).get_delta();
                // cout<<prev + (alpha * delta * actFunc)<<endl;
                neural_net.at(i).at(j).weights.at(wi)=(prev + (alpha * delta * actFunc));
            }

            // neural_net.at(i).at(j).set_weights(weight_vector);
        }
    }
    for (int i = 0; i < neural_net.size(); i++)
    {
        // cout << " " << endl;
        for (int j = 0; j < neural_net.at(i).size(); j++)
        {
            neural_net.at(i).at(j).w = neural_net.at(i).at(j).w + alpha * neural_net.at(i).at(j).get_delta();
        }
    }
}
