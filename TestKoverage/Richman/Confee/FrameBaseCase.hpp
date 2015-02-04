#ifndef TestKoverage__Richman__Confee__FrameBaseCase___hpp
#define TestKoverage__Richman__Confee__FrameBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class FrameBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		FrameBaseCase () :
			Koverager::Case ("FrameBaseCase", "Frame essentials")
		{}

		void run ();
	};

}}}

#endif
