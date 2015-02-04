#include "TestKoverage/Richman/Text/StringBaseCase.hpp"

#include "Richman/Text/String.hpp"

#include <cstring>
#include <sstream>


using TestKoverage::Richman::Text::StringBaseCase;

using Richman::Text::String;


void StringBaseCase::run () {
	String s1 ("test");
	assertEqual (std::strlen ("test")+1, s1.getLength (), "String base; check a length", __FILE__, __LINE__);

	String s2 = String ();
	assertEqual (0, s2.getLength (), "String base; check a zero length", __FILE__, __LINE__);

	String s3 ("test", std::strlen ("test")+1, false);
	assertEqual (std::strlen ("test")+1, s3.getLength (), "String base; check a constructed length", __FILE__, __LINE__);

	char * testString = new char[5];
	testString[0] = 't';
	testString[1] = 'e';
	testString[2] = 's';
	testString[3] = 't';
	testString[4] = '\0';
	String s4 (testString, 5, true);
	assertEqual (5, s4.getLength (), "String base; check a constructed length", __FILE__, __LINE__);


	char testString2[3];
	testString2[0] = 't';
	testString2[1] = 'e';
	testString2[2] = '\0';

	char testString3[3];
	testString3[0] = 'e';
	testString3[1] = 't';
	testString3[2] = '\0';

	char testString4[3];
	testString4[0] = 'e';
	testString4[1] = 't';
	testString4[2] = '\0';

	assertTrue (String (testString2) == String (testString2), "String base; check equal operator by ptrs", __FILE__, __LINE__);
	assertFalse (String (testString2, 3u) == String (testString2, 2u), "String base; check equal operator by ptrs", __FILE__, __LINE__);
	assertTrue (String (testString3, 3u) == String (testString4, 3u), "String base; check equal operator by diff ptrs", __FILE__, __LINE__);
	assertFalse (String (testString3, 3u) == String (testString2, 3u), "String base; check equal operator false by diff ptrs", __FILE__, __LINE__);
	assertFalse (String (testString3, 3u) == String (testString2, 2u), "String base; check equal operator false by diff ptrs with diff length", __FILE__, __LINE__);

	assertFalse (String (testString2) != String (testString2), "String base; check inequal operator by ptrs", __FILE__, __LINE__);
	assertTrue (String (testString2, 3u) != String (testString2, 2u), "String base; check inequal operator by ptrs", __FILE__, __LINE__);
	assertFalse (String (testString3, 3u) != String (testString4, 3u), "String base; check inequal operator by diff ptrs", __FILE__, __LINE__);
	assertTrue (String (testString3, 3u) != String (testString2, 3u), "String base; check inequal operator true by diff ptrs", __FILE__, __LINE__);
	assertTrue (String (testString3, 3u) != String (testString2, 2u), "String base; check inequal operator true by diff ptrs with diff length", __FILE__, __LINE__);

	std::stringstream buf;
	buf << String ();
	buf << String ("test");
	char buf1[5];
	buf >> buf1;
	assertEqualAlong ("test", buf1, "String base; check ostream", __FILE__, __LINE__);

	String s5 (nullptr);
	assertTrue (s5.getLength () == 0, "String base; check zero length of null-string", __FILE__, __LINE__);


	char comp0[2];
	comp0[0] = '1';
	comp0[1] = '\0';

	char comp1[2];
	comp1[0] = '1';
	comp1[1] = '\0';

	char comp2[2];
	comp2[0] = '2';
	comp2[1] = '\0';

	assertFalse (String (comp0) < String (comp0), "String base; check comparison operator by one ptr strings", __FILE__, __LINE__);
	assertFalse (String (comp0) < String (comp1), "String base; check comparison operator by diff ptrs and same strings", __FILE__, __LINE__);
	assertTrue (String (comp0) < String (comp2), "String base; check comparison operator by diff ptrs and diff strings", __FILE__, __LINE__);
}
