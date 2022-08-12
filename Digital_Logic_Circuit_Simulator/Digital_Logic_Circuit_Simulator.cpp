#include <iostream>
#include "AndGate.h"
#include "LogicGate.h"
#include "Circuit.h"
int main()
{

	Circuit c;

	c.addAnd("and1", 2, {true});
	c.addAnd("and2", 2,{true});
	c.addAnd("and3", 3, { "and1", "and2" });
	c.addAnd("and5", 2, { "and3" }, {true});
	c.addAnd("and4", 2);


	
	//AndGate and1("and1", 2, { true});
	//AndGate and2("and2", 2, { true, 1 });

	//auto ptr1 = std::make_shared<AndGate>(and1);
	//auto ptr2 = std::make_shared<AndGate>(and2);

	//AndGate and3("and3", 2, {ptr1});


	for (auto gate : c.gates) {
		std::cout << gate->getName();
		gate->printInputs();
		std::cout << "Output: " << gate->getOutput() << std::endl;
	}

	
}
