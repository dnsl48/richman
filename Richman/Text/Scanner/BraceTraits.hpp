#ifndef Richman__Text__Scanner__BraceTraits___hpp
#define Richman__Text__Scanner__BraceTraits___hpp

namespace Richman {
namespace Text {
namespace Scanner {


	/* Represents traits of a Brace entity */
	struct BraceTraits {
		/* Whether the close symbol can be escaped by short escape entity */
		bool escapeShort;


		/* Whether the close symbol can be escaped by long escape entity */
		bool escapeLong;


		/* Whether stop symbols can be escaped by the embracement */
		bool escapeStop;


		/* Whether the embrace entity is also a stop entity */
		bool stop;



		/* Just initializes all values
		 * @escapeShort Whether the close symbol can be escaped by short escape entity
		 * @escapeLong Whether the close symbol can be escaped by long escape entity
		 * @escapeStop Whether stop symbols can be escaped by the embracement
		 * @stop Whether the embrace entity is also a stop entity
		 */
		BraceTraits (const bool & escapeShort = false, const bool & escapeLong = false, const bool & escapeStop = false, const bool & stop = false) :
			escapeShort (escapeShort),
			escapeLong (escapeLong),
			escapeStop (escapeStop),
			stop (stop)
		{}
	};

}}}

#endif
