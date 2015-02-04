#ifndef Richman__Text__Scanner__Symbol___hpp
#define Richman__Text__Scanner__Symbol___hpp


#include <cstring>


namespace Richman {
namespace Text {
namespace Scanner {


	/* Represents a symbol that is a bit of parsing */
	class Symbol {
		char _first;
		std::size_t _length;
		const char * _string;

	public:
		/* Initializes the object by empty string */
		constexpr Symbol () :
			_first ('\0'),
			_length (0),
			_string ("")
		{};


		/* Initializes the object by c-string
		 * @string Pointer on a c-string 
		 */
		Symbol (const char * string) :
			_first (*string),
			_length (std::strlen (string)),
			_string (string)
		{};


		/* Returns the first character of the symbol
		 *
		 * @return The first character of the symbol
		 */
		const char & getFirst () const {
			return _first;
		}


		/* Returns the c-string of a symbol
		 *
		 * @return The c-string of a symbol
		 */
		const char * getString () const {
			return _string;
		}


		/* Returns the length of the symbol
		 *
		 * @return The length of the symbol
		 */
		const std::size_t & getLength () const {
			return _length;
		}
	};

}}}

#endif
