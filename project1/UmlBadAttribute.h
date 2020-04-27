/**
 * \file UmlBadAttribute.h
 *
 * \author Team Zuse
 *
 * Class that implements the bad attributes for UML
 */

#pragma once

#include <memory>
#include <string>

 /**
  * Bad attribute class
  */
class UmlBadAttribute
{
public:
	/// Set the mirror status
	/// \param m New mirror flag
	void SetBad(std::wstring m) { mBad = m; }

	/// Set the mirror status
	/// \param value string attribute value
	void SetBadValue(std::wstring value) { mBadValue = value; }

	///Gets Bad attribute
	/// \return mBadValue the bad attribute of the uml
	std::wstring GetName() { return mBadValue; }

	///Gets Bad boolean
	/// \return mBad whether the attribute is bad
	std::wstring GetBad() { return mBad; }

private:
	/// The bad attribute
	std::wstring mBad;

	/// The bad attribute
	std::wstring mBadValue;
};

