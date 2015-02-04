#ifndef TestKoverage__Richman__Confee__SubjectBaseCase___hpp
#define TestKoverage__Richman__Confee__SubjectBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class SubjectBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		SubjectBaseCase () :
			Koverager::Case ("SubjectBaseCase", "Subject essentials")
		{}

		void run ();
	};

}}}

#endif
