#pragma once
#include "AndGate.h"

class Circuit
{
	

public:
	
	std::vector<std::shared_ptr<LogicGate>> gates;

	//all parameters
	void addAnd(std::string name, unsigned numInputs, std::initializer_list<std::string> inGates, std::initializer_list<bool> inValues) {

		std::vector <std::shared_ptr<LogicGate>> foundGates;

		for (std::string gate : inGates) {
			auto ptr = getGate(gate);
			foundGates.push_back(ptr);
		}
		
		std::initializer_list<std::shared_ptr<LogicGate>>temp(&foundGates.front(), &foundGates.front()+foundGates.size());
		

		AndGate g(name, numInputs, temp, inValues);
		auto ptr = std::make_shared<AndGate>(g);
		gates.push_back(ptr);
	}

	// without input gates
	void addAnd(std::string name, unsigned numInputs, std::initializer_list<bool> inValues){

		AndGate g(name, numInputs, {}, inValues);
		auto ptr = std::make_shared<AndGate>(g);
		gates.push_back(ptr);
	}

	//without input values
	void addAnd(std::string name, unsigned numInputs, std::initializer_list<const char*> inGates) {

		std::vector <std::shared_ptr<LogicGate>> foundGates;

		for (std::string gate : inGates) {
			auto ptr = getGate(gate);
			foundGates.push_back(ptr);
		}

		std::initializer_list<std::shared_ptr<LogicGate>>temp(&foundGates.front(), &foundGates.front() + foundGates.size());


		AndGate g(name, numInputs, temp, {});
		auto ptr = std::make_shared<AndGate>(g);
		gates.push_back(ptr);
	}
	
	//without inputs
	void addAnd(std::string name, unsigned numInputs) {

		AndGate g(name, numInputs, {}, {});
		auto ptr = std::make_shared<AndGate>(g);
		gates.push_back(ptr);
	}


	std::shared_ptr<LogicGate> getGate(std::string gateName) {
		for (int i = 0; i < gates.size(); i++)
			if (gates.at(i)->getName() == gateName)
				return gates.at(i);
	}
	
};

