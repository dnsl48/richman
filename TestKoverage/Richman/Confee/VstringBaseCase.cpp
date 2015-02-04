#include "TestKoverage/Richman/Confee/VstringBaseCase.hpp"

#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vstring.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"
#include "TestKoverage/Richman/Confee/Mock/SameValue.hpp"


using Richman::Confee::Value;
using Richman::Confee::Vstring;

using TestKoverage::Richman::Confee::Mock::AnotherValue;
using TestKoverage::Richman::Confee::Mock::SameValue;

using TestKoverage::Richman::Confee::VstringBaseCase;


void VstringBaseCase::run () {
	Vstring vstr ("5");

	assertTrue (vstr.getString () == "5", "Vstring essentials; getString", __FILE__, __LINE__);

	Value * vstr2 = vstr.copy ();
	assertTrue (vstr == *vstr2, "Vstring essentials; copy", __FILE__, __LINE__);
	delete vstr2;

	const Value & vstr3 = vstr;
	assertTrue (vstr == vstr3, "Vstring essentials; equal", __FILE__, __LINE__);

	const Vstring & vstr4 = vstr;
	assertTrue (vstr == vstr4, "Vstring essentials; equal", __FILE__, __LINE__);

	AnotherValue anotherValue;
	assertTrue (vstr != anotherValue, "Vstring essentials; inequal", __FILE__, __LINE__);
}
