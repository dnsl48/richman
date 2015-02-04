#include "TestKoverage/Richman/Confee/VnumberBaseCase.hpp"

#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vnumber.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"
#include "TestKoverage/Richman/Confee/Mock/SameValue.hpp"


using Richman::Confee::Value;
using Richman::Confee::Vnumber;
using TestKoverage::Richman::Confee::Mock::AnotherValue;
using TestKoverage::Richman::Confee::Mock::SameValue;

using TestKoverage::Richman::Confee::VnumberBaseCase;


void VnumberBaseCase::run () {
	Vnumber vnum (5);

	assertEqual (5, vnum.getNumber (), "Vnumber essentials; getValue", __FILE__, __LINE__);

	Value * vnum2 = vnum.copy ();
	assertTrue (vnum == *vnum2, "Vnumber essentials; copy", __FILE__, __LINE__);
	delete vnum2;

	const Value & vnum3 = vnum;
	assertTrue (vnum == vnum3, "Vnumber essentials; equal", __FILE__, __LINE__);

	const Vnumber & vnum4 = vnum;
	assertTrue (vnum == vnum4, "Vnumber essentials; equal", __FILE__, __LINE__);

	AnotherValue anotherValue;
	assertTrue (vnum != anotherValue, "Vnumber essentials; inequal", __FILE__, __LINE__);
}
