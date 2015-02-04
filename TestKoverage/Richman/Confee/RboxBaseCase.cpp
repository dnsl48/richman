#include "TestKoverage/Richman/Confee/RboxBaseCase.hpp"

#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Rbox.hpp"
#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vbox.hpp"

#include "TestKoverage/Richman/Confee/Mock/AnotherRule.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"


using Richman::Confee::Rule;
using Richman::Confee::Rbox;
using Richman::Confee::Value;
using Richman::Confee::Vbox;

using TestKoverage::Richman::Confee::Mock::AnotherRule;
using TestKoverage::Richman::Confee::Mock::AnotherValue;

using TestKoverage::Richman::Confee::RboxBaseCase;


void RboxBaseCase::run () {
	Rbox<int> rbox;

	Rule * rbox2 = rbox.copy ();
	assertTrue (rbox == *rbox2, "Rbox essential; copy", __FILE__, __LINE__);
	delete rbox2;

	const Rule & rbox3 = rbox;
	assertTrue (rbox == rbox3, "Rbox essential; equal", __FILE__, __LINE__);

	AnotherRule anotherRule;
	assertTrue (rbox != anotherRule, "Rbox essential; inequal", __FILE__, __LINE__);

	AnotherValue anotherValue;
	Vbox<int> goodValue (new int (5));

	assertFalse (rbox.isValid (anotherValue), "Rbox essential; isValid", __FILE__, __LINE__);
	assertTrue (rbox.isValid (goodValue), "Rbox essential; isValid", __FILE__, __LINE__);
}
