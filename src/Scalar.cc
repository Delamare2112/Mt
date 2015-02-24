/*
	Scalar.cc - Scalar
*/

#include "objects/Scalar.hh"

namespace Mt {
	namespace objects {
		Scalar::Scalar(){
			Internal = 0;
		}

		Scalar::Scalar(mtfloat_t num){
			Internal = num;
		}

		Scalar::Scalar(Scalar&& s){
			Internal = s.Internal;
		}

		Scalar::Scalar(Scalar& s){
			Internal = s.Internal;
		}

		Scalar::~Scalar(){

		}

		/*!
			The assignment operator, this should check for type so you cant assign a Mt::Complex to an Mt::Integer
		*/
		Scalar& Scalar::operator=(Scalar& rhs){
			Internal = rhs.Internal;
			return *this;
		}
		Scalar& Scalar::operator=(mtfloat_t& rhs){
			Internal = rhs;
			return *this;
		}

		// Basic Arithmetic operations
		Scalar& Scalar::operator+(Scalar& rhs){
			Scalar s(Internal + rhs.Internal);
			return s;
		}
		Scalar& Scalar::operator-(Scalar& rhs){
			Scalar s(Internal - rhs.Internal);
			return s;
		}
		Scalar& Scalar::operator*(Scalar& rhs){
			Scalar s(Internal * rhs.Internal);
			return s;
		}
		Scalar& Scalar::operator/(Scalar& rhs){
			Scalar s(Internal / rhs.Internal);
			return s;
		}
		Scalar& Scalar::operator++(int){
			Internal++;
			return *this;
		}
		Scalar& Scalar::operator--(int){
			Internal--;
			return *this;
		}

		// Basic Arithmetic operations mtfloat_t
		Scalar& Scalar::operator+(mtfloat_t& rhs){
			Scalar s(Internal + rhs);
			return s;
		}
		Scalar& Scalar::operator-(mtfloat_t& rhs){
			Scalar s(Internal - rhs);
			return s;
		}
		Scalar& Scalar::operator*(mtfloat_t& rhs){
			Scalar s(Internal * rhs);
			return s;
		}
		Scalar& Scalar::operator/(mtfloat_t& rhs){
			Scalar s(Internal / rhs);
			return s;
		}

		// Comparison Scalar::operators
		bool Scalar::operator==(Scalar const& rhs){
			return Internal == rhs.Internal;
		}
		bool Scalar::operator!=(Scalar const& rhs){
			return Internal != rhs.Internal;
		}
		bool Scalar::operator>(Scalar const& rhs){
			return Internal > rhs.Internal;
		}
		bool Scalar::operator<(Scalar const& rhs){
			return Internal < rhs.Internal;
		}
		bool Scalar::operator>=(Scalar const& rhs){
			return Internal >= rhs.Internal;
		}
		bool Scalar::operator<=(Scalar const& rhs){
			return Internal <= rhs.Internal;
		}
		// Comparison mtfloat_t
		bool Scalar::operator==(mtfloat_t const& rhs){
			return Internal == rhs;
		}
		bool Scalar::operator!=(mtfloat_t const& rhs){
			return Internal != rhs;
		}
		bool Scalar::operator>(mtfloat_t const& rhs){
			return Internal > rhs;
		}
		bool Scalar::operator<(mtfloat_t const& rhs){
			return Internal < rhs;
		}
		bool Scalar::operator>=(mtfloat_t const& rhs){
			return Internal >= rhs;
		}
		bool Scalar::operator<=(mtfloat_t const& rhs){
			return Internal <= rhs;
		}
	}
}
