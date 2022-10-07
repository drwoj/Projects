#pragma once
#include "AndGate.h"
#include "NandGate.h"
#include "OrGate.h"
#include "NorGate.h"

class Circuit
{
	

public:
	
	std::vector<std::shared_ptr<LogicGate>> gates;

	//all parameters
	template<typename T>
	void addGate(std::string name, unsigned numInputs, std::vector<std::string> inGates, std::vector<bool> inValues) {

		std::vector <std::weak_ptr<LogicGate>> foundGates;

		for (std::string gate : inGates) {
			auto ptr = getGate(gate);
			foundGates.push_back(ptr);
		}		

		T g(name, numInputs, foundGates, inValues);
		auto ptr = std::make_shared<T>(g);
		gates.push_back(ptr);

	}


	void updateGates() {
		for (auto gate : gates)
			gate->initInputs();
	}
	
	void deleteGate(std::string name) {
		bool found = false;
		for (int i = -0; i < gates.size(); i++)
			if (gates.at(i)->getName() == name) {
				gates.erase(gates.begin() + i);
				found = true;
				break;
			}

		updateGates();
	}


	std::weak_ptr<LogicGate> getGate(std::string gateName) {
		for (int i = 0; i < gates.size(); i++)
			if (gates.at(i)->getName() == gateName)
				return gates.at(i);
	}

	bool checkGate(std::string gateName) {
		for (int i = 0; i < gates.size(); i++)
			if (gates.at(i)->getName() == gateName)
				return true;
		return false;
	}

	void setInputs(std::string name, std::list<bool>, std::list<std::weak_ptr<LogicGate>>) {
		auto gate = getGate(name);
		auto temp = gate.lock();
		
	}
	
	void displayGates() {
		for (auto gate : gates)
			gate->initInputs();


		for (auto gate : gates) {
			std::cout << std::endl << gate->getName();
			gate->printInputs();
			std::cout << "Output: " << gate->getOutput();
		}
	}
};

