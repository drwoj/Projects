#pragma once
#include "LogicGate.h"


class OrGate : public LogicGate
{
public:
	void doLogic() override {
		initInputs(); //initialise needed inputs

		if (doLogicValues()) {
			output = true;
			return;
		}

		if (doLogicGates()) {
			output = true;
			return;
		}

		output = false;
	}

	bool doLogicGates() {
		std::shared_ptr<LogicGate> temp;
		for (auto gate : inputGates) {
			temp = gate.lock();
			if (temp->getOutput())
				return true;
		}

		return false;
	}

	bool doLogicValues() {
		for (auto value : inputValues)
			if (value)
				return true;

		return false;
	}

	OrGate(std::string name, unsigned numInputs, std::vector<std::weak_ptr<LogicGate>> inGates, std::vector<bool> inValues)
		: LogicGate(name, numInputs, inGates, inValues) {}


	~OrGate() {
		//	std::cout << "Destructor called ";
	}
};