#ifndef Koverager__Assertion___hpp
#define Koverager__Assertion___hpp


#include "Koverager/AssertException.hpp"

#include "Richman/Text/String.hpp"

#include <cstring>


namespace Koverager {


	/* Mix-in class that contains methods and some test data for making assertions */
	class Assertion {
	public:
		/* Returns the fish message
		 *
		 * @return Lorem ipsum dolor sit amet...
		 */
		static constexpr const char * getLorem () {
			return "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
				"Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. "
				"Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
				"Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
		}


		/* Returns the length of the fish message
		 *
		 * @return strlen + 1 (because of \0)
		 */
		static std::size_t getLoremLength () {
			return std::strlen (getLorem ()) + 1;
		}


		/* Makes an equation assertion about two values
		 * @former Former value for making an evaluation
		 * @latter Latter value for making an evaluation
		 * @message Message describing the assertion
		 * @file The name of a file where the assertion is
		 * @line The number of a line where the assertion is
		 *
		 * @return nothing
		 */
		template <typename T>
		static void assertEqual (const T & former, const T & latter, Richman::Text::String && message, Richman::Text::String && file, unsigned int line) {
			bool result = former == latter;

			if (!result)
				throw AssertException (message, file, line);
		}


		/* Makes an equation assertion about two characters
		 * @former Former value for making an evaluation
		 * @latter Latter value for making an evaluation
		 * @message Message describing the assertion
		 * @file The name of a file where the assertion is
		 * @line The number of a line where the assertion is
		 *
		 * @return nothing
		 */
		static void assertEqual (const char & former, const char & latter, Richman::Text::String && message, Richman::Text::String && file, unsigned int line) {
			bool result = former == latter;

			if (!result) {
				char * f = new char[2];
				f[0] = former;
				f[1] = '\0';

				char * l = new char[2];
				l[0] = latter;
				l[1] = '\0';

				throw AssertException (Richman::Text::String (f, 2, true), Richman::Text::String (l, 2, true), message, file, line);
			}
		}


		/* Makes an equation assertion about two c-strings
		 * @former Former value for making an evaluation
		 * @latter Latter value for making an evaluation
		 * @message Message describing the assertion
		 * @file The name of a file where the assertion is
		 * @line The number of a line where the assertion is
		 *
		 * @return nothing
		 */
		static void assertEqual (const char * former, const char * latter, Richman::Text::String && message, Richman::Text::String && file, unsigned int line) {
			bool result = std::strcmp (former, latter);

			if (result != 0)
				throw AssertException (former, latter, message, file, line);
		}


		/* Makes an assertion about two c-strings that both of them are equal along the length of the former one
		 * @former Former c-string and the shorter one
		 * @latter Latter c-string and the longer one
		 * @message Description of the assertion
		 * @file The name of a file that contains the assertion
		 * @line The number of a line that contains the assertion
		 */
		static void assertEqualAlong (const char * former, const char * latter, Richman::Text::String && message, Richman::Text::String && file, unsigned int line) {
			bool result = std::strncmp (former, latter, std::strlen (former));

			if (result != 0)
				throw AssertException (former, latter, message, file, line);
		}


		/* Makes an assertion that the expr is true
		 * @expr Evaluated value
		 * @message Description of the assertion
		 * @file The name of a file that contains the assertion
		 * @line The number of a line that contains the assertion
		 */
		static void assertTrue (bool expr, Richman::Text::String && message, Richman::Text::String && file, unsigned int line) {
			if (!expr)
				throw AssertException ("true", "false", message, file, line);
		}


		/* Makes an assertion that the expr is false
		 * @expr Evaluated value
		 * @message Description of the assertion
		 * @file The name of a file that contains the assertion
		 * @line The number of a line that contains the assertion
		 */
		static void assertFalse (bool expr, Richman::Text::String && message, Richman::Text::String && file, unsigned int line) {
			if (expr)
				throw AssertException ("false", "true", message, file, line);
		}
	};

}

#endif
