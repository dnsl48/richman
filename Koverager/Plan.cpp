#include "Koverager/Plan.hpp"

#include "Koverager/AssertError.hpp"

#include <iostream>


using Koverager::AssertError;
using Koverager::Plan;


Plan::~Plan () {
	for (Suite * suite : _plan) {
		delete suite;
	}
}


void Plan::addSuite (Suite * suite) {
	_plan.push_back (suite);
}



void Plan::run () {
	for (Suite * suite : _plan) {
		suite->run ();

		if (suite->hasErrors ()) {
			std::cout << suite->getName () << " got " << suite->errorsCount () << " error" << (suite->errorsCount () > 1 ? "s" : "") << "\n\n";

			suite->forEachError ([](AssertError & error) {
				std::cout << error.getAssertFile () << ":" << error.getAssertLine () << "\n"
					<< error.getCaseName () << " [" << error.getCaseDescription () << "]: " << error.getAssertMessage ();

				if (error.getFormerExpectation ().getLength ()) {
					if (error.getLatterExpectation ().getLength ()) {
						std::cout << "\nExpects " << error.getFormerExpectation () << ", got " << error.getLatterExpectation ();
					} else {
						std::cout << "\nExpects " << error.getFormerExpectation ();
					}
				}

				std::cout << "\n\n";

				return true;
			});

			std::cout << "\n";
		}
	}
}
