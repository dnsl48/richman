#ifndef Richman__Text__String___hpp
#define Richman__Text__String___hpp


#include <algorithm>
#include <cstring>
#include <memory>
#include <ostream>



namespace Richman {
namespace Text {


	/* Simple wrapper around C-string with a control over its destruction */
	class String {
		std::shared_ptr<const char> _str;

		const char * _ptr = nullptr;

		mutable bool _lengthIsCalculated = true;
		mutable std::size_t _length = 0;


	public:
		/* Makes an empty string without any allocated memory */
		constexpr String () = default;


		/* Makes a new string with dynamically calculated length that won't be destroyed
		 * @ptr Pointer on a c-string 
		 */
		String (const char * ptr) :
			_ptr (ptr),
			_lengthIsCalculated (false)
		{}


		/* Makes a new string with precalculated length that won't be destroyed
		 * @ptr Pointer on a c-string
		 * @length Length of the string (including terminating char)
		 */
		String (const char * ptr, std::size_t length) :
			_ptr (ptr),
			_length (length)
		{}


		/* Makes a new string with precalculated length that can be destroyed if the third argument is true
		 * @ptr Pointer on a c-string
		 * @length Length of the string (including terminating char)
		 * @destruct Whether the string should be destroyed eventually
		 */
		String (const char * ptr, std::size_t length, bool destruct) :
			_str (ptr, [destruct] (const char * ptr) {if (destruct) delete [] ptr;}),
			_ptr (ptr),
			_length (length)
		{}


		/* Returns a pointer on the c-string
		 *
		 * @return A pointer on the c-string
		 */
		const char * getPtr () const {
			return _ptr;
		}


		/* Returns the length of the string
		 *
		 * @return The length of the string
		 */
		const std::size_t & getLength () const {
			if (!_lengthIsCalculated)
				_calculateLength ();

			return _length;	
		}


		/* Checks whether the current string equals to another one
		 *
		 * @return Whether the current string equals to another one
		 */
		bool operator== (const String & str) const {
			return getLength () == str.getLength () && (str.getPtr () == getPtr () || std::memcmp (getPtr (), str.getPtr (), getLength ()) == 0);
		}


		/* Checks whether the current string does not equal to another one
		 *
		 * @return Whether the current string does not equal to another one
		 */
		bool operator!= (const String & str) const {
			return getLength () != str.getLength () || (str.getPtr () != getPtr () && std::memcmp (getPtr (), str.getPtr (), getLength ()) != 0);
		}


		/* Compares the string with another one
		 * @str Another string to perform the comparation
		 *
		 * @return -1, 0 or 1 when current string lesser, equal or greater than another one
		 */
		bool operator< (const String & str) const {
			if (getPtr () == str.getPtr ())
				return getLength () < str.getLength ();

			char result = std::memcmp (getPtr (), str.getPtr (), std::min (getLength (), str.getLength ()));

			if (result == 0)
				return getLength () < str.getLength ();
			else
				return result < 0;
		}

	private:
		/* Calculates the length of the string (std::strlen) */
		void _calculateLength () const {
			_length = _ptr == nullptr ? 0 : std::strlen (_ptr) + 1;
			_lengthIsCalculated = true;
		}
	};


	/* Makes it possible to output strings
	 * @stream Stream for the output
	 * @string String to be putted out
	 *
	 * @return Stream that was used for the output
	 */
	inline std::ostream & operator<< (std::ostream & stream, const Richman::Text::String & string) {
		if (string.getLength ())
			stream << string.getPtr ();
		return stream;
	}

}}


#endif
