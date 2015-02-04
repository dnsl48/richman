#ifndef Richman__Exception__UninitializedException___hpp
#define Richman__Exception__UninitializedException___hpp


#include "Richman/Exception/RichException.hpp"


namespace Richman {
namespace Exception {


	/* Represents an error when something uninitialized has been requested (e.g., a null-pointer check can produce this exception) */
	class UninitializedException : public RichException {
	public:
		/* Default constructor
		 * @message Error explanation
		 * @file The name of a file that contains an exception producer
		 * @line The number of a line that contains an exception producer
		 */
		UninitializedException (const Richman::Text::String & message, const Richman::Text::String & file, std::size_t line) :
			RichException (message, file, line)
		{}


		/* Constructor for volatile values
		 * @message Error explanation
		 * @file The name of a file that contains an exception producer
		 * @line The number of a line that contains an exception producer
		 */
		UninitializedException (Richman::Text::String && message, Richman::Text::String && file, std::size_t line) :
			RichException (message, file, line)
		{}
	};

}}


#endif
