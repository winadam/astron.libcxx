#include "DistributedObject.h"
#include "ObjectRepository.h"
#include "../dcparser/dcFile.h"
#include "../dcparser/dcField.h"
#include "../dcparser/dcClass.h"

namespace astron   // open namespace
{


DistributedObject::DistributedObject(ObjectRepository *objectRepository, const std::string &dclass_name)
        : m_dclass_name(dclass_name), m_fields()
{
    m_dc_class = objectRepository->getClass(dclass_name);


}


DistributedObject::~DistributedObject()
{
}

void DistributedObject::updateField(const std::string& field){
    try {
        DistributedField distributedField = m_fields.at(field);
    }
    catch(std::out_of_range& outOfRange) {
        std::cout << "Field was not found!" << std::endl;
        DCField* dcField = m_dc_class->get_field_by_name(field);
        if(dcField) {

            m_fields.insert(std::make_pair(field, DistributedField(dcField)));
        } else{

        }
    }
}

} // close namespace astron
