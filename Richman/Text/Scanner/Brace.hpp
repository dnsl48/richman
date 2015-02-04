#ifndef Richman__Text__Scanner__Brace___hpp
#define Richman__Text__Scanner__Brace___hpp


#include "Richman/Text/Scanner/BraceTraits.hpp"
#include "Richman/Text/Scanner/Symbol.hpp"


namespace Richman {
namespace Text {
namespace Scanner {


	/* Represents an entity that can embrace other entities */
	class Brace {
		BraceTraits _traits;
		Symbol _open;
		Symbol _close;

	public:
		/* Empty constructor does nothing */
		Brace () = default;


		/* Initializes the object by all parameters it needs
		 * @open Symbol that opens the brace
		 * @close Symbol that closes the brace
		 * @escapeShort Whether the close symbol can be escaped by short escape entity
		 * @escapeLong Whether the close symbol can be escaped by long escape entity
		 * @escapeStop Whether stop symbols can be escaped by the embracement
		 * @stop Whether the embrace entity is also a stop entity
		 */
		Brace (const Symbol & open, const Symbol & close, bool escapeShort = true, bool escapeLong = true, bool escapeStop = true, bool stop = false) :
			_traits (escapeShort, escapeLong, escapeStop, stop),
			_open (open),
			_close (close)
		{}


		/* Constructor for volatile entities
		 * @open Symbol that opens the brace
		 * @close Symbol that closes the brace
		 * @escapeShort Whether the close symbol can be escaped by short escape entity
		 * @escapeLong Whether the close symbol can be escaped by long escape entity
		 * @escapeStop Whether stop symbols can be escaped by the embracement
		 * @stop Whether the embrace entity is also a stop entity
		 */
		Brace (Symbol && open, Symbol && close, bool escapeShort = true, bool escapeLong = true, bool escapeStop = true, bool stop = false) :
			_traits (escapeShort, escapeLong, escapeStop, stop),
			_open (open),
			_close (close)
		{}


		/* Returns traits of the entity
		 *
		 * @return Traits of the entity
		 */
		const BraceTraits & getTraits () const {
			return _traits;
		}


		/* Returns the open <Symbol> of the entity
		 *
		 * @return The open <Symbol> of the entity
		 */
		const Symbol & getOpenSymbol () const {
			return _open;
		}


		/* Returns the close <Symbol> of the entity
		 *
		 * @return The close <Symbol> of the entity
		 */
		const Symbol & getCloseSymbol () const {
			return _close;
		}
	};

}}}

#endif
