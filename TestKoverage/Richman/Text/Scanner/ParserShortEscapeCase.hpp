#ifndef TestKoverage__Richman__Text__Scanner__ParserShortEscapeCase___hpp
#define TestKoverage__Richman__Text__Scanner__ParserShortEscapeCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class ParserShortEscapeCase : public Koverager::Case, private Koverager::Assertion {
	public:
		ParserShortEscapeCase () :
			Koverager::Case ("ParserShortEscapeCase", "Parser short escape working check")
		{}

		void run ();
	};

}}}}


#endif
