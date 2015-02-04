#include "TestKoverage/Richman/Confee/RstringBaseCase.hpp"

#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Rstring.hpp"
#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vstring.hpp"

#include "TestKoverage/Richman/Confee/Mock/AnotherRule.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"


using Richman::Confee::Rule;
using Richman::Confee::Rstring;
using Richman::Confee::Value;
using Richman::Confee::Vstring;

using TestKoverage::Richman::Confee::Mock::AnotherRule;
using TestKoverage::Richman::Confee::Mock::AnotherValue;

using TestKoverage::Richman::Confee::RstringBaseCase;


void RstringBaseCase::run () {
	Rstring rstr;

	Rule * rstr2 = rstr.copy ();
	assertTrue (rstr == *rstr2, "Rstring essentials; copy", __FILE__, __LINE__);
	delete rstr2;

	const Rstring & rstr22 = rstr;
	assertTrue (rstr == rstr22, "Rstring essentials; copy", __FILE__, __LINE__);

	const Rule & rstr3 = rstr;
	assertTrue (rstr == rstr3, "Rstring essentials; equal", __FILE__, __LINE__);

	AnotherRule anotherRule;
	assertTrue (rstr != anotherRule, "Rstring essentials; inequal", __FILE__, __LINE__);

	AnotherValue anotherValue;
	Value * goodValue = new Vstring ("5");

	assertFalse (rstr.isValid (anotherValue), "Rstring essentials; isValid", __FILE__, __LINE__);
	assertTrue (rstr.isValid (*goodValue), "Rstring essentials; isValid", __FILE__, __LINE__);

	delete goodValue;
}
