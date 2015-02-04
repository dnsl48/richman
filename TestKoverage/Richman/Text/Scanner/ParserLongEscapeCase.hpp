#ifndef TestKoverage__Richman__Text__Scanner__ParserLongEscapeCase___hpp
#define TestKoverage__Richman__Text__Scanner__ParserLongEscapeCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class ParserLongEscapeCase : public Koverager::Case, private Koverager::Assertion {
	public:
		ParserLongEscapeCase () :
			Koverager::Case ("ParserLongEscapeCase", "Parser long escape working check")
		{}

		void run ();
	};

}}}}


#endif
