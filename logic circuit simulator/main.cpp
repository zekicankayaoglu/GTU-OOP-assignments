#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "gate.h"

using namespace std;

int main(){

    ifstream file("circuit.txt");
    ifstream file1("input.txt");
    int inputNumber = 0,in1,in2,inputs,input_number;
    char *temp;
    string name,line;
   
    Gate* gate[100];
    
    while(getline(file,line)){     //reading circuit file line by line 
        istringstream ss(line);
        ss >> name;
        if(name == "INPUT"){//if keyword is input 
            while(ss >> name){//takes all inputs to first elements of gate
                gate[inputNumber] = new input;
                gate[inputNumber]->output_name = name;
                inputNumber++;//counts element of gate array
            }
            input_number = inputNumber;//keeps number of inputs
        }
        
        else if(name == "OUTPUT"){//takes outputs names after input elements
            while(ss >> name){
                gate[inputNumber] = new output;
                gate[inputNumber]->output_name = name;
                gate[inputNumber]->value = 0;//all elements 0 for now
                inputNumber++;   
            }            
        }
        else if(name == "AND"){//if keyword is and
            gate[inputNumber] = new and_gate;
            ss >> name;
            gate[inputNumber]->output_name = name;//gets name of gate
            ss >> name;
            gate[inputNumber]->input_1 = name;//gets first input of gate
            ss >> name;
            gate[inputNumber]->input_2 = name;//gets second input of gate
            
            for(int i=0;i<inputNumber;i++){//finds first input's address in gate array
                if(gate[inputNumber]->input_1 == gate[i]->output_name){
                    gate[inputNumber]->in1 = gate[i];//takes in1
                    if(gate[i]->getClass() == "flipflop"){//checks input is it flipflop or not
                        gate[i]->flipCounter++;//if it is flipflop counts it
                        
                    }
                }
                else if(gate[inputNumber]->input_2 == gate[i]->output_name){//finds second input's address in gate array
                    gate[inputNumber]->in2 = gate[i];//takes in2
                    if(gate[i]->getClass() == "flipflop"){
                        gate[i]->flipCounter++;//counts flipflop
                    }
                }
            }
            inputNumber++;
        }
        else if(name == "OR"){//same things with and
            gate[inputNumber] = new or_gate;
            ss >> name;
            gate[inputNumber]->output_name = name;
            ss >> name;
            gate[inputNumber]->input_1 = name;
            ss >> name;
            gate[inputNumber]->input_2 = name;
            
            for(int i=0;i<inputNumber;i++){
                if(gate[inputNumber]->input_1 == gate[i]->output_name){
                    gate[inputNumber]->in1 = gate[i];
                    if(gate[i]->getClass() == "flipflop"){
                        gate[i]->flipCounter++;
                    }
                }
                else if(gate[inputNumber]->input_2 == gate[i]->output_name){
                    gate[inputNumber]->in2 = gate[i];
                    if(gate[i]->getClass() == "flipflop"){
                        gate[i]->flipCounter++;
                    }
                }
            }
            inputNumber++;
        }
        else if(name == "NOT"){//same things but just there is not second input
            gate[inputNumber] = new not_gate;
            ss >> name;
            gate[inputNumber]->output_name = name;
            ss >> name;
            gate[inputNumber]->input_1 = name;
          
            for(int i=0;i<inputNumber;i++){
                if(gate[inputNumber]->input_1 == gate[i]->output_name){
                    gate[inputNumber]->in1 = gate[i];
                    if(gate[i]->getClass() == "flipflop"){
                        gate[i]->flipCounter++;
                    }
                } 
            }
            inputNumber++;
        }

        else if(name == "FLIPFLOP"){//same as not
            gate[inputNumber] = new flipflop;
            ss >> name;
            gate[inputNumber]->output_name = name;
            ss >> name;
            gate[inputNumber]->input_1 = name;
            gate[inputNumber]->in2 = gate[0];
            
            for(int i=0;i<inputNumber;i++){
                if(gate[inputNumber]->input_1 == gate[i]->output_name){
                    gate[inputNumber]->in1 = gate[i];
                    if(gate[i]->getClass() == "flipflop"){
                        gate[i]->flipCounter++;
                    }                  
                }
            }
            inputNumber++;           
        }

        else if(name == "DECODER"){//if keyword is decoder
            gate[inputNumber] = new decoder;
            ss >> name;//these names are names of outputs so they are not important because we keept output names before
            ss >> name;
            ss >> name;
            ss >> name;
            ss >> name;
            gate[inputNumber]->input_1 = name;
            ss >> name;
            gate[inputNumber]->input_2 = name;
            for(int i=0;i<inputNumber;i++){//finds addresses of inputs
                if(gate[inputNumber]->input_1 == gate[i]->output_name){
                    gate[inputNumber]->in1 = gate[i];
                    if(gate[i]->getClass() == "flipflop"){
                        gate[i]->flipCounter++;
                    }
                }
                else if(gate[inputNumber]->input_2 == gate[i]->output_name){
                    gate[inputNumber]->in2 = gate[i];           
                    if(gate[i]->getClass() == "flipflop"){
                        gate[i]->flipCounter++;
                    }
                }
            }
        }    
    }

    int x = 0,num = 0;
    while(file1 >> inputs){//reads inputtxt file line by line
        gate[num]->value = inputs;//gets inputs into value variable 
        num++;
        if(num == input_number){//when line finished
            num = 0;
            int output = gate[inputNumber]->evaluate();//calls evaluate function of decoder class 
            gate[input_number+output]->value = 1;//just one of output becomes 1
            for(int i = input_number;i < input_number+4;i++){
                cout << gate[i]->value <<" ";//prints outputs
                gate[i]->value = 0;//makes them all 0 again
            }
            cout << endl;
        }
    }
}


