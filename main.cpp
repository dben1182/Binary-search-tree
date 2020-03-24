#include <iostream>
#include <fstream>
#include"BinarySearchTree.h"

using namespace std;

string inputCommands[] = { "INT","STRING", "tree", "size", "clear", "print", "add","remove", "find"};
int NUM_COMMANDS = 9;
const string TRUE_STRING = " true";
const string FALSE_STRING = " false";
const string FOUND_STRING = " found";
const string NOT_FOUND_STRING = " not found";

struct inputReturns
{
	int commandNumber = 0;//indicates which command from prompt was given
	string inputInformation = "";//indicates what data to manipulate in tree
};

inputReturns getInputValues(string line);//function returns values for a specific line of code


int main(int argc, char* argv[])
{
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	string inputLine = "";
	inputReturns myReturns;
	
	BinarySearchTree<int> intTree;
	BinarySearchTree<string> stringTree;
	bool editingInt = true;
	int inputConversion = 0;
	while (!inputFile.eof())
	{
		getline(inputFile, inputLine);
		myReturns = getInputValues(inputLine);
		//string inputCommands[] = { "INT","STRING", "tree", "size", "clear", "print", "add","remove", "find"};
		outputFile << inputLine;
		switch (myReturns.commandNumber)
		{
		case 0://case INT
			editingInt = true;
			outputFile << TRUE_STRING << endl;
			break;
		case 1://case STRING
			editingInt = false;
			outputFile << TRUE_STRING << endl;
			break;
		case 2://case tree
			outputFile << ":" << endl;
			break;
		case 3://case size
			if (editingInt)
			{
				outputFile << " " << intTree.size() << endl;
			}
			else
			{
				outputFile << " " << stringTree.size() << endl;
			}
			break;
		case 4://case clear
			if (editingInt)
			{
				intTree.removeWholeTree();
			}
			else
			{
				stringTree.removeWholeTree();
			}
			outputFile << TRUE_STRING << endl;
			break;
		case 5://case print
			if (editingInt)
			{
				outputFile << ":";
				outputFile << intTree.toString();
			}
			else
			{
				outputFile << ":";
				outputFile << stringTree.toString();
			}
			outputFile << endl;
			break;
		case 6://case add
			if (editingInt)
			{
				inputConversion = stoi(myReturns.inputInformation);
				if (intTree.addNode(inputConversion))
				{
					outputFile << TRUE_STRING;
				}
				else
				{
					outputFile << FALSE_STRING;
				}
			}
			else
			{
				if (stringTree.addNode(myReturns.inputInformation))
				{
					outputFile << TRUE_STRING;
				}							 
				else						  
				{							  
					outputFile << FALSE_STRING;
				}

			}
			outputFile << endl;
			break;
		case 7://case remove
			if (editingInt)
			{
				inputConversion = stoi(myReturns.inputInformation);
				if (intTree.removeNode(inputConversion))
				{
					outputFile << TRUE_STRING;
				}
				else
				{
					outputFile << FALSE_STRING;
				}
			}
			else
			{
				if (stringTree.removeNode(myReturns.inputInformation))
				{
					outputFile << TRUE_STRING;
				}
				else
				{
					outputFile << FALSE_STRING;
				}

			}
			outputFile << endl;
			break;
		case 8://case find
			if (editingInt)
			{
				inputConversion = stoi(myReturns.inputInformation);
				if (intTree.find(inputConversion))
				{
					outputFile << FOUND_STRING;
				}
				else
				{
					outputFile << NOT_FOUND_STRING;
				}

			}
			else
			{
				if (stringTree.find(myReturns.inputInformation))
				{
					outputFile << FOUND_STRING;
				}
				else
				{
					outputFile << NOT_FOUND_STRING;
				}
				
			}
			outputFile << endl;
			break;
		default:
			break;
		}
	}

	inputFile.close();
	outputFile.close();

	return 0;
}


inputReturns getInputValues(string line)//returns input values from text document
{
	inputReturns myReturn;
	string command = "";
	bool getMore = false;
	unsigned int i = 0;//counter variable
	while (i < line.size())
	{
		command += line.at(i);
		i++;
		if (i < line.size())
		{
			if (line.at(i) == ' ')
			{
				break;
			}
		}
		
	}
	for (int j = 0; j < NUM_COMMANDS; j++)
	{
		if (command == inputCommands[j])
		{
			myReturn.commandNumber = j;
			break;
		}
	}
	if (myReturn.commandNumber <= 5)
	{
		return myReturn;
	}
	else
	{
		i++;//ignores space
		while (i < line.size())
		{
			myReturn.inputInformation += line.at(i);
			i++;
		}
		return myReturn;
	}
}
