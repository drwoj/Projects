#pragma once
#include "LogicGate.h"


//template<unsigned numInputs>
class AndGate : public LogicGate
{
public:
	void doLogic() override {

		initInputs(numInputs); //initialise needed inputs

		if (!doLogicValues()) {
			output = false;
			return;
		}

		if (!doLogicGates()) {
			output = false;
			return;
		}

		output = true;
	}

	bool doLogicGates() {
		for (auto gate : inputGates)
			if (!gate->getOutput()) 
				return false;
		
		return true;
	}

	bool doLogicValues() {
		for (auto value : inputValues)
			if (!value)
				return false;

		return true;
	}

	AndGate(std::string name, unsigned numInputs, std::initializer_list<std::shared_ptr<LogicGate>> inGates, std::initializer_list<bool> inValues)
		: LogicGate(name, numInputs, inGates, inValues){}


	~AndGate() {
	//	std::cout << "Destructor called ";
	}
};