#ifndef Richman__Text__Scanner__Resource___hpp
#define Richman__Text__Scanner__Resource___hpp


#include <cstddef>


namespace Richman {
namespace Text {
namespace Scanner {


	/* Represents a resource of symbols for a parser */
	class Resource {
		std::size_t _offset;



	public:
		/* Returns the current scanning position
		 *
		 * @return The current scanning position
		 */
		std::size_t getOffset () const {
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
		virtual bool hasNext (std::size_t length = 1) const = 0;


		/* Returns whether the resource has the amount of previous characters for reading
		 * @length Amount of characters for reading
		 *
		 * @return Whether the resource has the amount of previous characters for reading
		 */
		virtual bool hasPrev (std::size_t length = 1) const = 0;


		/* Skips the number of following characters
		 * @length The number of characters for skipping
		 */
		virtual void skipNext (std::size_t length = 1) = 0;


		/* Skips the number of previous characters
		 * @length The number of characters for skipping
		 */
		virtual void skipPrev (std::size_t length = 1) = 0;


		/* Returns the character following the current position
		 * @skip The amount of characters to be skipped before the one to be returned
		 *
		 * @return The character following the current position
		 */
		virtual char sliceNextChar (std::size_t skip = 0) const = 0;


		/* Returns the character previous to the current position
		 * @skip The amount of characters to be skipped before the one to be returned
		 *
		 * @return The character previous to the current position
		 */
		virtual char slicePrevChar (std::size_t skip = 0) const = 0;


		/* Returns the c-string following the current position
		 * @skip The amount of characters to be skipped
		 *
		 * @return The c-string following the current position
		 */
		virtual const char * sliceNextPtr (std::size_t skip = 0) const = 0;


		/* Returns the c-string previous to the current position
		 * @skip The amount of characters to be skipped
		 *
		 * @return The c-string previous to the current position
		 */
		virtual const char * slicePrevPtr (std::size_t skip = 0) const = 0;


		/* Reads the next character from resource and returns it increasing the current offset
		 *
		 * @return The next character of the resource
		 */
		virtual char readChar () = 0;
	};

}}}

#endif
