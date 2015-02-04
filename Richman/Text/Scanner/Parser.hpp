#ifndef Richman__Text__Scanner__Parser___hpp
#define Richman__Text__Scanner__Parser___hpp


#include "Richman/Text/Scanner/Brace.hpp"
#include "Richman/Text/Scanner/Escape.hpp"
#include "Richman/Text/Scanner/Stop.hpp"
#include "Richman/Text/String.hpp"
#include "Richman/Text/Scanner/StringResource.hpp"

#include <cstring>


namespace Richman {
namespace Text {
namespace Scanner {


	/* Single threaded parser without any allocations */
	template <
		unsigned char stopsCount,
		unsigned char escapesShortCount = 0,
		unsigned char escapesLongCount = 0,
		unsigned char bracesCount = 0,
		typename Resource = StringResource
	>
	class Parser {
		Stop _stopsList[stopsCount];
		Brace _bracesList[bracesCount];
		Escape _escapesShortList[escapesShortCount];
		Escape _escapesLongList[escapesLongCount];

		bool _readFlag;

		std::size_t _lastReadPosition;

		bool _escapeShortFlag;
		std::size_t _escapeShortOffset;

		std::size_t _escapeLongPtr;
		bool _escapeLongFlag;

		std::size_t _greedyCount;
		std::size_t _greedyLength;

		std::size_t _bracesCount;
		std::size_t _braces[bracesCount];

		std::size_t _sectionOffset[2];



	public:
		/* Default constructor */
		constexpr Parser () = default;


		/* Default copying constructor */
		constexpr Parser (const Parser &) = default;


		/* Default volatile constructor */
		constexpr Parser (Parser &&) = default;


		/* Initializes a new stop entity by the passed values
		 * @idx Index of the entity that must have been reserved while the type declaration
		 * @symbol The symbol of the <Stop> entity
		 * @skip Skip trait of the <Stop> entity
		 * @greedy Greedy trait of the <Stop> entity
		 * @escapeShort escapeShort trait of the <Stop> entity
		 * @escapeLong escapeLong trait of the <Stop> entity
		 */
		void setStop (const unsigned char & idx, Symbol && symbol, bool skip = true, bool greedy = true, bool escapeShort = true, bool escapeLong = true) {
			if (idx < stopsCount)
				_stopsList[idx] = Stop (symbol, skip, greedy, escapeShort, escapeLong);
		}


		/* Initializes a new brace entity by the passed values
		 * @idx Index of the entity that must have been reserved while the type declaration
		 * @openSymbol The open symbol of the <Brace> entity
		 * @closeSymbol The close symbol of the <Brace> entity
		 * @escapeShort escapeShort trait of the <Brace> entity
		 * @escapeLong escapeLong trait of the <Brace> entity
		 * @escapeStop escapeStop trait of the <Brace> entity
		 * @stop stap trait of the <Brace> entity
		 */
		void setBrace (const unsigned char & idx, Symbol && openSymbol, Symbol && closeSymbol, bool escapeShort = true, bool escapeLong = true, bool escapeStop = true, bool stop = true) {
			if (idx < bracesCount)
				_bracesList[idx] = Brace (openSymbol, closeSymbol, escapeShort, escapeLong, escapeStop, stop);
		}


		/* Initializes a new escapeShort entity by the passed values
		 * @idx Index of the entity that must have been reserved while the type declaration
		 * @symbol The symbol of the <Escape> entity
		 */
		void setEscapeShort (const unsigned char & idx, Symbol && symbol) {
			if (idx < escapesShortCount)
				_escapesShortList[idx] = Escape (symbol);
		}


		/* Initializes a new escapeLong entity by the passed values
		 * @idx Index of the entity that must have been reserved while the type declaration
		 * @symbol The symbol of the <Escape> entity
		 */
		void setEscapeLong (const unsigned char & idx, Symbol && symbol) {
			if (idx < escapesLongCount)
				_escapesLongList[idx] = Escape (symbol);
		}


		/* Returns the count of symbols that was eaten greedly while the last reading
		 *
		 * @return The count of symbols that was eaten greedly while the last reading
		 */
		const std::size_t & getGreedyCount () const {
			return _greedyCount;
		}


		/* Returns the length of a piece of a resource, that was eaten greedly
		 *
		 * @return The length of a piece of a resource, that was eaten greedly
		 */
		const std::size_t & getGreedyLength () const {
			return _greedyLength;
		}


		/* Returns the current offset of a resource
		 *
		 * @return The current offset of a resource
		 */
		const std::size_t * getSectionOffset () const {
			return _sectionOffset;
		}


		/* Reads a section of the passed resource and returns it as a string
		 * @resource Resource to be read
		 *
		 * @return The read part of the passed resource
		 */
		String readSection (Resource & resource) {
			_greedyCount = 0;
			_greedyLength = 0;
			_lastReadPosition = 0;
			_sectionOffset[0] = resource.getOffset ();
			_escapeLongFlag = false;
			_escapeLongPtr = 0;
			_escapeShortFlag = false;
			_escapeShortOffset = 0;
			_bracesCount = 0;
			_readFlag = true;

			for (unsigned char i=0; i<bracesCount; ++i)
				_braces[i] = 0;

			bool skipGreedyLength = false;

			while (_readFlag && resource.hasNext ())
				skipGreedyLength = _hook (resource);

			_sectionOffset[1] = _lastReadPosition - (skipGreedyLength ? _greedyLength : 0);

			return String (resource.slicePrevPtr (resource.getOffset () - _sectionOffset[0]), _sectionOffset[1] - _sectionOffset[0]);
		}



