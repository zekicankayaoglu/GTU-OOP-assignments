#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

//I accepted input's leftmost digit is 0 as an error(E0) because secret number's left most digit can not be 0.

//generates random number according to user's input size
void generate_number(int num[],int size);
//counts firstcount of inputs
int check_fcount(int num[], int size, int input[]);
//counts secondcount of inputs
int check_scount(int num[], int size, int input[]);
//learns length of char array.This function learns digit number of user input
int length_arr(char** argv);
//finds length of string
int check_string(string temp);
////learns input number's digit number and fills the num array with input
int input(int number,int num[]);

void generate_number(int num[],int size){  //generates random number
    int y,x=0,flag=0,temp[10];
    //firstly makes all elements of num -1 and temp -2
    for(int i=0;i<size;i++){
        num[i]=-1;
        temp[i]=-2;
    }
    //then finds a number to leftmost digit out of 0
    y=rand()%9+1;
    num[0]=y;
    temp[x]=y;//temp helps to compare digits in number each other to generate unique secret number
    x++;
    
    for(int i=1;i<size;i++){        
        y=rand()%10; //picks digits randomly   
        flag=0;       
        while(flag == 0){//then generates other digits of elements randomly in a loop
                flag=1;
                y=rand()%10;    
                num[i]=y;
                //checks same elements to make unique number
                for(int j=0;j<=x;j++){
                    if(temp[j]==num[i]) flag=0;                        
                }
        }
        num[i]=y;           
        temp[x]=y;
        x++;            
    }
}

int check_fcount(int num[], int size, int input[]){//finds first count
    int firstCount=0;
    //counts first count 
    for(int i=0;i<size;i++){          
        if(input[i] == num[i]){
            firstCount++;
        }
    }
    return firstCount;
}
int check_scount(int num[], int size, int input[]){ //finds second count  
    int secondCount=0;
    //counts second count
    for(int i=0;i<size;i++){//finds digits in another place
        for(int j=0;j<size;j++){
            if(input[i]==num[j]){
                if(input[i]!=num[i]) secondCount++;
            }  
        }   
    }
    return secondCount;
}
int check_argv(char** argv){
    int i=0,count=0;
    //finds length of char array 
    while(argv[1][i]!='\0' && argv[1][i]!=' '){
        count++;
        i++;
    }
    return count;
}
int length_arr(char** argv){
    int i=0,count=0;
    //finds length of char array 
    while(argv[2][i]!='\0'){
        count++;
        i++;
    }
    return count;
}

int check_string(string temp){//finds length of string
    int i=0,count=0;
    while(temp[i]!='\0'){
        count++;
        i++;
    }
    return count;  
}
int input(int number,int num[]){//takes input number and splits it into int array
    int size,count=0;
    int number2=number;
    //learns length of number
    while(number!=0){
        number = number / 10;
        count++;
    }
    size=count;
    for(int i=count-1;i>=0;i--){//makes number array with input number
        num[i]=number2 % 10;//fills the array digit by digit
        number2=number2/10;
    }
    return size;//returns size of input number
}

