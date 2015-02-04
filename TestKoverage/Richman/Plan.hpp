#ifndef TestKoverage__Richman__Plan___hpp
#define TestKoverage__Richman__Plan___hpp


#include "Koverager/Plan.hpp"

#include "TestKoverage/Richman/Confee/Suite.hpp"
#include "TestKoverage/Richman/Exception/Suite.hpp"
#include "TestKoverage/Richman/Text/Suite.hpp"
#include "TestKoverage/Richman/Text/Scanner/Suite.hpp"


namespace TestKoverage {
namespace Richman {

	class Plan : public Koverager::Plan {
	public:
		Plan () : Koverager::Plan ("Richman test plan") {
			addSuite (new Text::Suite ());
			addSuite (new Exception::Suite ());
			addSuite (new Confee::Suite ());
			addSuite (new Text::Scanner::Suite ());
		}
	};

}}

#endif
