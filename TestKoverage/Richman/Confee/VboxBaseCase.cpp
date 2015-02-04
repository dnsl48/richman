#include "TestKoverage/Richman/Confee/VboxBaseCase.hpp"

#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vbox.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"


using Richman::Confee::Value;
using Richman::Confee::Vbox;
using TestKoverage::Richman::Confee::Mock::AnotherValue;
using TestKoverage::Richman::Confee::VboxBaseCase;


void VboxBaseCase::run () {
	Vbox<int> vbox (new int (5));

	assertEqual (5, vbox.getValue (), "Vbox essentials; getValue", __FILE__, __LINE__);

	Value * vbox2 = vbox.copy ();
	assertTrue (vbox == *vbox2, "Vbox essentials; copy", __FILE__, __LINE__);
	delete vbox2;

	const Value & vbox3 = vbox;
	assertTrue (vbox == vbox3, "Vbox essentials; equal", __FILE__, __LINE__);

	AnotherValue anotherValue;
	assertTrue (vbox != anotherValue, "Vbox essentials; inequal", __FILE__, __LINE__);
}
