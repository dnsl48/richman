#include "TestKoverage/Richman/Confee/RlistBaseCase.hpp"


#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Rlist.hpp"
#include "Richman/Confee/Value.hpp"
#include "Richman/Confee/Vlist.hpp"

#include "TestKoverage/Richman/Confee/Mock/SameRule.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherRule.hpp"
#include "TestKoverage/Richman/Confee/Mock/AnotherValue.hpp"
#include "TestKoverage/Richman/Confee/Mock/SameValue.hpp"


using Richman::Confee::Rule;
using Richman::Confee::Rlist;
using Richman::Confee::Value;
using Richman::Confee::Vlist;

using TestKoverage::Richman::Confee::Mock::SameRule;
using TestKoverage::Richman::Confee::Mock::AnotherRule;
using TestKoverage::Richman::Confee::Mock::AnotherValue;
using TestKoverage::Richman::Confee::Mock::SameValue;

using TestKoverage::Richman::Confee::RlistBaseCase;


void RlistBaseCase::run () {
	Rlist rlist;

	Rule * rlist2 = rlist.copy ();
	assertTrue (rlist == *rlist2, "Rlist essentials; copy", __FILE__, __LINE__);
	delete rlist2;

	const Rule & rlist3 = rlist;
	assertTrue (rlist == rlist3, "Rlist essentials; equal", __FILE__, __LINE__);

	AnotherRule anotherRule;
	assertTrue (rlist != anotherRule, "Rlist essentials; inequal", __FILE__, __LINE__);

	AnotherValue anotherValue;
	Vlist goodValue;

	assertFalse (rlist.isValid (anotherValue), "Rlist essentials; isValid", __FILE__, __LINE__);
	assertTrue (rlist.isValid (goodValue), "Rlist essentials; isValid", __FILE__, __LINE__);


	Rlist rlist4;
	rlist4.setDefaultRule (new SameRule ());
	rlist4.setMinSize (1);
	rlist4.setMaxSize (2);

	Vlist vlist4;
	assertFalse (rlist4.isValid (vlist4), "Rlist essentials; isValid", __FILE__, __LINE__);

	vlist4.push (new SameValue ());
	assertTrue (rlist4.isValid (vlist4), "Rlist essentials; isValid", __FILE__, __LINE__);

	vlist4.push (new SameValue ());
	assertTrue (rlist4.isValid (vlist4), "Rlist essentials; isValid", __FILE__, __LINE__);

	vlist4.push (new SameValue ());
	assertFalse (rlist4.isValid (vlist4), "Rlist essentials; isValid", __FILE__, __LINE__);

	Rlist rlist5;
	rlist5.setDefaultRule (new AnotherRule ());
	Vlist vlist55;
	vlist55.push (new SameValue ());
	const Value & vlist5 = vlist55;
	assertFalse (rlist5.isValid (vlist5), "Rlist essentials; isValid", __FILE__, __LINE__);

	rlist5.setDefaultRule (new SameRule ());
	assertTrue (rlist5.isValid (vlist5), "Rlist essentials; isValid", __FILE__, __LINE__);

	rlist5.setRule (0, new AnotherRule ());
	assertFalse (rlist5.isValid (vlist5), "Rlist essentials; isValid", __FILE__, __LINE__);

	SameRule * sameRule = new SameRule ();
	rlist5.setRule (0, sameRule);
	rlist5.setRule (0, sameRule);
	assertTrue (rlist5.isValid (vlist5), "Rlist essentials; isValid", __FILE__, __LINE__);


	Rlist rlist6;
	rlist6.setMinSize (1);
	rlist6.setMaxSize (3);
	rlist6.setDefaultRule (new SameRule ());

	const Rlist & rlist8 = rlist6;
	assertTrue (rlist6 == rlist8, "Rlist essentials; equal", __FILE__, __LINE__);

	Rlist rlist9;
	assertFalse (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	rlist9.setMinSize (2);
	assertFalse (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	rlist9.setMinSize (1);
	assertFalse (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	rlist9.setMaxSize (1);
	assertFalse (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	rlist9.setMaxSize (3);
	assertFalse (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	rlist6.setDefaultRule (new AnotherRule ());
	rlist9.setDefaultRule (new AnotherRule ());
	assertFalse (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	rlist6.setDefaultRule (new SameRule ());
	rlist9.setDefaultRule (new SameRule ());
	assertTrue (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	rlist6.setRule (0, new SameRule ());
	rlist6.setRule (1, new AnotherRule ());
	assertFalse (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	rlist9.setRule (0, new SameRule ());
	rlist9.setRule (1, new SameRule ());
	assertFalse (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	rlist6.setRule (1, new SameRule ());
	assertTrue (rlist6 == rlist9, "Rlist essentials; equal", __FILE__, __LINE__);

	Rlist * rlist7 = rlist6.copy ();
	assertTrue (rlist6 == *rlist7, "Rlist essentials; equal", __FILE__, __LINE__);
	delete rlist7;

	int cntr = 0;
	rlist6.forEachRule ([&cntr] (const ::Richman::Confee::Rule & val) -> bool {
		if (cntr++ > 0)
			return false;
		return true;
	});
}
