#ifndef Koverager__Suite___hpp
#define Koverager__Suite___hpp


#include "Koverager/AssertError.hpp"
#include "Koverager/Case.hpp"

#include "Richman/Text/String.hpp"

#include <list>


namespace Koverager {


	/* Test suite represents a bunch of test cases. Also it holds a list of errors occured while a test run. */
	class Suite {
	private:
		Richman::Text::String _name;
		std::list<Case *> _cases;
		std::list<AssertError *> _errors;

	public:
		/* Initializes the suite by a name */
		Suite (Richman::Text::String && name);


		/* Virtual descructor destroys all cases and errors */
		virtual ~Suite ();


		/* Getter for the suite's name
		 *
		 * @return The name of the suite
		 */
		const Richman::Text::String & getName () const {return _name;}


		/* Adds a new test case to a suite */
		void addCase (Case *);


		/* Runs all test cases */
		void run ();


		/* Returns true if some of the cases made assertion errors
		 *
		 * @return Whether some of the cases made assertion errors
		 */
		bool hasErrors () const;


		/* Returns the amount of the assertion errors
		 *
		 * @return The amount of the assertion errors
		 */
		std::size_t errorsCount () const;


		/* Applies the closure to each assertion error
		 * @callback Closure that might do something with the passed <AssertError>
		 */
		void forEachError (bool (*callback)(AssertError &)) const;
	};

}

#endif
