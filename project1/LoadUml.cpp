/**
 * \file LoadUml.cpp
 *
 * \author Team Zuse
 *
 */

#include "pch.h"
#include "LoadUml.h"
#include <string>
#include "XmlNode.h"
#include <algorithm>

using namespace std;
using namespace xmlnode;

/// Filename for the pause screen image
const static wstring UmlFilename = L"images/uml.xml";

CLoadUml::CLoadUml()
{
	UMLLoad(UmlFilename);
}

void CLoadUml::UMLLoad(const std::wstring& filename) {
	try
	{
		shared_ptr<CXmlNode> root = xmlnode::CXmlNode::OpenDocument(filename);
		//Clear();

		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"inheritance")
			{
				// Found a node named <inheritance>
				wstring str = L"";
				wstring bad_name = L"";
				wstring bad_c = L"";
				wstring base_c = L"";

				for (auto child : node->GetChildren())//name and attribute
				{
					if (child->GetType() == NODE_ELEMENT && child->GetName() == L"inherit")
					{
						//str += child->GetValue();
						//Gets the bad attribute value
						UmlBadAttribute base;
						bad_name = child->GetAttributeValue(L"base", L"");
						//mName.push_back(bad_name);
						base.SetBad(bad_name);
						int b = 2;
						for (auto child2 : child->GetChildren())
						{
							if (child2->GetType() == NODE_TEXT)
							{
								base_c = child2->GetValue();
								base.SetBadValue(base_c);
								int a = 1;
								mInheritBad.push_back(base);
							}

						}

					}
				}

				for (auto child : node->GetChildren())//name and attribute
				{
					if (child->GetType() == NODE_ELEMENT && child->GetName() == L"inherit")
					{
						//str += child->GetValue();
						//Gets the bad attribute value
						UmlBadAttribute bad;
						bad_name = child->GetAttributeValue(L"bad", L"");
						//mName.push_back(bad_name);
						bad.SetBad(bad_name);
						int b = 2;
						for (auto child2 : child->GetChildren())
						{
							if (child2->GetType() == NODE_TEXT)
							{
								bad_c = child2->GetValue();
								bad.SetBadValue(bad_c);
								int a = 1;
								mInheritBad.push_back(bad);
							}

						}

					}
				}
			}
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"class")
			{
				// Found a node named <class>
				wstring str = L"";
				wstring bad_name = L"";
				wstring attribute = L"";
				wstring operation = L"";
				//std::list<int> my_list;
				for (auto child : node->GetChildren())//name and attribute
				{
					if (child->GetType() == NODE_ELEMENT && child->GetName() == L"attribute")
					{
						//str += child->GetValue();
						//Gets the bad attribute value
						UmlBadAttribute bad;
						bad_name = child->GetAttributeValue(L"bad", L"");
						//mName.push_back(bad_name);
						bad.SetBad(bad_name);
						int b = 2;
						for (auto child2 : child->GetChildren())
						{
							if (child2->GetType() == NODE_TEXT)
							{
								attribute = child2->GetValue();
								bad.SetBadValue(attribute);
								int a = 1;
								mAttributes.push_back(bad);
							}

						}

					}
					if (child->GetType() == NODE_ELEMENT && child->GetName() == L"name")
					{
						//str += child->GetValue();
						//Gets the bad attribute value
						UmlBadAttribute bad;
						bad_name = child->GetAttributeValue(L"bad", L"");
						//mName.push_back(bad_name);
						bad.SetBad(bad_name);
						int b = 2;
						for (auto child2 : child->GetChildren())
						{
							if (child2->GetType() == NODE_TEXT)
							{
								attribute = child2->GetValue();
								bad.SetBadValue(attribute);
								int a = 1;
								mNames.push_back(bad);
							}

						}
					}
					if (child->GetType() == NODE_ELEMENT && child->GetName() == L"operation")
					{
						//str += child->GetValue();
						UmlBadAttribute bad;
						bad_name = child->GetAttributeValue(L"bad", L"");
						//mName.push_back(bad_name);
						bad.SetBad(bad_name);
						//Gets the bad attribute value
						for (auto child2 : child->GetChildren())
						{
							if (child2->GetType() == NODE_TEXT)
							{
								attribute = child2->GetValue();
								bad.SetBadValue(attribute);
								int a = 1;
								mOperations.push_back(bad);
							}

						}
					}
				}
				//random_shuffle(mAttributes.begin(), mAttributes.end());
			}
		}
	}

	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
	//wstring name = L"";

}

void CLoadUml::Attribute()
{
	random_shuffle(mAttributes.begin(), mAttributes.end());
	random_shuffle(mOperations.begin(), mOperations.end());
	random_shuffle(mNames.begin(), mNames.end());

	std::sort(mAttributes.begin(), mAttributes.end(), CompareGoodBad);
	std::sort(mOperations.begin(), mOperations.end(), CompareGoodBad);
	std::sort(mNames.begin(), mNames.end(), CompareGoodBad);

}

UmlBadAttribute CLoadUml::Att(int i)
{
	return mAttributes[i];
	//return UmlBadAttribute();
}

UmlBadAttribute CLoadUml::Op(int i)
{
	return mOperations[i];
}

UmlBadAttribute CLoadUml::Name(int i)
{
	//Call the shuffle function
	return mNames[i];
}


