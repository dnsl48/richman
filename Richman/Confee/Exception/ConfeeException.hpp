#ifndef Richman__Confee__Exception__ConfeeException___hpp
#define Richman__Confee__Exception__ConfeeException___hpp


#include "Richman/Exception/RichException.hpp"


namespace Richman {
namespace Confee {
namespace Exception {

	/* Base marker for all exceptions that could be thrown by Confee.
	 *
	 * All exceptions that belong to Confee::Exception should implement this marker.
	 * It allows catching ConfeeException when we want any Confee exceptions.
	 */
	class ConfeeException : public Richman::Exception::RichException {
	public:
		/* Default constructor just passes its arguments into <Richman::Exception::RichException>
		 * @message Message to describe exception
		 * @file The name of a file that contains code which generated exception
		 * @line The number of a line that contains code which generated exception
		 */
		ConfeeException (const Text::String & message, const Text::String & file, std::size_t line) :
			RichException (message, file, line)
		{}

		/* Default constructor for volatile arguments
		 * @message Message to describe exception
		 * @file The name of a file that contains code which generated exception
		 * @line The number of a line that contains code which generated exceptionr
		 */
		ConfeeException (Text::String && message, Text::String && file, std::size_t line) :
			RichException (message, file, line)
		{}
	};

}}}

#endif
