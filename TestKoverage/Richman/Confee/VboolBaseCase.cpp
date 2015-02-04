#include "TestKoverage/Richman/Confee/VboolBaseCase.hpp"

#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vbool.hpp"

#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"


using Richman::Confee::Value;
using Richman::Confee::Vbool;

using TestKoverage::Richman::Confee::Mock::AnotherValue;
using TestKoverage::Richman::Confee::VboolBaseCase;


void VboolBaseCase::run () {
	Vbool T (Vbool::True);

	assertEqual (Vbool::True, T.getValue (), "Vbool essentials; test getValue", __FILE__, __LINE__);

	Value * T1 = T.copy ();
	assertTrue (T == *T1, "Vbool essentials; test equal", __FILE__, __LINE__);
	delete T1;

	Value * T2 = &T;
	assertTrue (T == *T2, "Vbool essentials; test equal", __FILE__, __LINE__);

	AnotherValue mock = AnotherValue ();
	assertFalse (T == mock, "Vbool essentials; test equal", __FILE__, __LINE__);

	Vbool T3 = Vbool (Vbool::False);
	const Value & val = T3;
	assertTrue (T != val, "Vbool essentials; test inequal", __FILE__, __LINE__);
}
