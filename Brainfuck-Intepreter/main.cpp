//
//  main.cpp
//  Brainfuck-Interpreter
//
//  Created by Edward Chu on 3/2/2017.
//  Copyright © 2017 Puffins. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>


//Manifest constants
const int MAX_ARRAY_SIZE = 10000;
const std::string PROGRAM_NAME = "program.txt";
const std::string OUTPUT_NAME = "output.txt";


//Function prototypes
bool isCommand(char c);
void intepretCommand(char*& currCommand, char*& ptr, std::ofstream &output);
bool writeToFile(char c, std::ofstream &output);


int main() {
    
    //Opening program and removing comments
    std::string command;
    std::ifstream program (PROGRAM_NAME);
    std::ofstream output;
    output.open(OUTPUT_NAME);
    
    if(!output.is_open()){
        std::cout << "Unable to open output.txt" << std::endl;
        return false;
    }
    
    
    if(!program.is_open()){
        std::cout << "Unable to open program.txt" << std::endl;
        return 1;
    }
    
    std::string line;
    while(getline(program,line))
    {
        command += line;
    }
    
    std::string sanitized;
    for(int i = 0; i < command.length(); i++){
        if (isCommand(command[i])){
            sanitized += command[i];
        }
    }
    
    
    //Initialization
    char values[MAX_ARRAY_SIZE];
    for(int i = 0; i < MAX_ARRAY_SIZE; i++){
        values[i] = '0';
    }
    
    char* currPtr = values;
    char* currCommand = &sanitized[0];
    
    //Run program
    while(currCommand - &sanitized[0] < sanitized.length()){
        intepretCommand(currCommand, currPtr, output);
        currCommand++;
    }
    
    program.close();
    output.close();
    
    std::cout << std::endl;
    
    return 0;
}

void intepretCommand(char*& currCommand, char*& ptr, std::ofstream &output){
    switch(*currCommand){
        case '>':
            ptr++;
            break;
            
        case '<':
            ptr--;
            break;
            
        case '+':
            (*ptr)++;
            break;
            
        case '-':
            (*ptr)--;
            break;
            
        case '.':
            std::cout << static_cast<char>(*ptr - 48);
            writeToFile(static_cast<char>(*ptr - 48), output);
            break;
            
        case ',':
        {
            std::cout << std::endl << "Input a char: ";
            char temp;
            std::cin >> temp;
            *ptr = temp;
            break;
        }
            
        case '[':
            if(*ptr == '0'){
                
                int count = 1;
                
                //Loop to find matching ']'
                while(count != 0){
                    currCommand++;
                    if(*currCommand == '[')
                        count++;
                    if(*currCommand == ']')
                        count--;
                }
            }
            break;
            
        case ']':
            if(*ptr != '0'){
                
                int count = -1;
                
                //Loop to find matching '['
                while(count != 0){
                    currCommand--;
                    if(*currCommand == '[')
                        count++;
                    if(*currCommand == ']')
                        count--;
                }
            }
            break;
            
        default:
            std::cout << "Invalid command detected";
            break;
    }
}

bool writeToFile(char c, std::ofstream &output){
    
    output << c;
    
    return true;
}

bool isCommand(char c){
    return c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']';
}
