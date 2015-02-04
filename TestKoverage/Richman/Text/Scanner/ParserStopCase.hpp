#ifndef TestKoverage__Richman__Text__Scanner__ParserStopCase___hpp
#define TestKoverage__Richman__Text__Scanner__ParserStopCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class ParserStopCase : public Koverager::Case, private Koverager::Assertion {
	public:
		ParserStopCase () :
			Koverager::Case ("ParserStopCase", "Parser stop and stop skipping")
		{}

		void run ();
	};

}}}}


#endif
