#include "TestKoverage/Richman/Confee/RnumberBaseCase.hpp"

#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Rnumber.hpp"
#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vnumber.hpp"

#include "TestKoverage/Richman/Confee/Mock/AnotherRule.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"


using Richman::Confee::Rule;
using Richman::Confee::Rnumber;
using Richman::Confee::Value;
using Richman::Confee::Vnumber;

using TestKoverage::Richman::Confee::Mock::AnotherRule;
using TestKoverage::Richman::Confee::Mock::AnotherValue;

using TestKoverage::Richman::Confee::RnumberBaseCase;


void RnumberBaseCase::run () {
	Rnumber rnum;

	Rule * rnum2 = rnum.copy ();
	assertTrue (rnum == *rnum2, "Rnumber essentials; copy", __FILE__, __LINE__);
	delete rnum2;

	const Rnumber & rnum22 = rnum;
	assertTrue (rnum == rnum22, "Rnumber essentials; copy", __FILE__, __LINE__);

	const Rule & rnum3 = rnum;
	assertTrue (rnum == rnum3, "Rnumber essentials; equal", __FILE__, __LINE__);

	AnotherRule anotherRule;
	assertTrue (rnum != anotherRule, "Rnumber essentials; inequal", __FILE__, __LINE__);

	AnotherValue anotherValue;
	Vnumber goodValue (5);

	assertFalse (rnum.isValid (anotherValue), "Rnumber essentials; isValid", __FILE__, __LINE__);
	assertTrue (rnum.isValid (goodValue), "Rnumber essentials; isValid", __FILE__, __LINE__);

	Rnumber rnum4;
	rnum4.setMinLimit (1);
	rnum4.setMaxLimit (2);

	Rnumber * rnum5 = rnum4.copy ();

	Vnumber zero (0);
	Vnumber one (1);
	Value * two = new Vnumber (2);
	Vnumber three (3);

	assertFalse (rnum5->isValid (zero), "Rnumber essentials; isValid", __FILE__, __LINE__);
	assertFalse (rnum5->isValid (three), "Rnumber essentials; isValid", __FILE__, __LINE__);
	assertTrue (rnum5->isValid (*two), "Rnumber essentials; isValid", __FILE__, __LINE__);

	delete rnum5;
	delete two;
}