int main(int argc, char** argv){
    int num[10],num2[10],size,size1,size2,inputSize;
    int number,firstCount,secondCount;
    int count=0,length,flag=1,check,x=0;
    char temp2[10][10];
    string temp;
    srand(time(NULL));
    if(argc!=3){//if parameter number is not 3, gives error.
       cout<<"E0"<<endl;
            exit(0);  
    }
    //checks command line to learn it is 'r' or 'u'
    if(argv[1][1]=='r' && argv[1][0]=='-'){
        if(check_argv(argv)>2){
            cout<<"E0"<<endl;
            exit(0);
        }
        
        size1=length_arr(argv);//size1 for error situations
    
        if(size1>1){//if number digit bigger than 9 E0 ERROR!
            if(size1==2 && argv[2][0]=='1' && argv[2][1]=='0') size=10;
            else{
                cout<<"E0"<<endl;
                exit(0);
            }  
        }
        if(size1==1){
            size=argv[2][0]-'0';//checks size of secret number
        }

        if((argv[2][0]>'0' && argv[2][0]<='9')!=1){//if digit number isn't between 0-9 gives E0 ERROR!
            cout<<"E0"<<endl;
            exit(0);
        } 
        
        generate_number(num,size);//generates a random secret number
        while(1){        
            x=0;
            cin>>temp;//takes input
            size2=check_string(temp);//finds its length
            if(size2 == 1){//if number is just 1 digit, checks input is it integer or not
                if(temp[0]<'0' || temp[0]>'9'){
                        cout<<"E2"<<endl;//if input is not integer gives E2 ERROR
                        exit(0);
                    }    
            }
            for(int i=1;i<size2;i++){//checks string is it integer or not     
                    if(temp[i]<'0' || temp[i]>'9'){
                        cout<<"E2"<<endl;//if input is not integer gives E2 ERROR!
                        exit(0);
                    }         
            }
            if(temp[0] == '-'){//if input is negative it gives E0 ERROR!
                cout<<"E0"<<endl;
                exit(0);
            } 
            if(temp[0]<'0' || temp[0]>'9'){//if input's first digit is not integer gives E2 ERROR!
                cout<<"E2"<<endl;
                exit(0);
            }        
            if(size2>8){
                for(int i=0;i<size2;i++){
                    temp2[0][i]=temp[i];
                    num2[i]=temp2[0][i]-'0';
                    x++;
                }
                inputSize=x;
            }
            if(size2<9){
                number=stoi(temp);
                inputSize = input(number,num2);//finds input size to compare secret size    
            }
            if(temp[0]=='0') num2[0]=0;//because of stoi if first digit is 0 it doesnt see the 0               
            if(size2!=size){//if input size is bigger or less than secret number digit, it gives E1 ERROR!
                cout<<"E1"<<endl;
                exit(0);
            }
                
            for(int i=0;i<inputSize;i++){//checks input secret number to find is there any same digit
                for(int j=0;j<i;j++){
                    if(num2[i]==num2[j]){
                        cout<<"E1"<<endl;
                        exit(0);
                    }
                }
            }
            if(temp[0] == '0'){//if leftmost digit is 0 it gives E0 ERROR!
                cout<<"E0"<<endl;
                exit(0);
            }  

            firstCount = check_fcount(num,size,num2);
            secondCount = check_scount(num,size,num2);
            count++;//counts iteration
            if(count==100 && firstCount!=size){//if condition for iteration count if it is bigger than 100 gives error and exits
                cout<<"FAILED"<<endl;
                exit(0);
            }
            if(firstCount==size && secondCount==0 && size2!=0){//checks winning condition
                flag=1;
                break;
            }
            if(flag == 1){
                cout<<firstCount<<" "<<secondCount<<endl;//prints first and second counts
            }
        }
        if(flag == 1){
            cout<<"FOUND "<<count<<endl;//prints iteration count if user wins
        }
    }

    else if(argv[1][1]=='u' && argv[1][0]=='-'){//if user selects secret number
        if(check_argv(argv)>2){
            cout<<"E0"<<endl;
            exit(0);
        }
        size=length_arr(argv);//finds input's length
       
        for(int i=0;i<size;i++){//checks string is it integer or not     
                if(argv[2][i]<'0' || argv[2][i]>'9'){
                    cout<<"E0"<<endl;//if input is not integer gives E2 ERROR!
                    exit(0);
                }         
        }
        for(int i=0;i<size;i++){
            num[i]=argv[2][i]-'0';//converts char array to int array
        }
        if(num[0] == 0){//if leftmost digit is 0 it gives E0 ERROR!
            cout<<"E0"<<endl;
            exit(0);
        }
        
        for(int i=0;i<size;i++){//checks input secret number to find if there is any same numbers
            for(int j=0;j<i;j++){
                if(num[i]==num[j]){
                    cout<<"E0"<<endl;//if there are same digits in the input gives E0 ERROR!
                    exit(0);
                }
            }
        }       
        while(1){     
            x=0;       
            cin>>temp;//takes input as a string 
            size2=check_string(temp);//finds string's length
            if(size2 == 1){//if number is just 1 digit, checks input is it integer or not
                if(temp[0]<'0' || temp[0]>'9'){
                        cout<<"E2"<<endl;//if input is not integer gives E2 ERROR
                        exit(0);
                    }    
            }
            
            for(int i=1;i<size2;i++){//checks string is it integer or not     
                    if(temp[i]<'0' || temp[i]>'9'){
                        cout<<"E2"<<endl;//if input is not integer gives E2 ERROR!
                        exit(0);
                    }         
            }
            if(temp[0] == '-'){//if input is negative it gives E0 ERROR!
                cout<<"E0"<<endl;
                exit(0);
            } 
            if(temp[0]<'0' || temp[0]>'9'){//if input's first digit is not integer gives E2 ERROR!
                cout<<"E2"<<endl;
                exit(0);
            }       
            if(size2>8){//if input number's length is bigger than 8 stoi makes an error so I fixed it by this way
                for(int i=0;i<size2;i++){
                    temp2[0][i]=temp[i];//convert string to char 
                    num2[i]=temp2[0][i]-'0';//convert char to int
                    x++;
                }
                inputSize=x;
            }
            if(size2<9){
                number=stoi(temp);
                inputSize = input(number,num2);//finds input size to compare secret size    
                
            }
            if(temp[0]=='0') num2[0]=0;                          
            if(size2!=size){//if input size is bigger or less than secret number digit, it gives E1 ERROR!
                cout<<"E1"<<endl;
                exit(0);
            }
            if(temp[0] == '0'){//if leftmost digit is 0 it gives E0 ERROR!
                cout<<"E0"<<endl;
                exit(0);
            }     
            for(int i=0;i<size2;i++){//checks input secret number to find is there are same numbers
                for(int j=0;j<i;j++){
                    if(num2[i]==num2[j]){
                        cout<<"E1"<<endl;//if there are same digits in input, gives E1 ERROR!
                        exit(0);
                    }
                }
            }
            
            firstCount = check_fcount(num,size,num2);//finds first count    
            secondCount = check_scount(num,size,num2);//finds second count
            count++;//counts iteration

            if(count==100 && firstCount!=size){//if condition for iteration count, if it is bigger than 100 gives error and exits
                cout<<"FAILED"<<endl;
                flag=0;
                exit(0);
            }
            if(firstCount==size && secondCount==0){//checks winning condition
                flag=1;
                break;        
            }
            cout<<firstCount<<" "<<secondCount<<endl;//prints first and second counts
        }
        if(flag==1){
            cout<<"FOUND "<<count<<endl;//prints found if user wins
        }
    }
    else{
        cout<<"E0"<<endl;//if parameters are wrong in command,it gives E0 ERROR and exits
        exit(0);
    }
}