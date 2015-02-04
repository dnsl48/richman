#ifndef TestKoverage__Richman__Confee__Mock__SameRule___hpp
#define TestKoverage__Richman__Confee__Mock__SameRule___hpp


#include "Richman/Confee/Rule.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {
namespace Mock {


	class SameRule : public ::Richman::Confee::Rule {
	public:
		SameRule * copy () const {
			return new SameRule ();
		}

		bool operator== (const ::Richman::Confee::Rule & value) const {
			return true;
		}

		virtual bool isValid (const ::Richman::Confee::Value &) const {
			return true;
		};
	 };


 }}}}


 #endif
