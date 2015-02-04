#ifndef Koverager__AssertException___hpp
#define Koverager__AssertException___hpp


#include "Richman/Exception/RichException.hpp"


namespace Koverager {


	/* Exception that is going to be thrown if an assertion is not true */
	class AssertException : public Richman::Exception::RichException {
		Richman::Text::String _formerExpectationBuf;
		Richman::Text::String _latterExpectationBuf;

	public:
		/* Makes an exception with only one value that caused an error
		 * @formerExpectation The evaluated value that caused the exception
		 * @message Describing message of the failure
		 * @file The name of the file where the assertion is
		 * @line The number of a line in the file where the assertion is
		 */
		AssertException (const Richman::Text::String & formerExpectation, const Richman::Text::String & message, const Richman::Text::String & file, std::size_t line) :
			RichException (message, file, line),
			_formerExpectationBuf (formerExpectation)
		{}


		/* Makes an exception with two values, comparation of which caused an error
		 * @formerExpectation The former evaluated value that caused the exception
		 * @latterExpectation The latter evaluated value that caused the exception
		 * @message Describing message of the failure
		 * @file The name of the file where the assertion is
		 * @line The number of a line in the file where the assertion is
		 */
		AssertException (const Richman::Text::String & formerExpectation, const Richman::Text::String & latterExpectation, const Richman::Text::String & message, const Richman::Text::String & file, std::size_t line) :
			RichException (message, file, line),
			_formerExpectationBuf (formerExpectation),
			_latterExpectationBuf (latterExpectation)
		{}


		/* Constructs an exception without any values
		 * @message Describing message of the failure
		 * @file The name of the file where the assertion is
		 * @line The number of a line in the file where the assertion is
		 */
		AssertException (const Richman::Text::String & message, const Richman::Text::String & file, std::size_t line) :
			RichException (message, file, line)
		{}


		/* Constructs an exception without any values
		 * @message Describing message of the failure
		 * @file The name of the file where the assertion is
		 * @line The number of a line in the file where the assertion is
		 */
		AssertException (Richman::Text::String && message, Richman::Text::String && file, std::size_t line) :
			RichException (message, file, line)
		{}


		/* Copying constructor is a default one */
		AssertException (AssertException &) = default;


		/* Copying constructor is a default one */
		AssertException (AssertException &&) = default;


		/* Getter for the former value caused an error
		 *
		 * @return Former value
		 */
		Richman::Text::String getFormerExpectation () const {return _formerExpectationBuf;}


		/* Getter for the latter value caused an error
		 *
		 * @return Latter value
		 */
		Richman::Text::String getLatterExpectation () const {return _latterExpectationBuf;}
	};

}


#endif
