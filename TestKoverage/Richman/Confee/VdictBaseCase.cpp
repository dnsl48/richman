#include "TestKoverage/Richman/Confee/VdictBaseCase.hpp"


#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vdict.hpp"

#include "Richman/Exception/NotFoundException.hpp"

#include "Richman/Text/String.hpp"

#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"
#include "TestKoverage/Richman/Confee/Mock/SameValue.hpp"


using Richman::Confee::Value;
using Richman::Confee::Vdict;

using Richman::Exception::NotFoundException;

using TestKoverage::Richman::Confee::Mock::AnotherValue;
using TestKoverage::Richman::Confee::Mock::SameValue;
using TestKoverage::Richman::Confee::VdictBaseCase;


void VdictBaseCase::run () {
	Vdict dict;
	dict.setValue ("key1", new AnotherValue ());
	dict.setValue ("key1", new SameValue ());

	Value * dict2 = &dict;
	assertTrue (dict == *dict2, "Vdict essential; equal", __FILE__, __LINE__);
	assertEqual (dict, dict, "Vdict essential; equal", __FILE__, __LINE__);

	Value * dict1 = dict.copy ();
	assertTrue (dict == *dict1, "Vdict essential; copy", __FILE__, __LINE__);
	delete dict1;

	AnotherValue mock;
	assertTrue (dict != mock, "Vdict essential; inequal", __FILE__, __LINE__);

	Vdict dict3;
	dict3.setValue ("key1", new SameValue ());
	dict3.setValue ("key2", new AnotherValue ());
	assertFalse (dict == dict3, "Vdict essential; equal", __FILE__, __LINE__);

	dict.setValue ("key2", new AnotherValue ());
	assertFalse (dict == dict3, "Vdict essential; equal", __FILE__, __LINE__);

	assertTrue (dict.hasValue ("key1"), "Vdict essential; hasValue", __FILE__, __LINE__);
	assertFalse (dict.hasValue ("key3"), "Vdict essential; hasValue", __FILE__, __LINE__);

	assertEqual (dict.getValue ("key1"), dict3.getValue ("key1"), "Vdict essential; getValue", __FILE__, __LINE__);

	try {
		dict.getValue ("key3");
		assertTrue (false, "Vdict essential; get unexistent value", __FILE__, __LINE__);
	} catch (NotFoundException & exception) {
		assertTrue (exception.getMessage () == "key3", "Vdict essential; catch not found", __FILE__, __LINE__);
	}

	Vdict dict4;
	dict4.setValue ("key1", new SameValue ());
	dict4.setValue ("key2", new SameValue ());
	dict4.setValue ("key3", new SameValue ());

	Vdict dict5;
	dict4.forEachValue ([&dict5] (const ::Richman::Text::String & key, const ::Richman::Confee::Value & val) -> bool {
		dict5.setValue (key, val.copy ());
		return true;
	});
	assertEqual (dict4, dict5, "Vdict essential; forEachValue", __FILE__, __LINE__);

	Vdict dict6;
	dict4.forEachValue ([&dict6] (const ::Richman::Text::String & key, const ::Richman::Confee::Value & val) -> bool {
		if (key == "key3")
			return false;

		dict6.setValue (key, val.copy ());
		return true;
	});
	assertTrue (dict4 != dict6, "Vdict essential; forEachValue", __FILE__, __LINE__);

	dict6.setValue ("key3", new SameValue ());
	assertTrue (dict4 == dict6, "Vdict essential; forEachValue", __FILE__, __LINE__);
}
