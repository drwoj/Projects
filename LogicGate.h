#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>


class LogicGate
{
protected:
	std::string name = "Default";
	bool output = false;
	unsigned numInputs;

	std::vector<std::shared_ptr<LogicGate>>inputGates; //stores connected input gates
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

	void initInputs(int n){
		int freeInputs = checkFreeInputs(n); //check number of initialised inputs
		bool value;

		if (freeInputs > 0) {

			printInputs();
			if (freeInputs == 1)
				std::cout << "input: ";
			else 
				std::cout << "inputs(" << freeInputs << "): ";

			for (int i = 0; i < freeInputs; ++i) {
				std::cin >> value;
				inputValues.push_back(value);
			}
		}
	}

	int checkFreeInputs(int n){ //checks how many inputs are uninitialised
		return n - inputGates.size() - inputValues.size();
	}

	void printInputs() {
		std::cout <<" (";
		for (auto gate : inputGates)
			std::cout << gate->getOutput();
		for (auto value : inputValues)
			std::cout << value;
		std::cout << ")";
	}

	LogicGate(std::string name, unsigned numInputs, std::initializer_list<std::shared_ptr<LogicGate>> inGates, std::initializer_list<bool> inValues)
		:name {name}, numInputs{ numInputs }, inputGates{ inGates }, inputValues{ inValues } {}

};

