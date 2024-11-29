#include <iostream>
#include <string>
#include "mips.h"
using namespace std;

const int SIZE = 16;
const int EIGHT_BITS = 255;
const int THIRTY_TWO_BITS = 32; //To denote limit in string size
const string PROMPT_TO_DEC = "\nEnter up to 8 binary digits (0-1) ->";
const string PROMPT_TO_HEX = "\nEnter up to 32 Binary digits (0-1) ->";

// Defining linked list node structure
struct Node
{
	int bit = 0;
	string hex = "";
	Node* next = nullptr;
	Node* prev = nullptr;
};

// Decimal to Binary
void DecToBi(Node*& node, Node*& tail);
void BiToDec(string prompt);
int GetDec(string prompt);

// Hex to Binary, Decimal to Hex, Binary to Hex
void HexToBi(Node*& node, Node*& head, Node*& tail);
void DecToHex(Node*& node, Node*& tail, int i);
void BiToHex(string prompt, Node*& node, Node*& head, Node*& tail);
int EnterDecimal();
string EnterHex();

// Division operations and Input validation
void Divide(int& dividend, int divisor, int& quotient, int& remainder);
bool CheckDigit(string);
bool CheckHex(string hexNum);

// Linked list functions
void AddBitNode(Node*& node, Node*& tail, int remainder); 
void AddHexNode(Node*& node, Node*& tail, string hexValue, int remainder);
void PrintNodes(Node*& head);
void PrintNodesReverse(Node*& tail);
void PrintHexNodes(Node*& head);
void PrintHexNodesReverse(Node*& tail);


bool quitProgram();


void PrintRegMem(string *registers, string *memory); // Print registers and memory location data

int main()
{

    bool isConverting = true;
    string hexInput = " ";

    string registers[SIZE] = {"0000", "0001", "0002", "0003", 
                              "0004", "0005", "0006", "0007", 
                              "0008", "0009", "000A", "000B",
                              "000C", "000D", "000E", "000F"}; 

    string memory[SIZE] = {"0000", "0001", "0002", "0003", 
                           "0004", "0005", "0006", "0007", 
                           "0008", "0009", "000A", "000B",
                           "000C", "000D", "000E", "000F"};
    while (isConverting)
    {
        PrintRegMem(registers, memory);
        cout << "\n\n" << "Enter an 8 digit hexadecimal MIPS instruction -> ";
        hexInput = EnterHex();
    }
   
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

int EnterDecimal()
{
	int num = 0;

	//Input validation: all non digit inputs or inputs that are not 0-255 are invalid
	while (cout << "\nEnter any number 0-255 ->"
		&& !(cin >> num) || num < 0 || num > 255)
	{
		cout << "\nERROR: Integer is not within 0-255.";
		cin.clear(); 
		cin.ignore(1000, '\n');
	}

	return num;
}

string EnterHex()
{
	string hexNum;

	// Input validation: All inputs must correspond to hex values at base 16
    cin >> hexNum;
    
	while(!CheckHex(hexNum));
	{
		cin.ignore();
		cin.ignore(1000, '\n');
		cout << "\n" << "Enter an 8 digit hexadecimal MIPS instruction -> ";
		cin >> hexNum;
        //Added Condition: the hexadecimal input MUST be 8 digits so a mips instruction can be processed
	} 

	return hexNum;
}


void Divide(int &dividend, int divisor, int &quotient, int &remainder)
{
	quotient = dividend / divisor;

	// Remainder for Decimal to binary
	remainder = dividend % divisor; 

	// quotient = new dividend to extract remainder from
	dividend = quotient;
}

void DecToBi(Node*& node, Node*& tail)
{
	int dividend, quotient, remainder; 
	dividend = EnterDecimal();

	while (dividend > 0)
	{
		//Continue to divide the dividend by 2 until 2 is greater than the dividend ex: 2 / 1 exits the loop
		Divide(dividend, 2, quotient, remainder);

		//Create a new node that represents the corresponding binary digit
		AddBitNode(node, tail, remainder);
	}

	cout << "\nConverted to binary: ";
	PrintNodesReverse(tail);
	cout << "\n";
	cout << "\n------------------------------------------------------------";
}

void BiToDec(string prompt)
{
	int dec = 0;
	dec = GetDec(prompt); // Store decimal value here

	// Input validation: only 8 binary digits are allowed
	while (dec > EIGHT_BITS)
	{
		cout << "\nERROR: Input exceeds 8 bits";
		dec = GetDec(prompt);
	}
	cout << "\n" << "Converted to decimal: " << dec << "\n";
	cout << "\n------------------------------------------------------------";
}

int GetDec(string prompt)
{
	string digits = " ";
	int dec = 0; 
	cout << prompt;
	cin >> digits;

	// Input validation only binary digits are allowed.
	while (!CheckDigit(digits))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\nERROR: Input(s) include non-binary digits.";
		cout << prompt;
		cin >> digits;
	} 
	
	// Collect decimal value
	dec = stoi(digits, nullptr, 2);
	return dec;
}

