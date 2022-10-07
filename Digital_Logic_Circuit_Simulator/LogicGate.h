#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <array>
#include <algorithm>


class LogicGate
{
protected:
	std::string name = "Default";
	bool output = false;
	unsigned numInputs;

	std::vector<std::weak_ptr<LogicGate>>inputGates; //stores connected input gates
	std::vector<bool> inputValues; // stores connected value;


public:
	virtual void doLogic() = 0;

	bool getOutput() {
		doLogic();
		return output;
	}

	std::string  getName() {
		return name;
	}

	void initInputs(){
		deleteExpiredInputs();
		int freeInputs = checkFreeInputs(); //check number of initialised inputs
		std::string input;
		int value;

		if (freeInputs > 0) {

			std::cout << name;
			printInputs();
			if (freeInputs == 1)
				std::cout << "set input: ";
			else 
				std::cout << "set inputs[" << freeInputs << "]: ";

			for (int i = 0; i < freeInputs; ++i) {
				std::cin >> input;
				value=parseInput(input);
				inputValues.push_back(value);
			}
		}
	}

	void setInputs() {

	}
	
	int parseInput(std::string s) {
		if (s == "1" || s == "true" || s == "TRUE" || s == "True")
			return true;
		else if (s == "0" || s == "false" || s == "FALSE" || s == "False")
			return false;
		else return 2;
	}


	int checkFreeInputs(){ //checks how many inputs are uninitialised
		return numInputs - inputGates.size() - inputValues.size();
	}

	bool checkIfInputExpired(int index) {
		if (inputGates.at(index).use_count()) 
			return false;
		
		return true;
	}

	void deleteExpiredInputs() {
		for (int i = 0; i < inputGates.size(); i++) {
			if (checkIfInputExpired(i))
				inputGates.erase(inputGates.begin() + i);
		}
	}

	void printInputs() {
		std::cout <<" (";
		std::shared_ptr<LogicGate> temp;
		for (auto gate : inputGates){
			temp = gate.lock(); //we have to convert weak to shared_ptr to access it's referenced object
			std::cout << temp->getOutput();
		}
		for (auto value : inputValues)
			std::cout << value;
		std::cout << ")";
	}

	LogicGate(std::string name, unsigned numInputs, std::vector<std::weak_ptr<LogicGate>> inGates, std::vector<bool> inValues)
		:name {name}, numInputs{ numInputs }, inputGates{ inGates }, inputValues{ inValues } {}

};

