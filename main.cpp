#include <iostream>
#include <string>
#include "mips.h"

using namespace std;

const int SIZE = 16;

void PrintRegMem(string *registers, string *memory); // Print registers and memory location data

int main()
{
   string registers[SIZE] = {"0000", "0001", "0002", "0003", 
                             "0004", "0005", "0006", "0007", 
                             "0008", "0009", "000A", "000B",
                             "000C", "000D", "000E", "000F"}; 

    string memory[SIZE] = {"0000", "0001", "0002", "0003", 
                           "0004", "0005", "0006", "0007", 
                           "0008", "0009", "000A", "000B",
                           "000C", "000D", "000E", "000F"};

    PrintRegMem(registers, memory);

}


void PrintRegMem(string *registers, string *memory)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (i < 10)
        {
            cout << "\n" << "Reg[$" << i << "]   " << registers[i] << "  "
         << "Mem[" << i << "]   " << memory[i];
        }
        else
        {
             cout << "\n" << "Reg[$" << i << "]  " << registers[i] << "  "
         << "Mem[" << i << "]  " << memory[i];
        }
    }
    
}