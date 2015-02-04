#ifndef Koverager__Plan___hpp
#define Koverager__Plan___hpp


#include "Koverager/Suite.hpp"

#include "Richman/Text/String.hpp"

#include <list>


namespace Koverager {


	/* Represents a test plan that contains a number of test suites and is the highest point for tests running */
	class Plan {
	private:
		Richman::Text::String _name;
		std::list<Suite *> _plan;

	public:
		/* Constructs the plan and gives a name to it
		 * @name The name of the test plan
		 */
		Plan (Richman::Text::String && name) : _name(name) {}


		/* Virtual descructor that destroys all the suites after the testing */
		virtual ~Plan ();


		/* Adds a suite to the plan
		 * @suite <Suite> that should be run as a part of the test plan
		 */
		void addSuite (Suite * suite);


		/* Runs all suites of the plan */
		void run ();
	};

}

#endif
