#include "ObjectRepository.h"
#include "../dcparser/dcFile.h"
namespace astron   // open namespace
{


ObjectRepository::ObjectRepository() : _file()
{
}

    ObjectRepository::ObjectRepository(const std::vector<std::string> dcFiles) : _file() {

        for(const auto &file : dcFiles) {
            addDcFile(file);
        }

    }
    void ObjectRepository::addDcFile(const std::string &filename){
        if(!_file.read(filename)) {
            throw FileNotFound(filename);
        }
    }

    ObjectRepository::~ObjectRepository() {

    }

    DistributedObject *ObjectRepository::generateObject(const std::string &dclass_name) {
        return new DistributedObject(this, dclass_name);
    }

    uint32_t ObjectRepository::getDcHash() {
        return static_cast<uint32_t>(_file.get_hash());
    }

    DCClass *ObjectRepository::getClass(const std::string &dclass_name) {
        DCClass* dc_class = _file.get_class_by_name(dclass_name);
        if(dc_class == nullptr){
            throw new ObjectNotFound(dclass_name);
        }
        return dc_class;

    }


} // close namespace astron
