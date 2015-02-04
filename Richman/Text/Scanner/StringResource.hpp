#ifndef Richman__Text__Scanner__StringResource___hpp
#define Richman__Text__Scanner__StringResource___hpp


#include "Richman/Text/String.hpp"


namespace Richman {
namespace Text {
namespace Scanner {


	/* Represents a resource of symbols for a parser that incapsulates a string */
	class StringResource {
		std::size_t _offset;
		String _string;
		const char * _cstring;
		std::size_t _length;



	public:
		/* Initializes the object by the passed string
		 * @string String to be source of parsing
		 */
		StringResource (const String & string) : _string (string) {
			_offset = 0;
			_cstring = _string.getPtr ();
			_length = _string.getLength();
		}


		/* Initializes the object by the passed string
		 * @string String to be source of parsing
		 */
		StringResource (String && string) : _string (string) {
			_offset = 0;
			_cstring = _string.getPtr ();
			_length = _string.getLength();
		}


		/* Returns the current scanning position
		 *
		 * @return The current scanning position
		 */
		const std::size_t & getOffset () const {
			return _offset;
		}


		/* Sets a new position for the next scanning
		 * @offset A new position for the next scanning
		 */
		void setOffset (std::size_t offset) {
			_offset = offset;
		}


		/* Skips all following space characters
		 *
		 * @return The count of skipped characters
		 */
		std::size_t skipSpaces () {
			bool loop = true;
			std::size_t begin = getOffset ();

			while (loop && hasNext ()) {
				switch (sliceNextChar ()) {
					case ' ':
					case '\n':
					case '\t':
					case '\r':
						skipNext ();
						break;

					default:
						loop = false;
						break;
				}
			}

			return getOffset () - begin;
		}


		/* Returns whether the resource has the amount of following characters for reading
		 * @length Amount of characters for reading
		 *
		 * @return Whether the resource has the amount of following characters for reading
		 */
		bool hasNext (std::size_t length = 1) const {
			return _length >= _offset + length;
		}


		/* Returns whether the resource has the amount of previous characters for reading
		 * @length Amount of characters for reading
		 *
		 * @return Whether the resource has the amount of previous characters for reading
		 */
		bool hasPrev (std::size_t length = 1) const {
			return _offset >= length;
		}


		/* Skips the number of following characters
		 * @length The number of characters for skipping
		 */
		void skipNext (std::size_t length = 1) {
			_offset += length;
		}


		/* Skips the number of previous characters
		 * @length The number of characters for skipping
		 */
		void skipPrev (std::size_t length = 1) {
			_offset -= length;
		}


		/* Returns the character following the current position
		 * @skip The amount of characters to be skipped before the one to be returned
		 *
		 * @return The character following the current position
		 */
		const char & sliceNextChar (std::size_t skip = 0) const {
			return *(_cstring + (_offset + skip));
		}


		/* Returns the character previous to the current position
		 * @skip The amount of characters to be skipped before the one to be returned
		 *
		 * @return The character previous to the current position
		 */
		const char & slicePrevChar (std::size_t skip = 1) const {
			return *(_cstring + (_offset - skip));
		}


		/* Returns the c-string following the current position
		 * @skip The amount of characters to be skipped
		 *
		 * @return The c-string following the current position
		 */
		const char * sliceNextPtr (std::size_t skip = 0) const {
			return _cstring + (_offset + skip);
		}


		/* Returns the c-string previous to the current position
		 * @skip The amount of characters to be skipped
		 *
		 * @return The c-string previous to the current position
		 */
		const char * slicePrevPtr (std::size_t skip = 1) const {
			return _cstring + (_offset - skip);
		}


		/* Reads the next character from resource and returns it increasing the current offset
		 *
		 * @return The next character of the resource
		 */
		const char & readChar () {
			return *(_cstring + (_offset++));
		}
	};

}}}

#endif
