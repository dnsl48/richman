#ifndef Richman__Exception__RichException___hpp
#define Richman__Exception__RichException___hpp


#include "Richman/Text/String.hpp"


#include <exception>


namespace Richman {
namespace Exception {

	/* Base exception for all others produced by the Richman library */
	class RichException : public std::exception {
		Richman::Text::String _message;
		Richman::Text::String _file;
		std::size_t _line;

	public:
		/* Default constructor
		 * @message Error explanation
		 * @file The name of a file that contains an exception producer
		 * @line The number of a line that contains an exception producer
		 */
		RichException (const Richman::Text::String & message, const Richman::Text::String & file, std::size_t line) :
			_message(message),
			_file(file),
			_line(line)
		{}


		/* Constructor for volatile values
		 * @message Error explanation
		 * @file The name of a file that contains an exception producer
		 * @line The number of a line that contains an exception producer
		 */
		RichException (Richman::Text::String && message, Richman::Text::String && file, std::size_t line) :
			_message(message),
			_file(file),
			_line(line)
		{}


		/* Does nothing */
		virtual ~RichException () {}


		/* Returns the message of the exception
		 *
		 * @return The message of the exception
		 */
		const Richman::Text::String & getMessage () const {
			return _message;
		}


		/* Returns the name of a file that contains the exception's producer
		 *
		 * @return The name of a file that contains the exception's producer
		 */
		const Richman::Text::String & getFile () const {
			return _file;
		}


		/* Returns the number of a line that contains the exception's producer
		 *
		 * @return The number of a line that contains the exception's producer
		 */
		std::size_t getLine () const {
			return _line;
		}
	};

}}

#endif
