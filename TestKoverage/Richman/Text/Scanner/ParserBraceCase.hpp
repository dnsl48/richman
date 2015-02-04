#ifndef TestKoverage__Richman__Text__Scanner__ParserBraceCase___hpp
#define TestKoverage__Richman__Text__Scanner__ParserBraceCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class ParserBraceCase : public Koverager::Case, private Koverager::Assertion {
	public:
		ParserBraceCase () :
			Koverager::Case ("ParserBraceCase", "Parser braces working check")
		{}

		void run ();
	};

}}}}


#endif
