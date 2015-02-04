#ifndef Richman__Text__Scanner__Escape___hpp
#define Richman__Text__Scanner__Escape___hpp


#include "Richman/Text/Scanner/Symbol.hpp"


namespace Richman {
namespace Text {
namespace Scanner {


	/* Represents an escape entity */
	class Escape {
		Symbol _symbol;


	public:
		/* Does nothing */
		Escape () = default;


		/* Initializes the entity by a symbol
		 * @symbol The symbol
		 */
		Escape (const Symbol & symbol) : _symbol(symbol) {}


		/* Initializes the entity by a symbol
		 * @symbol The symbol
		 */
		Escape (Symbol && symbol) : _symbol(symbol) {}


		/* Returns the symbol
		 *
		 * @return The symbol
		 */
		const Symbol & getSymbol () const {
			return _symbol;
		}
	};

}}}

#endif
