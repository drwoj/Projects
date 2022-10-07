#pragma once
#include "LogicGate.h"

class NandGate : public LogicGate
{
public:
	void doLogic() override {

		initInputs();

		if (!doLogicValues()) {
			output = true;
			return;
		}

		if (!doLogicGates()) {
			output = true;
			return;
		}

		output = false;
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

	NandGate(std::string name, unsigned numInputs, std::vector<std::weak_ptr<LogicGate>> inGates, std::vector<bool> inValues)
		: LogicGate(name, numInputs, inGates, inValues) {}
};