	private:
		/* Reads the passed resource using all the parser's logic
		 * @resource Resource to be read
		 *
		 * @return Whether parser should skip the length of greedly read skip symbols
		 */
		bool _hook (Resource & resource) {
			const char & chr = resource.readChar ();
			_lastReadPosition = resource.getOffset ();

			if (_escapeShortFlag && _escapeShortOffset != (_lastReadPosition - 1)) {
				_escapeShortFlag = false;
				_escapeShortOffset = 0;
			}

			bool stopFound;
			unsigned char stopIndex;
			_searchStop (resource, chr, stopFound, stopIndex);

			if (stopFound) {
				if (_escapeShortFlag && _stopsList[stopIndex].getTraits ().escapeShort) {
					_escapeShortFlag = false;

					return false;
				}

				if (_escapeLongFlag && _stopsList[stopIndex].getTraits ().escapeLong)
					return false;

				for (unsigned char i = 0; i < bracesCount; ++i) {
					if (_braces[i] > 0) {
						if (_bracesList[i].getTraits ().escapeStop)
							return false;
					}
				}

				_readFlag = false;
				if (_stopsList[stopIndex].getSymbol ().getLength () > 1)
					resource.skipNext (_stopsList[stopIndex].getSymbol ().getLength () - 1);

				_greedyCount = 1;
				_lastReadPosition += _stopsList[stopIndex].getSymbol ().getLength () - 1;

				if (_stopsList[stopIndex].getTraits ().greedy) {
					while (
							resource.hasNext (_stopsList[stopIndex].getSymbol ().getLength ())
						&&
							resource.sliceNextChar () == _stopsList[stopIndex].getSymbol ().getFirst ()
						&&
							std::memcmp (resource.sliceNextPtr (), _stopsList[stopIndex].getSymbol ().getString (), _stopsList[stopIndex].getSymbol ().getLength ()) == 0
					)
						resource.skipNext (_stopsList[stopIndex].getSymbol ().getLength ());

					_greedyCount += (resource.getOffset () - _lastReadPosition) / _stopsList[stopIndex].getSymbol ().getLength ();
					_lastReadPosition = resource.getOffset ();
				}

				_greedyLength = _greedyCount * _stopsList[stopIndex].getSymbol ().getLength ();

				return _stopsList[stopIndex].getTraits ().skip;
			}


			bool eshortFound;
			unsigned char eshortIndex;
			_searchEshort (resource, chr, eshortFound, eshortIndex);
			if (eshortFound) {
				if (_escapesShortList[eshortIndex].getSymbol ().getLength () > 1) {
					resource.skipNext (_escapesShortList[eshortIndex].getSymbol ().getLength () - 1);
					_lastReadPosition = resource.getOffset ();
				}

				if (_escapeShortFlag) {
					_escapeShortOffset = 0;
					_escapeShortFlag = false;

					return false;

				} else {
					_escapeShortOffset = _lastReadPosition;
					_escapeShortFlag = true;

					return false;
				}
			}


			bool elongFound;
			unsigned char elongIndex;
			_searchElong (resource, chr, elongFound, elongIndex);
			if (elongFound) {
				if (_escapesLongList[elongIndex].getSymbol ().getLength () > 1) {
					resource.skipNext (_escapesLongList[elongIndex].getSymbol ().getLength () - 1);
					_lastReadPosition = resource.getOffset ();
				}

				if (_escapeShortFlag) {
					_escapeShortFlag = false;

					return false;

				} else if (!_escapeLongFlag) {
					_escapeLongPtr = elongIndex;
					_escapeLongFlag = true;

					return false;

				} else if (elongIndex == _escapeLongPtr) {
					_escapeLongFlag = false;

					return false;
				}
			}


			bool braceFound;
			unsigned char braceIndex;
			bool isOpenBraceFound;
			_searchBrace (resource, chr, braceFound, braceIndex, isOpenBraceFound);
			if (braceFound) {
				if (isOpenBraceFound) {
					if (_bracesList[braceIndex].getOpenSymbol ().getLength () > 1) {
						resource.skipNext (_bracesList[braceIndex].getOpenSymbol ().getLength () - 1);
						_lastReadPosition = resource.getOffset ();
					}
				} else {
					if (_bracesList[braceIndex].getCloseSymbol ().getLength () > 1) {
						resource.skipNext (_bracesList[braceIndex].getCloseSymbol ().getLength () - 1);
						_lastReadPosition = resource.getOffset ();
					}
				}

				if (_escapeShortFlag && _bracesList[braceIndex].getTraits ().escapeShort) {
					_escapeShortFlag = false;

					return false;
				}

				if (_escapeLongFlag && _bracesList[braceIndex].getTraits ().escapeLong)
					return false;

				if (isOpenBraceFound) {
					++_braces[braceIndex];
					++_bracesCount;
				} else {
					if (_braces[braceIndex] > 0) {
						--_braces[braceIndex];
						--_bracesCount;

						if (_bracesList[braceIndex].getTraits ().stop && _bracesCount == 0)
							_readFlag = false;
					}
				}
			}

			return false;
		}


