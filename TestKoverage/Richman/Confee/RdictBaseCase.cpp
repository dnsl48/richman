#include "TestKoverage/Richman/Confee/RdictBaseCase.hpp"


#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Rdict.hpp"
#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vdict.hpp"

#include "Richman/Exception/NotFoundException.hpp"

#include "Richman/Text/String.hpp"

#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherRule.hpp"
#include "TestKoverage/Richman/Confee/Mock/SameRule.hpp"
#include "TestKoverage/Richman/Confee/Mock/SameValue.hpp"


using Richman::Confee::Rule;
using Richman::Confee::Rdict;
using Richman::Confee::Value;
using Richman::Confee::Vdict;

using Richman::Exception::NotFoundException;

using TestKoverage::Richman::Confee::Mock::AnotherRule;
using TestKoverage::Richman::Confee::Mock::AnotherValue;
using TestKoverage::Richman::Confee::Mock::SameRule;
using TestKoverage::Richman::Confee::Mock::SameValue;

using TestKoverage::Richman::Confee::RdictBaseCase;


void RdictBaseCase::run () {
	Rdict rule1;

	SameRule * sr1 = new SameRule ();

	/* Force to delete old rules */
	rule1.setRule ("key1", sr1);
	assertFalse (rule1.isRequiredRule ("key1"), "Rdict essentials; isRequiredRule", __FILE__, __LINE__);

	rule1.setRule ("key1", sr1, true);
	assertTrue (rule1.isRequiredRule ("key1"), "Rdict essentials; isRequiredRule", __FILE__, __LINE__);
	assertFalse (rule1.isRequiredRule ("key2"), "Rdict essentials; isRequiredRule", __FILE__, __LINE__);

	rule1.setRule ("key1", new SameRule ());

	Rule * rule2 = &rule1;
	assertTrue (rule1 == *rule2, "Rdict essentials; equal", __FILE__, __LINE__);
	assertEqual (rule1, rule1, "Rdict essentials; equal", __FILE__, __LINE__);

	Rule * dict1 = rule1.copy ();
	assertTrue (rule1 == *dict1, "Rdict essentials; copy", __FILE__, __LINE__);
	delete dict1;

	AnotherRule mock;
	assertTrue (rule1 != mock, "Rdict essentials; inequal", __FILE__, __LINE__);

	assertTrue (rule1.getRule ("key1") == SameRule (), "Rdict essentials; getRule", __FILE__, __LINE__);

	try {
		rule1.getRule ("key2");
		assertTrue (false, "Rdict essentials; hasRule has returned unexistent value", __FILE__, __LINE__);
	} catch (NotFoundException & exception) {
		assertTrue (exception.getMessage () == "key2", "Rdict essentials; catch not found", __FILE__, __LINE__);
	}

	Rdict rule3;
	rule3.setRule ("key1", new SameRule ());
	rule3.setRule ("key2", new AnotherRule ());
	assertFalse (rule1 == rule3, "Rdict essentials; equal", __FILE__, __LINE__);

	rule1.setRule ("key2", new AnotherRule ());
	assertFalse (rule1 == rule3, "Rdict essentials; equal", __FILE__, __LINE__);

	assertTrue (rule1.hasRule ("key1"), "Rdict essentials; hasRule", __FILE__, __LINE__);
	assertFalse (rule1.hasRule ("key3"), "Rdict essentials; hasRule", __FILE__, __LINE__);

	assertEqual (rule1.getRule ("key1"), rule3.getRule ("key1"), "Rdict essentials; getRule", __FILE__, __LINE__);

	Rdict rule4;
	rule4.setRule ("key1", new SameRule ());
	rule4.setRule ("key2", new SameRule ());
	rule4.setRule ("key3", new SameRule ());

	Rdict rule5;
	rule4.forEachRule ([&rule5] (const ::Richman::Text::String & key, const ::Richman::Confee::Rule & val, bool isRequired) -> bool {
		rule5.setRule (key, val.copy ());
		return true;
	});
	assertEqual (rule4, rule5, "Rdict essentials; forEachRule", __FILE__, __LINE__);

	Rdict rule6;
	rule4.forEachRule ([&rule6] (const ::Richman::Text::String & key, const ::Richman::Confee::Rule & val, bool isRequired) -> bool {
		if (key == "key3")
			return false;

		rule6.setRule (key, val.copy ());
		return true;
	});
	assertTrue (rule4 != rule6, "Rdict essentials; forEachRule", __FILE__, __LINE__);

	rule6.setRule ("key3", new SameRule ());
	assertTrue (rule4 == rule6, "Rdict essentials; forEachRule", __FILE__, __LINE__);


	AnotherValue anotherValue;
	assertFalse (rule1.isValid (anotherValue), "Rdict essentials; isValid", __FILE__, __LINE__);

	Vdict vdict;
	Rdict rdict7;
	const Value & value = vdict;
	assertTrue (rdict7.isValid (value), "Rdict essentials; isValid", __FILE__, __LINE__);

	rdict7.setRule ("key1", new SameRule ());
	assertTrue (rdict7.isValid (vdict), "Rdict essentials; isValid", __FILE__, __LINE__);

	rdict7.setRule ("key1", new SameRule (), true);
	assertFalse (rdict7.isValid (vdict), "Rdict essentials; isValid", __FILE__, __LINE__);

	vdict.setValue ("key1", new SameValue ());
	assertTrue (rdict7.isValid (vdict), "Rdict essentials; isValid", __FILE__, __LINE__);

	rdict7.setRule ("key1", new AnotherRule ());
	assertFalse (rdict7.isValid (vdict), "Rdict essentials; isValid", __FILE__, __LINE__);

	rdict7.setRule ("key1", new SameRule ());
	vdict.setValue ("key1", new SameValue ());
	assertTrue (rdict7.isValid (vdict), "Rdict essentials; isValid", __FILE__, __LINE__);

	vdict.setValue ("key2", new SameValue ());
	assertFalse (rdict7.isValid (vdict), "Rdict essentials; isValid", __FILE__, __LINE__);


	Rdict rdict8;
	Rdict rdict9;

	assertTrue (rdict8 == rdict9, "Rdict essentials; equal", __FILE__, __LINE__);

	rdict8.setRule ("key1", new SameRule (), true);
	assertFalse (rdict8 == rdict9, "Rdict essentials; equal", __FILE__, __LINE__);

	rdict9.setRule ("key1", new SameRule (), false);
	assertFalse (rdict8 == rdict9, "Rdict essentials; equal", __FILE__, __LINE__);

	rdict9.setRule ("key1", new SameRule (), true);
	assertTrue (rdict8 == rdict9, "Rdict essentials; equal", __FILE__, __LINE__);

	rdict8.setRule ("key1", new AnotherRule (), true);
	assertFalse (rdict8 == rdict9, "Rdict essentials; equal", __FILE__, __LINE__);
}
