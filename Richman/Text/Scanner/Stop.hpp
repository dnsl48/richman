#ifndef Richman__Text__Scanner__Stop___hpp
#define Richman__Text__Scanner__Stop___hpp


#include "Richman/Text/Scanner/StopTraits.hpp"
#include "Richman/Text/Scanner/Symbol.hpp"


namespace Richman {
namespace Text {
namespace Scanner {


	/* Represents a stop entity when a parser should finish scanning */
	class Stop {
		StopTraits _traits;
		Symbol _symbol;

	public:
		/* Does nothing */
		Stop () = default;


		/* Initializes the entity by all the values
		 * @symbol The symbol
		 * @skip Whether the symbol should be skipped from a returned chunk of data
		 * @greedy Whether a parser should continue reading while he meets the stop-symbol
		 * @escapeShort Whether the stop entity can be escaped by the short escape entity
		 * @escapeLong Whether the stop entity can be escaped by the long escape entity
		 */
		Stop (const Symbol & symbol, bool skip = true, bool greedy = false, bool escapeShort = true, bool escapeLong = true) :
			_traits (skip, greedy, escapeShort, escapeLong),
			_symbol (symbol)
		{}


		/* Initializes the entity by all the values
		 * @symbol The symbol
		 * @skip Whether the symbol should be skipped from a returned chunk of data
		 * @greedy Whether a parser should continue reading while he meets the stop-symbol
		 * @escapeShort Whether the stop entity can be escaped by the short escape entity
		 * @escapeLong Whether the stop entity can be escaped by the long escape entity
		 */
		Stop (Symbol && symbol, bool skip = true, bool greedy = false, bool escapeShort = true, bool escapeLong = true) :
			_traits (skip, greedy, escapeShort, escapeLong),
			_symbol (symbol)
		{}


		/* Returns the symbol
		 *
		 * @return The symbol
		 */
		const Symbol & getSymbol () const {
			return _symbol;
		}


		/* Returns the traits of the entity
		 *
		 * @return The traits of the entity
		 */
		const StopTraits & getTraits () const {
			return _traits;
		}
	};

}}}

#endif
