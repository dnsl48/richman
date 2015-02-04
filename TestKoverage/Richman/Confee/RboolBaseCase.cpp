#include "TestKoverage/Richman/Confee/RboolBaseCase.hpp"

#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Rbool.hpp"
#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vbool.hpp"

#include "TestKoverage/Richman/Confee/Mock/AnotherRule.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"


using Richman::Confee::Rule;
using Richman::Confee::Rbool;
using Richman::Confee::Value;
using Richman::Confee::Vbool;
using TestKoverage::Richman::Confee::Mock::AnotherRule;
using TestKoverage::Richman::Confee::Mock::AnotherValue;
using TestKoverage::Richman::Confee::RboolBaseCase;



void RboolBaseCase::run () {
	Rbool tfnRule1;

	Rbool * tfnRule2 = tfnRule1.copy ();
	assertEqual (tfnRule1, *tfnRule2, "Rbool essential; test equal", __FILE__, __LINE__);
	delete tfnRule2;

	const Rule & tfnRule3 = tfnRule1;
	assertTrue (tfnRule1 == tfnRule3, "Rbool essential; test equal", __FILE__, __LINE__);

	Rule * tfnRule4 = tfnRule1.copy ();
	assertTrue (tfnRule1 == *tfnRule4, "Rbool essential; test equal", __FILE__, __LINE__);
	delete tfnRule4;

	AnotherRule anotherRule;
	assertFalse (tfnRule1 == anotherRule, "Rbool essential; test equal", __FILE__, __LINE__);
	assertTrue (tfnRule1 != anotherRule, "Rbool essential; test equal", __FILE__, __LINE__);

	AnotherValue anotherValue;
	assertFalse (tfnRule1.isValid (anotherValue), "Rbool essential; test isValid", __FILE__, __LINE__);


	Value * trueValue = new Vbool (Vbool::True);
	assertTrue (tfnRule1.isValid (*trueValue), "Rbool essential; test isValid", __FILE__, __LINE__);
	delete trueValue;
}
