#ifndef TestKoverage__Richman__Confee__Mock__AnotherRule___hpp
#define TestKoverage__Richman__Confee__Mock__AnotherRule___hpp


#include "Richman/Confee/Rule.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {
namespace Mock {


	class AnotherRule : public ::Richman::Confee::Rule {
	public:
		AnotherRule * copy () const {
			return new AnotherRule ();
		}

		bool operator== (const ::Richman::Confee::Rule & value) const {
			return this == &value;
		}

		virtual bool isValid (const ::Richman::Confee::Value &) const {
			return false;
		};
	 };


 }}}}


 #endif
