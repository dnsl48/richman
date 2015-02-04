#ifndef Richman__Text__Scanner__StopTraits___hpp
#define Richman__Text__Scanner__StopTraits___hpp

namespace Richman {
namespace Text {
namespace Scanner {


	/* Represents traits of a stop entity */
	struct StopTraits {
		/* Whether the symbol should be skipped from a returned chunk of data */
		bool skip;


		/* Whether a parser should continue reading while he meets the stop-symbol */
		bool greedy;


		/* Whether the stop entity can be escaped by the short escape entity */
		bool escapeShort;


		/* Whether the stop entity can be escaped by the long escape entity */
		bool escapeLong;



		/* Initializes the object by the values
		 * @skip Whether the symbol should be skipped from a returned chunk of data
		 * @greedy Whether a parser should continue reading while he meets the stop-symbol
		 * @escapeShort Whether the stop entity can be escaped by the short escape entity
		 * @escapeLong Whether the stop entity can be escaped by the long escape entity
		 */
		StopTraits (const bool & skip = false, const bool & greedy = false, const bool & escapeShort = false, const bool & escapeLong = false) :
			skip (skip),
			greedy (greedy),
			escapeShort (escapeShort),
			escapeLong (escapeLong)
		{}
	};

}}}

#endif
