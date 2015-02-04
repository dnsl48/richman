#ifndef Koverager__Case___hpp
#define Koverager__Case___hpp


#include "Richman/Text/String.hpp"


namespace Koverager {


	/* Represents a test case that contains a list of logically related assertions */
	class Case {
		Richman::Text::String _name;
		Richman::Text::String _description;

	public:
		/* Initializes the case with a name and description
		 * @name The name of the case
		 * @description Description of the case
		 */
		Case (Richman::Text::String && name, Richman::Text::String && description) :
			_name (name),
			_description (description)
		{}


		/* Just a virtual descructor that does nothing */
		virtual ~Case () {}


		/* Runs all assertions of the case */
		virtual void run () = 0;


		/* Getter for the name of the case
		 *
		 * @return The name of the case
		 */
		const Richman::Text::String & getName () const {
			return _name;
		}


		/* Getter for the description of the case
		 *
		 * @return The description of the case
		 */
		const Richman::Text::String & getDescription () const {
			return _description;
		}
	};

}

#endif
