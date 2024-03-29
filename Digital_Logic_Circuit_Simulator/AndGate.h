#pragma once
#include "LogicGate.h"

class AndGate : public LogicGate
{
public:
	void doLogic() override {

		initInputs();

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
		std::shared_ptr<LogicGate> temp;
		for (auto gate : inputGates) {
			temp = gate.lock();
			if (!temp->getOutput())
				return false;
		}
		
		return true;
	}

	bool doLogicValues() {
		for (auto value : inputValues)
			if (!value)
				return false;

		return true;
	}

	AndGate(std::string name, unsigned numInputs, std::vector<std::weak_ptr<LogicGate>> inGates, std::vector<bool> inValues)
		: LogicGate(name, numInputs, inGates, inValues){}


	~AndGate() {
	//	std::cout << "Destructor called ";
	}
};