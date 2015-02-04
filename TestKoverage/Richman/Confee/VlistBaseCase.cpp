#include "TestKoverage/Richman/Confee/VlistBaseCase.hpp"

#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vlist.hpp"

#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"
#include "TestKoverage/Richman/Confee/Mock/SameValue.hpp"


using Richman::Confee::Value;
using Richman::Confee::Vlist;

using TestKoverage::Richman::Confee::Mock::AnotherValue;
using TestKoverage::Richman::Confee::Mock::SameValue;

using TestKoverage::Richman::Confee::VlistBaseCase;


void VlistBaseCase::run () {
	Vlist val1;
	const Value & cval = val1;

	assertTrue (cval == val1, "Vlits essentials; equal", __FILE__, __LINE__);

	Vlist * val2 = val1.copy ();
	assertTrue (val1 == *val2, "Vlist essentials; equal", __FILE__, __LINE__);
	

	val1.push (new SameValue ());
	assertEqual (1, val1.length (), "Vlist essentials; length", __FILE__, __LINE__);

	Vlist * val3 = val1.copy ();
	assertTrue (val1 == *val3, "Vlist essentials; equal", __FILE__, __LINE__);
	assertTrue (*val2 != *val3, "Vlist essentials; equal", __FILE__, __LINE__);

	delete val2;
	delete val3;


	Value * val4 = new AnotherValue ();
	assertTrue (val1 != *val4, "Vlist essentials; equal", __FILE__, __LINE__);
	delete val4;

	const Vlist & val5 = val1;
	assertTrue (val1 == val5, "Vlist essentials; equal", __FILE__, __LINE__);

	Vlist val6;
	Vlist val7;

	val6.push (new AnotherValue ());
	val7.push (new AnotherValue ());

	assertTrue (val6 != val7, "Vlist essentials; equal", __FILE__, __LINE__);
}
