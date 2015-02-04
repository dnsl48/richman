#ifndef Richman__Exception__NotFoundException___hpp
#define Richman__Exception__NotFoundException___hpp


#include "Richman/Exception/RichException.hpp"


namespace Richman {
namespace Exception {


	/* Represents an error when something expected hasn't been found in a storage */
	class NotFoundException : public RichException {
	public:
		/* Default constructor
		 * @message Error explanation
		 * @file The name of a file that contains an exception producer
		 * @line The number of a line that contains an exception producer
		 */
		NotFoundException (const Richman::Text::String & message, const Richman::Text::String & file, std::size_t line) :
			RichException (message, file, line)
		{}


		/* Constructor for volatile values
		 * @message Error explanation
		 * @file The name of a file that contains an exception producer
		 * @line The number of a line that contains an exception producer
		 */
		NotFoundException (Richman::Text::String && message, Richman::Text::String && file, std::size_t line) :
			RichException (message, file, line)
		{}
	};

}}


#endif
