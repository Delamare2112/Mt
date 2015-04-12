/*
	ASTObjs.hh - Objects that are represented in the Abstract syntax tree
*/
#pragma once

#include "core/INumeric.hh"

#include "objects/Scalar.hh"
#include "objects/Complex.hh"

#include "core/Types.hh"

#include <iostream>
#include <vector>
#include <map>
#include <string>


namespace Mt {
	namespace core {
		namespace lang {
			/*! \class NRoot
				\brief Lexical Expression Base

				This is an empty class that serves as the base for all SML lexical objects
			*/
			class NRoot {

			};
			/*! \class NStatment 
				\brief SML Lexical Statement

				This is an empty class the serves as the base for all SML lexical statements
			*/
			class NStatement : NRoot {

			};
			/*! \class NExpression
				\brief SML Lexical Expression

				This is an empty class that serves as the base for all SML expressions
			*/
			class NExpression : NRoot {

			};
			/*! \class NInteger
				\brief SML Integer Representation

				This is a lexical object that represents the Mt::objects::Integer type
			*/
			class NInteger : public NExpression {
				public:
					Mt::objects::Scalar _i;
					NInteger(int val) : _i((mtfloat_t)val) { }
			};
			/*! \class NDouble
				\brief SML Double Representation

				This is a lexical object that represents the Mt::objects::Double type
			*/
			class NDouble : public NExpression{
				public:
					Mt::objects::Scalar _d;
					NDouble(double val) : _d((mtfloat_t)val) {}
			};
			/*! \class NComplex
				\brief SML Complex Representation

				This is a lexical object that represents the Mt::objects::Complex type
			*/
			class NComplex : public NExpression {
				public:
					Mt::objects::Complex _c;
					NComplex(const std::string cplx) : _c(cplx) {}
					NComplex(const char* cplx) : _c(cplx) {}
			};
			/*! \class NIdentifier
				\brief SML Lexical Identifier

				This class holds a SML identifier, this can be a function or variable name.

				An SML identifier can be any alphanumeric string with any amount of underscores contained 
				within as long as it starts only with an alpha that matches [a-zA-Z]
			*/
			class NIdentifier : public NExpression {
				public:
					std::string _name;
					NIdentifier(const std::string& name) : _name(name) { }
			};
			/*! \class NVariableDeclaration
				\brief SML Variable Declaration Representation

				This class represents a SML variable declaration in the form of:

				~~~
				NIdentifer := NExpression
				~~~
			*/
			class NVariableDeclaration : public NStatement {
				public:
					NIdentifier& _id;
					NExpression* _assignmentExpr;
					NVariableDeclaration(NIdentifier& id) :
						_id(id) { }
					NVariableDeclaration(NIdentifier& id, NExpression *assignmentExpr) :
						_id(id), _assignmentExpr(assignmentExpr) { }
			};


			typedef std::vector<Mt::core::lang::NStatement*> StatementList;
			typedef std::vector<Mt::core::lang::NExpression*> ExpressionList;
			typedef std::vector<Mt::core::lang::NVariableDeclaration*> VariableList;

			/*! \class NMethodCall
				\brief SML Method Call Representation

				This class stores an SML method call in the form of:

				~~~
				NIdentifier := ExpressionList
				~~~

				where `ExpressionList` is `std::vector<Mt::core::lang::NExpression*>`
			*/
			class NMethodCall : public NExpression {
				public:
					const NIdentifier& _id;
					ExpressionList _arguments;
					NMethodCall(const NIdentifier& id, ExpressionList& arguments) : _id(id), _arguments(arguments) { }
					NMethodCall(const NIdentifier& id) : _id(id) { }
			};
			/*! \class NBinaryOperator
				\brief SML Binary Operator Representation

				This class is a sub-class of Mt::core::lang::NExpression that holds any binary operation in the form of:

				~~~
				NExpression OPERATOR NExpression
				~~~
			*/
			class NBinaryOperator : public NExpression {
				public:
					NExpression& _lhs;
					int _op;
					NExpression& _rhs;
					NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
						_lhs(lhs), _op(op), _rhs(rhs) { }
			};
			/*! \class NAssigmnet 
				\brief SML Assignment Operation Representation
			
				This class is a sub-class of Mt::core::lang::NExpression that holds any SML assignment
				operation in the from of:

				~~~
				NIdentifer := NExpression
				~~~
			*/
			class NAssignment : public NExpression {
				public:
					NIdentifier& _lhs;
					NExpression& _rhs;
					NAssignment(NIdentifier& lhs, NExpression& rhs) :
						_lhs(lhs), _rhs(rhs) { }
			};
			/*! \class NBlock
				\brief SML Scope Representation

				This class is a container for a collection of SML statements
			*/
			class NBlock : public NExpression {
				public:
					StatementList statements;
					NBlock() { }
			};
			/*! \class NExpressionStatement
				\brief SML Expression Statement Representation

				This class is a sub-class of Mt::core::lang::NStatement where it allows for a NExpression
				as a statement.
			*/
			class NExpressionStatement : public NStatement {
				public:
					NExpression& _expression;
					NExpressionStatement(NExpression& expression) :
						_expression(expression) { }
			};
			/*! \class NFunctionDeclaration
				\brief SML Function Declaration Representation

				This class represents the definition of an SML function in the form of:

				~~~
				NIdentifer := VariableList
				~~~

				where `VariableList` is `std::vector<Mt::core::lang::NVariableDeclaration*>`
			*/
			class NFunctionDeclaration : public NStatement {
				public:
					const NIdentifier& _id;
					VariableList _arguments;
					NBlock& _block;
					NFunctionDeclaration(const NIdentifier& id,
							const VariableList& arguments, NBlock& block) :
						_id(id), _arguments(arguments), _block(block) { }
			};

			class NListDeclaration : public NStatement {
				public:
					const NIdentifier& _id;
					VariableList _arguments;
					NBlock& _block;
					NListDeclaration(const NIdentifier& id,
							const VariableList& arguments, NBlock& block) :
						_id(id), _arguments(arguments), _block(block) { }
			};
		}
	}
}
