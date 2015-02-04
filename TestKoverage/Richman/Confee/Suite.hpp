#ifndef TestKoverage__Richman__Confee__Suite___hpp
#define TestKoverage__Richman__Confee__Suite___hpp


#include "Koverager/Suite.hpp"
#include "TestKoverage/Richman/Confee/RboolBaseCase.hpp"
#include "TestKoverage/Richman/Confee/RboxBaseCase.hpp"
#include "TestKoverage/Richman/Confee/RdictBaseCase.hpp"
#include "TestKoverage/Richman/Confee/RlistBaseCase.hpp"
#include "TestKoverage/Richman/Confee/RnumberBaseCase.hpp"
#include "TestKoverage/Richman/Confee/RstringBaseCase.hpp"
#include "TestKoverage/Richman/Confee/VboolBaseCase.hpp"
#include "TestKoverage/Richman/Confee/VboxBaseCase.hpp"
#include "TestKoverage/Richman/Confee/VdictBaseCase.hpp"
#include "TestKoverage/Richman/Confee/VlistBaseCase.hpp"
#include "TestKoverage/Richman/Confee/VnumberBaseCase.hpp"
#include "TestKoverage/Richman/Confee/VstringBaseCase.hpp"

#include "TestKoverage/Richman/Confee/SubjectBaseCase.hpp"
#include "TestKoverage/Richman/Confee/NodeBaseCase.hpp"
#include "TestKoverage/Richman/Confee/FrameBaseCase.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class Suite : public Koverager::Suite {
	public:
		Suite () : Koverager::Suite ("Confee suite"){ 
			addCase (new VboolBaseCase ());
			addCase (new RboolBaseCase ());
			addCase (new VboxBaseCase ());
			addCase (new RboxBaseCase ());
			addCase (new VdictBaseCase ());
			addCase (new RdictBaseCase ());
			addCase (new VlistBaseCase ());
			addCase (new RlistBaseCase ());
			addCase (new VnumberBaseCase ());
			addCase (new RnumberBaseCase ());
			addCase (new VstringBaseCase ());
			addCase (new RstringBaseCase ());

			addCase (new SubjectBaseCase ());
			addCase (new NodeBaseCase ());
			addCase (new FrameBaseCase ());
		}
	};

}}}

#endif
