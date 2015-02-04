#include "Koverager/AssertException.hpp"
#include "Koverager/Suite.hpp"


using Koverager::AssertError;
using Koverager::AssertException;
using Koverager::Suite;


Suite::Suite (Richman::Text::String && name) : _name(name) {}


Suite::~Suite () {
	for (Case * _case : _cases)
		delete _case;

	for (AssertError * error : _errors)
		delete error;
}


void Suite::addCase (Case * _case) {
	_cases.push_back (_case);
}


void Suite::run () {
	for (Case * _case : _cases) {
		try {
			_case->run ();
		} catch (AssertException & error) {
			_errors.push_back (new AssertError (error.getFormerExpectation (), error.getLatterExpectation (), _case->getName (), _case->getDescription (), error.getMessage (), error.getFile (), error.getLine ()));
		}
	}
}


bool Suite::hasErrors () const {
	return !_errors.empty ();
}


std::size_t Suite::errorsCount () const {
	return _errors.size ();
}


void Suite::forEachError (bool (*callback)(AssertError &)) const {
	for (AssertError * error : _errors) {
		if (!callback (*error))
			break;
	}
}
