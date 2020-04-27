/**
 * \file LoadUml.h
 *
 * \author Team Zuse
 *
 * Class that loads Uml text.
 *
 */

#pragma once
#include <vector>
#include "UmlBadAttribute.h"
#include <vector>

/// the screen class
class CScreen;

/** Class that handles loading UML text
*/
class CLoadUml
{
public:

	///Constructor for load uml
	CLoadUml();

	CLoadUml(const CLoadUml&) = delete; ///< Deleted constructor

	/// Load uml
	/// \param filename image file
	void UMLLoad(const std::wstring& filename);

	/// attribute of uml
	void Attribute();

	/// bad attribute of uml
	/// \param i index
	/// \return string
	UmlBadAttribute Att(int i);

	/// bad operation of uml
	/// \param i index
	/// \return string
	UmlBadAttribute Op(int i);

	/// bad name of uml
	/// \param i index
	/// \return string
	UmlBadAttribute Name(int i);

	/// Comparison between uml attribute objects
	/// \param a the first attribute to compare
	/// \param b the second attribute to compare
	/// \return bool whether the second attribute is worse
	static bool CompareGoodBad(UmlBadAttribute a, UmlBadAttribute b) { return (a.GetBad() < b.GetBad()); }

private:
	/// The attributes that go inside our UML boxes
	std::vector<UmlBadAttribute> mAttributes;

	/// The operations that go inside our UML boxes
	std::vector<UmlBadAttribute> mOperations;

	/// The names that go inside our UML boxes
	std::vector<UmlBadAttribute> mNames;

	/// Inheritance names
	std::vector<UmlBadAttribute> mInheritanceNames;

	/// Bad inheritance
	std::vector<UmlBadAttribute> mInheritBad;


};

