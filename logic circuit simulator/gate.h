#include <iostream>

using namespace std;

class Gate{   
    public:
        int value,flipCounter = 0,flip=0,flip_temp =0,counter = 0;
        string input_1,input_2;
        string output_name;
        Gate* in1;
        Gate* in2;
        Gate(){};
        string classname;
        
        virtual int evaluate(){//evaluate function which takes two input and finds output of gate
            int output;
            return output;
        }
        virtual string getClass(){//get function to learn class
            return classname;
        }            
};

class input : public Gate{     
    public:
        int evaluate(){//input class's evaluate just return the value of input
            return value;
        }
};

class output : public Gate{
};

class and_gate : public Gate{
    public:
        int evaluate(){//calculates output of and gate
            int input1,input2,output;
            input1 = in1->evaluate();//calles in1's function to learn first input's value
            input2 = in2->evaluate();//calles in2's function to learn second input's value
            if(input1 == 1 && input2 == 1){
                output = 1;
            }
            else{
                output = 0;
            }           
            return output;
        }
};

class or_gate : public Gate{
    public:
        int evaluate(){//calculates output of or gate
            int input1,input2,output;
            input1 = in1->evaluate();
            input2 = in2->evaluate();
  
            if(input1 == 0 && input2 == 0){
                output = 0;
            }
            else{
                output = 1;
            }           
            return output;
        }
};

class not_gate : public Gate{
    public:
        int evaluate(){//calculates output of not gate
            int input1,output;
            input1 = in1->evaluate();
    
            if(input1 == 1){
                output = 0;
            }
            else{
                output = 1;
            }           
            return output;
        }
};

class flipflop : public Gate{
    public:
        int evaluate(){//calculates output of flipflop
            int input1,input2,output;
            input1 = in1->evaluate();
            input2 = flip;//flip is former out: if it is first line of input it is 0, if not it is former out
            flip_temp = flip;//temp variable for flip

            if(input1==input2){
                output = 0;
            }
            else if(input1 != input2){
                output = 1;
            }
            
            counter++;// counts number of times enter this func

            if(counter==flipCounter){//if it is equal to flipcounter 
                flip = output;//next flip becomes output of this flipflop
                counter = 0;
            }
            else if(counter<flipCounter){flip = flip_temp;}//if it is not equal flip becomes first flip again
                        
            return output;
        }
        string getClass(){
            return "flipflop";
        }
};

class decoder : public Gate{
    public:
        int evaluate(){//calculates output of decoder
            int input1,input2,output;
            input1 = in1->evaluate();
            input2 = in2->evaluate();
            //returns output
            if(input1 == 0 && input2 == 0){
                output = 0;
            }
            else if(input1 == 0 && input2 == 1){
                output = 1;// 0 1 0 0 
            }
            else if(input1 == 1 && input2 == 0){
                output = 2;// 0 0 1 0
            }
            else if(input1 == 1 && input2 == 1){
                output = 3;// 0 0 0 1
            }     
            return output;
        }
};

