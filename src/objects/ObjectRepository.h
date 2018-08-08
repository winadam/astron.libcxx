#pragma once

#include <vector>
#include "../dcparser/dcFile.h"
#include "DistributedObject.h"
class DistributedObject;
namespace astron   // open namespace
{

class ObjectNotFound : public std::runtime_error
{
public:
    ObjectNotFound(const std::string &class_name) : std::runtime_error("DClass with name:" + class_name + " was not found" ) { }
};

class FileNotFound : public std::runtime_error{
public:
    FileNotFound(const std::string& filename) : std::runtime_error("File " + filename + " was not found") { }
};

class ObjectRepository
{
	public:
		ObjectRepository();
		ObjectRepository(const std::vector<std::string> dcFiles);
		void addDcFile(const std::string& filename);
		uint32_t getDcHash();
		~ObjectRepository();
		DistributedObject* generateObject(const std::string &dclass_name);
		DCClass* getClass(const std::string& className);
    private:
        DCFile _file;
};


} // close namespace
