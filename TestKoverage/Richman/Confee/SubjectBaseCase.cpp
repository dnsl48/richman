#include "TestKoverage/Richman/Confee/SubjectBaseCase.hpp"


#include "Richman/Confee/Exception/MergeSubjectsException.hpp"

#include "Richman/Confee/Rbool.hpp"
#include "Richman/Confee/Subject.hpp"
#include "Richman/Confee/Vbool.hpp"

#include "Richman/Exception/NotFoundException.hpp"
#include "Richman/Exception/UninitializedException.hpp"


using Richman::Confee::Exception::MergeSubjectsException;

using Richman::Confee::Rbool;
using Richman::Confee::Subject;
using Richman::Confee::Vbool;

using Richman::Exception::NotFoundException;
using Richman::Exception::UninitializedException;

using TestKoverage::Richman::Confee::SubjectBaseCase;


void SubjectBaseCase::run () {
	Subject subj ("simple bool", new Rbool ());

	assertTrue (subj.getId () == "simple bool", "Subject essentials; getId", __FILE__, __LINE__);
	assertFalse (subj.isRequired (), "Subject essentials; isRequired", __FILE__, __LINE__);

	Rbool rbool;
	assertTrue (subj.getRule () == rbool, "Subject essentials; getRule", __FILE__, __LINE__);

	assertEqual (0, subj.getAttributesCount (), "Subject essentials; getAttributesCount", __FILE__, __LINE__);
	assertFalse (subj.hasAttribute ("attr1"), "Subject essentials; getAttribute", __FILE__, __LINE__);

	try {
		subj.getAttribute ("attr1");
		assertTrue (false, "Subject essentials; getAttribute has returned something horrible...", __FILE__, __LINE__);
	} catch (NotFoundException & exception) {
		assertTrue (exception.getMessage () == "attr1", "Subject essentials; getAttribute threw exception", __FILE__, __LINE__);
	}

	Subject * attr11 = new Subject ("attr1", new Rbool ());
	subj.setAttribute (attr11);
	subj.setAttribute (attr11);

	Subject * attr1 = new Subject ("attr1", new Rbool ());
	subj.setAttribute (attr1);

	assertTrue (&subj.getAttribute ("attr1") == attr1, "Subject essentials; getAttribute", __FILE__, __LINE__);

	Subject * attr2 = new Subject ("attr2", new Rbool ());
	subj.setAttribute (attr2);

	int cntr = 0;
	subj.forEachAttribute ([attr1, attr2, &cntr] (const Subject & attr) -> bool {
		if (cntr++ == 0) {
			assertTrue (attr1 == &attr, "Subject essentials; forEachAttribute", __FILE__, __LINE__);
			return true;
		} else {
			assertTrue (attr2 == &attr, "Subject essentials; forEachAttribute", __FILE__, __LINE__);
			return false;
		}
	});

	assertFalse (subj.hasValue (), "Subject essentials; hasValue", __FILE__, __LINE__);
	assertFalse (subj.hasDefaultValue (), "Subject essentials; hasDefaultValue", __FILE__, __LINE__);

	try {
		subj.getValue ();
		assertTrue (false, "Subject essentials; getValue has returned something horrible...", __FILE__, __LINE__);
	} catch (UninitializedException & exception) {
		assertTrue (exception.getMessage () == "Value hasn't been initialized yet", "Subject essentials; getValue threw exception", __FILE__, __LINE__);
	}

	Vbool * vbool1 = new Vbool (Vbool::True);
	subj.setValue (vbool1);
	subj.setValue (vbool1);

	assertTrue (vbool1 == &subj.getValue (), "Subject essentials; getValue", __FILE__, __LINE__);

	try {
		subj.getDefaultValue ();
		assertTrue (false, "Subject essentials; getDefaultValue has returned something horrible...", __FILE__, __LINE__);
	} catch (UninitializedException & exception) {
		assertTrue (exception.getMessage () == "Default value hasn't been initialized yet", "Subject essentials; getValue threw exception", __FILE__, __LINE__);
	}

	Vbool * vbool2 = new Vbool (Vbool::False);
	subj.setDefaultValue (vbool2);
	subj.setDefaultValue (vbool2);

	assertTrue (vbool2 == &subj.getDefaultValue (), "Subject essentials; getDefaultValue", __FILE__, __LINE__);

	Subject * subj2 = subj.copy ();
	assertFalse (subj != *subj2, "Subject essentials; copy & inequal", __FILE__, __LINE__);
	delete subj2;

	assertTrue (subj == subj, "Subject essentials; equal", __FILE__, __LINE__);

	Subject subj3 ("subject", new Rbool ());
	Subject subj4 ("subj", new Rbool ());
	Subject subj5 ("subject", new Rbool ());
	assertFalse (subj3 == subj4, "Subject essentials; equal", __FILE__, __LINE__);

	subj3.setAttribute (new Subject ("sub-subject", new Rbool ()));
	assertFalse (subj3 == subj5, "Subject essentials; equal", __FILE__, __LINE__);

	subj5.setAttribute (new Subject ("sub-subject", new Rbool ()));
	subj3.setValue (new Vbool (Vbool::True));
	assertFalse (subj3 == subj5, "Subject essentials; equal", __FILE__, __LINE__);

	subj5.setValue (new Vbool (Vbool::False));
	assertFalse (subj3 == subj5, "Subject essentials; equal", __FILE__, __LINE__);

	Subject subj6 ("subject", new Rbool (Vbool::False | Vbool::True));
	subj6.setAttribute (new Subject ("sub-subject", new Rbool ()));
	subj6.setValue (new Vbool (Vbool::True));
	assertFalse (subj3 == subj6, "Subject essentials; equal", __FILE__, __LINE__);

	Subject subj7 ("subject", new Rbool ());
	subj7.setAttribute (new Subject ("sub-subject", new Rbool (Vbool::True)));
	subj7.setValue (new Vbool (Vbool::True));
	assertFalse (subj3 == subj7, "Subject essentials; equal", __FILE__, __LINE__);

	subj7.setAttribute (new Subject ("sub-subject", new Rbool ()));
	assertTrue (subj3 == subj7, "Subject essentials; equal", __FILE__, __LINE__);


	Subject subj8 ("subject for merging", new Rbool ());

	Subject * merged1 = subj8.merge (subj8);
	delete merged1;

	Subject subj9 ("subject for merge exception", new Rbool ());

	try {
		delete subj8.merge (subj9);
		assertTrue (false, "Subject essentials; merge", __FILE__, __LINE__);
	} catch (MergeSubjectsException & exception) {
		assertTrue (exception.getFormer () == subj8, "Subject essentials; merge", __FILE__, __LINE__);
		assertTrue (exception.getLatter () == subj9, "Subject essentials; merge", __FILE__, __LINE__);
	}

	Subject subj10  ("subject for merging", new Rbool (Vbool::True));

	try {
		delete subj8.merge (subj10);
		assertTrue (false, "Subject essentials; merge", __FILE__, __LINE__);
	} catch (MergeSubjectsException & exception) {
		assertTrue (exception.getFormer () == subj8, "Subject essentials; merge", __FILE__, __LINE__);
		assertTrue (exception.getLatter () == subj10, "Subject essentials; merge", __FILE__, __LINE__);
	}

	subj8.setDefaultValue (new Vbool (Vbool::False));
	Subject subj11  ("subject for merging", new Rbool ());
	subj11.setDefaultValue (new Vbool (Vbool::True));

	try {
		delete subj8.merge (subj11);
		assertTrue (false, "Subject essentials; merge", __FILE__, __LINE__);
	} catch (MergeSubjectsException & exception) {
		assertTrue (exception.getFormer () == subj8, "Subject essentials; merge", __FILE__, __LINE__);
		assertTrue (exception.getLatter () == subj11, "Subject essentials; merge", __FILE__, __LINE__);
	}


	subj8.setValue (new Vbool (Vbool::True));
	Subject subj12  ("subject for merging", new Rbool ());
	subj12.setDefaultValue (new Vbool (Vbool::False));
	subj12.setValue (new Vbool (Vbool::False));

	try {
		delete subj8.merge (subj12);
		assertTrue (false, "Subject essentials; merge", __FILE__, __LINE__);
	} catch (MergeSubjectsException & exception) {
		assertTrue (exception.getFormer () == subj8, "Subject essentials; merge", __FILE__, __LINE__);
		assertTrue (exception.getLatter () == subj12, "Subject essentials; merge", __FILE__, __LINE__);
	}


	Subject subj13  ("subject for merging", new Rbool ());

	Subject * subj14 = subj8.merge (subj13);
	assertTrue (*subj14 == subj8, "Subject essentials; merge", __FILE__, __LINE__);
	assertFalse (*subj14 == subj13, "Subject essentials; merge", __FILE__, __LINE__);
	delete subj14;

	Subject subj15 ("subject for merging", new Rbool ());
	subj15.setValue (new Vbool (Vbool::True));

	Subject * subj16 = subj13.merge (subj15);
	assertTrue (*subj16 == subj15, "Subject essentials; merge", __FILE__, __LINE__);
	assertFalse (*subj16 == subj13, "Subject essentials; merge", __FILE__, __LINE__);
	delete subj16;


	Subject subj17 ("subject", new Rbool ());
	Subject subj18 ("subject", new Rbool ());

	subj17.setAttribute (new Subject ("sub1", new Rbool ()));

	Subject * merged2 = subj17.merge (subj18);
	assertTrue (subj17 == *merged2, "Subject essentials; merge", __FILE__, __LINE__);
	assertFalse (subj18 == *merged2, "Subject essentials; merge", __FILE__, __LINE__);
	delete merged2;

	subj18.setAttribute (new Subject ("sub1", new Rbool ()));

	Subject * merged3 = subj17.merge (subj18);
	assertTrue (subj17 == *merged3, "Subject essentials; merge", __FILE__, __LINE__);
	assertTrue (subj18 == *merged3, "Subject essentials; merge", __FILE__, __LINE__);
	delete merged3;


	Subject subj19 ("subject", new Rbool ());
	Subject subj20 ("subject", new Rbool ());

	subj20.setAttribute (new Subject ("sub1", new Rbool ()));

	Subject * merged4 = subj19.merge (subj20);
	assertFalse (subj19 == *merged4, "Subject essentials; merge", __FILE__, __LINE__);
	assertTrue (subj20 == *merged4, "Subject essentials; merge", __FILE__, __LINE__);
	delete merged4;


	Subject subj21 ("subject", new Rbool ());
	Subject subj22 ("subject", new Rbool ());

	subj22.setDefaultValue (new Vbool (Vbool::True));

	Subject * merged5 = subj21.merge (subj22);
	assertTrue (subj21 == *merged5, "Subject essentials; merge", __FILE__, __LINE__);
	assertTrue (subj22 == *merged5, "Subject essentials; merge", __FILE__, __LINE__);
	delete merged5;
}
