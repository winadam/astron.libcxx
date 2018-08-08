#pragma once
#include <string>
#include "ObjectRepository.h"
#include "DistributedField.h"


namespace astron   // open namespace
{

	class FieldNotFound : public std::runtime_error
	{
	public:
		FieldNotFound(const std::string &field_name) : std::runtime_error("DC Field with name:" + field_name + " was not found" ) { }
	};

class ObjectRepository;
class DistributedObject
{
	public:
		DistributedObject(ObjectRepository *objectRepository, const std::string &dclass_name);
		~DistributedObject();

		inline std::string get_dclass_name()
		{
			return m_dclass_name;
		}

	protected:


	private:
		std::string m_dclass_name;
		std::map<const std::string, DistributedField> m_fields;
		DCClass* m_dc_class;

	void updateField(const string &field);
};


} // close namespace