		/* Tries to find the symbol of the current position in the list of stop-symbols
		 * @resource Link on the read resource
		 * @chr Current character as it read from resource
		 * @result Whether the symbol found
		 * @index Index of the found symbol in the list
		 */
		void _searchStop (Resource & resource, const char & chr, bool & result, unsigned char & index) {
			result = false;

			for (unsigned char ix = 0; ix < stopsCount; ++ix) {
				if (_stopsList[ix].getSymbol ().getFirst () == chr) {
					if (
						_stopsList[ix].getSymbol ().getLength () > 1
					&&
						(
							!resource.hasNext (_stopsList[ix].getSymbol ().getLength () - 1)
						||
							std::memcmp (resource.sliceNextPtr (), _stopsList[ix].getSymbol ().getString () + 1, _stopsList[ix].getSymbol ().getLength () - 1) != 0
						)
					)
						continue;

					result = true;
					index = ix;
					break;
				}
			}
		}


		/* Tries to find the symbol of the current position in the list of short-escape symbols
		 * @resource Link on the read resource
		 * @chr Current character as it read from resource
		 * @result Whether the symbol found
		 * @index Index of the found symbol in the list
		 */
		void _searchEshort (Resource & resource, const char & chr, bool & result, unsigned char & index) {
			result = false;

			for (unsigned char ix = 0; ix < escapesShortCount; ++ix) {
				if (_escapesShortList[ix].getSymbol ().getFirst () == chr) {
					if (
						_escapesShortList[ix].getSymbol ().getLength () > 1
					&&
						(
							!resource.hasNext (_escapesShortList[ix].getSymbol ().getLength () - 1)
						||
							std::memcmp (resource.sliceNextPtr (), _escapesShortList[ix].getSymbol ().getString () + 1, _escapesShortList[ix].getSymbol ().getLength () - 1) != 0
						)
					)
						continue;

					result = true;
					index = ix;
					break;
				}
			}
		}


		/**
		 * Tries to find the symbol of the current position in the list of long-escape symbols
		 * @resource Link on the read resource
		 * @chr Current character as it read from resource
		 * @result Whether the symbol found
		 * @index Index of the found symbol in the list
		 */
		void _searchElong (Resource & resource, const char & chr, bool & result, unsigned char & index) {
			result = false;

			for (unsigned char ix = 0; ix < escapesLongCount; ++ix) {
				if (_escapesLongList[ix].getSymbol ().getFirst () == chr) {
					if (
						_escapesLongList[ix].getSymbol ().getLength () > 1
					&&
						(
							!resource.hasNext (_escapesLongList[ix].getSymbol ().getLength () - 1)
						||
							std::memcmp (resource.sliceNextPtr (), _escapesLongList[ix].getSymbol ().getString () + 1, _escapesLongList[ix].getSymbol ().getLength () - 1) != 0
						)
					)
						continue;

					result = true;
					index = ix;
					break;
				}
			}
		}


		/* Tries to find the symbol of the current position in the list of braces
		 * @resource Link on the read resource
		 * @chr Current character as it read from resource
		 * @result Whether the symbol found
		 * @index Index of the found symbol in the list
		 * @isOpenBraceFound Whether the found symbol is open or close
		 */
		void _searchBrace (Resource & resource, const char & chr, bool & result, unsigned char & index, bool & isOpenBraceFound) {
			result = false;

			for (unsigned char ix = 0; ix < bracesCount; ++ix) {
				if (_bracesList[ix].getOpenSymbol ().getFirst () == chr) {
					if (
						_bracesList[ix].getOpenSymbol ().getLength () > 1
					&&
						(
							!resource.hasNext (_bracesList[ix].getOpenSymbol ().getLength () - 1)
						||
							std::memcmp (resource.sliceNextPtr (), _bracesList[ix].getOpenSymbol ().getString () + 1, _bracesList[ix].getOpenSymbol ().getLength () - 1) != 0
						)
					) {
						// pass
					} else {
						result = true;
						index = ix;
						isOpenBraceFound = true;
						break;
					}
				}

				if (_bracesList[ix].getCloseSymbol ().getFirst () == chr) {
					if (
						_bracesList[ix].getCloseSymbol ().getLength () > 1
					&&
						(
							!resource.hasNext (_bracesList[ix].getCloseSymbol ().getLength () - 1)
						||
							std::memcmp (resource.sliceNextPtr (), _bracesList[ix].getCloseSymbol ().getString () + 1, _bracesList[ix].getCloseSymbol ().getLength () - 1) != 0
						)
					) {
						// pass
					} else {
						result = true;
						index = ix;
						isOpenBraceFound = false;
						break;
					}
				}
			}
		}
	};

}}}


#endif