void HexToBi(Node*& node, Node*& head, Node*& tail)
{
	string hexNum;
	hexNum = EnterHex();

	// For each character in the string, create a node that has data corresponding to its binary digit combination
	for (int i = 0; i < hexNum.length(); i++)
	{
		switch (hexNum[i])
		{
		case '0':
			AddHexNode(node, tail, "0000", 0);
			break;
		case '1':
			AddHexNode(node, tail, "0001", 1);
			break;
		case '2':
			AddHexNode(node, tail, "0010", 2);
			break;
		case '3':
			AddHexNode(node, tail, "0011", 3);
			break;
		case '4':
			AddHexNode(node, tail, "0100", 4);
			break;
		case '5':
			AddHexNode(node, tail, "0101", 5);
			break;
		case '6':
			AddHexNode(node, tail, "0110", 6);
			break;
		case '7':
			AddHexNode(node, tail, "0111", 7);
			break;
		case '8':
			AddHexNode(node, tail, "1000", 8);
			break;
		case '9':
			AddHexNode(node, tail, "1001", 9);
			break;
		case 'A':
			AddHexNode(node, tail, "1010", 10);
			break;
		case 'B':
			AddHexNode(node, tail, "1011", 11);
			break;
		case 'C':
			AddHexNode(node, tail, "1100", 12);
			break;
		case 'D':
			AddHexNode(node, tail, "1101", 13);
			break;
		case 'E':
			AddHexNode(node, tail, "1110", 14);
			break;
		case 'F':
			AddHexNode(node, tail, "1111", 15);
			break;
		default:
			break;
		}
	}

	cout << "\nConverted to hexadecimal:";
	AddHexNode(node, tail, "", 0);
	PrintHexNodes(head);
	cout << "\n";
	cout << "\n------------------------------------------------------------";
}

void BiToHex(string prompt, Node*& node, Node*& head, Node*& tail)
{
	int temp = 0;
	int dec = 0;
	int diff = 0;
	string bits = "";
	string sub = "";

	cout << prompt;
	cin >> bits;

	//Input validation: no more than 32 BINARY DIGITS will be accepted
	while (bits.length() > THIRTY_TWO_BITS || !CheckDigit(bits))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\nERROR: Input exceeds 32 binary digits OR input includes non-binary digits";
		cout << prompt;
		cin >> bits;
	}

	// make the length of the string 0-based
	temp = (bits.length() - 1);

	if (bits.length() <= 4)
	{
		// convert to decimal
		dec = stoi(bits, nullptr, 2);

		// convert to hex
		DecToHex(node, tail, dec);
	}
	else if (bits.length() > 4 && bits.length() <= 8)
	{
		//Get the substring of the first 4 characters
		sub = bits.substr(temp - 3, 4);

		// Convert to decimal 
		dec = stoi(sub, nullptr, 2);

		// Convert to hex and add to linked list
		DecToHex(node, tail, dec);

		// Get the substring of the remaining characters
		sub = bits.substr(0, temp - 3);

		// Convert to decimal 
		dec = stoi(sub, nullptr, 2);

		// Convert to hex and add to linked list
		DecToHex(node, tail, dec);
	}
	else
	{
		// Get the substring of the first 4 characters
		sub = bits.substr(temp - 3, 4);

		// Convert to decimal
		dec = stoi(sub, nullptr, 2);

		// Convert to hex
		DecToHex(node, tail, dec);

		// move the substring index down the string
		temp -= 3;

		while (!(temp-4 <= 0))
		{
			// Get the substring of the next 4 characters
			sub = bits.substr(temp - 4, 4);

			// convert to decimal
			dec = stoi(sub, nullptr, 2);

			// convert to hex
			DecToHex(node, tail, dec);

			// move the substring index down the string
			temp -= 4;

			// Check if the substring index <= 0
			if (temp - 4 <= 0)
			{
				diff = temp; // if so store it as diff
				temp -= 4;
			}
		}

		// The substring index before it's <= 0 is enough to get the remaining characters in the list 
		////// Get the substring of the remaining characters
		sub = bits.substr(0, diff);

		//convert to decimal
		dec = stoi(sub, nullptr, 2);

		//convert to hex
		DecToHex(node, tail, dec);
	}

	cout << "\nConverted to hexadecimal:";
	PrintHexNodesReverse(tail);
	cout << "\n";
	cout << "\n------------------------------------------------------------";
}

