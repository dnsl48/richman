#ifndef Richman__Confee__Exception__MergeSubjectsException___hpp
#define Richman__Confee__Exception__MergeSubjectsException___hpp


#include "Richman/Confee/Exception/ConfeeException.hpp"
#include "Richman/Confee/Subject.hpp"

#include "Richman/Text/String.hpp"

#include <cstddef>
#include <memory>


namespace Richman {
namespace Confee {
namespace Exception {


	/* Represents exceptions that could be thrown by the algorithm merging two subjects
	 *
	 * If two subjects aren't appropriate to be merged by some reasons, MergeSubjectsException will be thrown
	 * initialized by appropriate message and copies of subjects that was being merged.
	 */
	class MergeSubjectsException : public ConfeeException {
		std::shared_ptr<Subject> _former;
		std::shared_ptr<Subject> _latter;

	public:
		/* Initializes the instance by copies of two subjects, error message and its place
		 * @former Copy of the former subject that was being merged
		 * @latter Copy of the latter subject that was being merged
		 * @message The message describing the error
		 * @file The name of a file produced the exception
		 * @line The number of a line produced the exception
		 */
		MergeSubjectsException (Subject * former, Subject * latter, Text::String && message, Text::String && file, std::size_t line):
			ConfeeException (message, file, line),
			_former (former),
			_latter (latter)
		{}


		/* Getter for the former subject
		 *
		 * @return The former subject that was being merged
		 */
		const Subject & getFormer () const {
			return *_former.get ();
		}


		/* Getter for the latter subject
		 *
		 * @return The latter subject that was being merged
		 */
		const Subject & getLatter () const {
			return *_latter.get ();
		}
	};

}}}


#endif
