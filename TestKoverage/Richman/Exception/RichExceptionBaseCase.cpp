#include "TestKoverage/Richman/Exception/RichExceptionBaseCase.hpp"

#include "Richman/Text/String.hpp"
#include "Richman/Exception/RichException.hpp"


using TestKoverage::Richman::Exception::RichExceptionBaseCase;

using Richman::Text::String;
using Richman::Exception::RichException;


void RichExceptionBaseCase::run () {
	RichException e1 ("TestMessage1", __FILE__, 20);

	assertTrue (e1.getMessage () == "TestMessage1", "RichException base case; check getMessage", __FILE__, __LINE__);
	assertTrue (e1.getFile () == __FILE__, "RichException base case; check getFile", __FILE__, __LINE__);
	assertTrue (e1.getLine () == 20, "RichException base case; check getLine", __FILE__, __LINE__);


	const String fname (__FILE__);
	const String message ("TestMessage2");

	RichException e2 (message, fname, 50);
	assertTrue (e2.getMessage () == "TestMessage2", "RichException base case; check getMessage", __FILE__, __LINE__);
	assertTrue (e2.getFile () == __FILE__, "RichException base case; check getFile", __FILE__, __LINE__);
	assertTrue (e2.getLine () == 50, "RichException base case; check getLine", __FILE__, __LINE__);
}
