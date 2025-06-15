// TradingSystem Moda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "System.h"
#include "Commands/CommandFactory.h"



int main()
{
    System s;
    s.load();

    CommandFactory commandFactory;
    
    while (true) {
        char input[CONSTANTS::MAX_LENGTH];
        std::cin.getline(input, CONSTANTS::MAX_LENGTH);

        if (strcmp(input, "save") == 0) break;

        if (Command* cmd = commandFactory.create(input)) { 
            try {
                cmd->execute(s);
            }
            catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }

            delete cmd;
        }
        else {
            std::cout << "Invalid command! Please try again" << std::endl;
        }
    }
    
}

