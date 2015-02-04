#ifndef Koverager__AssertError___hpp
#define Koverager__AssertError___hpp


#include "Koverager/AssertException.hpp"


namespace Koverager {


	/* Represents an assert error in a test and contains all the information about the error */
	class AssertError {
		Richman::Text::String _formerExpectation;
		Richman::Text::String _latterExpectation;
		Richman::Text::String _caseName;
		Richman::Text::String _caseDesc;
		Richman::Text::String _assertMessage;
		Richman::Text::String _assertFile;
		std::size_t _assertLine;

	public:
		/* Default constructor initializes all necessary parameters
		 * @formerExpectation A value that was evaluated somehow in an error prone test
		 * @latterExpectation A value that was compared with the former value
		 * @caseName The name of a test case that caused an error
		 * @caseDesc Description of a test case that caused an error
		 * @assertMessage An assertion message describing the assertion
		 * @assertFile Filename where the assertion is
		 * @assertLine Line number where the assertion is
		 */
		AssertError (
			const Richman::Text::String & formerExpectation,
			const Richman::Text::String & latterExpectation,
			const Richman::Text::String & caseName,
			const Richman::Text::String & caseDesc,
			const Richman::Text::String & assertMessage,
			const Richman::Text::String & assertFile,
			std::size_t assertLine
		) :
			_formerExpectation (formerExpectation),
			_latterExpectation (latterExpectation),
			_caseName (caseName),
			_caseDesc (caseDesc),
			_assertMessage (assertMessage),
			_assertFile (assertFile),
			_assertLine (assertLine)
		{}


		/* Copying constructor is a default one */
		AssertError (AssertError &) = default;


		/* Copying constructor is a default one */
		AssertError (AssertError &&) = default;


		/* Getter for the name of the test case that contains a test with an error
		 *
		 * @return Name of the test case
		 */
		const Richman::Text::String & getCaseName () const {
			return _caseName;
		}


		/* Getter for the description of the test case that contains a test with an error
		 *
		 * @return Description of the test case
		 */
		const Richman::Text::String & getCaseDescription () const {
			return _caseDesc;
		}


		/* Getter for the message of the assertion that caused an error
		 *
		 * @return Message of the assertion
		 */
		const Richman::Text::String & getAssertMessage () const {
			return _assertMessage;
		}


		/* Getter for the name of the file contains a test with an error
		 *
		 * @return Name of the file with the error assertion
		 */
		const Richman::Text::String & getAssertFile () const {
			return _assertFile;
		}


		/* Getter for the value that was passed to an assertion that caused an error
		 *
		 * @return Former value passed to the assertion
		 */
		const Richman::Text::String & getFormerExpectation () const {
			return _formerExpectation;
		}


		/* Getter for the value that was passed to an assertion that caused an error
		 *
		 * @return Latter value passed to the assertion
		 */
		const Richman::Text::String & getLatterExpectation () const {
			return _latterExpectation;
		}


		/* Getter for the number of a line that contains an assertion that caused an error
		 *
		 * @return Number of a line
		 */
		std::size_t getAssertLine () const {
			return _assertLine;
		}
	};
}


#endif