void DecToHex(Node*& node, Node*& tail, int i)
{
	// Converts a decimal value to its corresponding hex value by making a new node
	switch (i)
	{
	case 0:
		AddHexNode(node, tail, "0", 0);
		break;
	case 1:
		AddHexNode(node, tail, "1", 1);
		break;
	case 2:
		AddHexNode(node, tail, "2", 2);
		break;
	case 3:
		AddHexNode(node, tail, "3", 3);
		break;
	case 4:
		AddHexNode(node, tail, "4", 4);
		break;
	case 5:
		AddHexNode(node, tail, "5", 5);
		break;
	case 6:
		AddHexNode(node, tail, "6", 6);
		break;
	case 7:
		AddHexNode(node, tail, "7", 7);
		break;
	case 8:
		AddHexNode(node, tail, "8", 8);
		break;
	case 9:
		AddHexNode(node, tail, "9", 9);
		break;
	case 10:
		AddHexNode(node, tail, "A", 10);
		break;
	case 11:
		AddHexNode(node, tail, "B", 11);
		break;
	case 12:
		AddHexNode(node, tail, "C", 12);
		break;
	case 13:
		AddHexNode(node, tail, "D", 13);
		break;
	case 14:
		AddHexNode(node, tail, "E", 14);
		break;
	case 15:
		AddHexNode(node, tail, "F", 15);
		break;
	default:
		break;
	}
}

bool CheckDigit(string bits)
{
	int count = 0;

	// For loop steps through the string and increments the count by 1 
	// IF any character in the array is not a digit or not 0-1
	for (int i = 0; i < bits.length(); i++)
	{
		if (!isdigit(bits[i]) || bits[i] < '0' || bits[i] > '1')
		{
			count++;
		}
	}

	// If the count is not 0 then the string is invalid
	return (count == 0);
}

bool CheckHex(string hexNum)
{

	if (hexNum.length() < 8 || hexNum.length() > 8)
	{
		cout << "\nERROR: Input is not EXACTLY 8 digits";
		return false;
	}

	// For the length of this string, validate if each character is a digit or A-F
	for (int i = 0; i < hexNum.length(); i++)
	{
		// Alphanumeric error checking. No symbols accepted
		if (!isalnum(hexNum[i]))
		{
			cout << "\nERROR: Non-alphanumeric character(s) entered";
			return false;
		}

		// Alpha error checking A-F only accepted
		if (isalpha(hexNum[i]))
		{
			if (!(hexNum[i] >= 'A'  || hexNum[i] <= 'F'))
			{
				cout << "\nERROR: Characters other than A-F entered";
				return false;
			}
		}
	}
	return true;
}

void AddBitNode(Node*& node, Node*& tail, int remainder)
{
	// Adding a new node to the linked list for binary conversions
	node = new Node();
	node->bit = remainder;
	node->next = nullptr;
	node->prev = tail;
	tail->next = node;
	tail = node;
}

void AddHexNode(Node*& node, Node*& tail, string hexValue, int remainder)
{
	// Adding a new node to a linked list for hex Conversions
	node = new Node();
	node->hex = hexValue;
	node->next = nullptr;
	node->prev = tail;
	tail->next = node;
	tail = node;
}

void PrintNodes(Node*& head)
{
	// Traverse through list with this pointer
	Node* tempPtr = head;

	// All nodes are printed 
	while (tempPtr != nullptr)
	{
		cout << tempPtr->bit;
		tempPtr = tempPtr->next;
	}
}

void PrintNodesReverse(Node*& tail)
{
	// This pointer is for reading the data
	Node* tempPtr = tail;

	// This pointer prevents the function from reading the first node
	// For example 3 would display as 110 instead of 11 without this pointer
	Node* lookAheadPtr = tail;
	lookAheadPtr = lookAheadPtr->prev;

	// All nodes are printed in reverse order
	while (lookAheadPtr != nullptr)
	{
		cout << tempPtr->bit;
		tempPtr = tempPtr->prev;
		lookAheadPtr = lookAheadPtr->prev;
	}
}

void PrintHexNodes(Node*& head)
{
	// Traverse through list with this pointer
	Node* tempPtr = head;
	Node* lookAheadPtr = head;
	lookAheadPtr = lookAheadPtr->next;

	// All nodes are printed 
	while (lookAheadPtr != nullptr)
	{
		cout << tempPtr->hex;
		tempPtr = tempPtr->next;
		lookAheadPtr = lookAheadPtr->next;
	}
}

void PrintHexNodesReverse(Node*& tail)
{
	// Traverse through linked list with this pointer
	Node* tempPtr = tail;

	// All nodes are printed 
	while (tempPtr != nullptr)
	{
		cout << tempPtr->hex;
		tempPtr = tempPtr->prev;
	}
}

bool quitProgram()
{
	// ends program upon being called in the main function through a switch statement
	return false;
}