#include "common.h"

#ifndef __HEADER_RESOURCE_H
#define __HEADER_RESOURCE_H

// core structures
struct ResourceHeader {
	uint16 	magic;			// must be 0x4949
	uint32 	version;
	uint32	type;
	uint32	numitems;
} PACKED;

struct ResourceObjectPtr {
	uint32	id;
	uint32	position;
} PACKED;

class ResourceObject {
public:
	uint32 getId();
	virtual uint32 getType()=0;
	
protected:
	void setId(uint32 id);	
	
private:
	uint32 m_id;
};

class Resource {
public:
	Resource();
	Resource(string path);
	virtual ~Resource();
	
	int load(string path);
	void unload();
	int isLoaded();
	ResourceObject *getObject(uint32 objectId);
	uint32 getObjectsCount();
	ResourceObject *getObjectByIndex(uint32 index);
	
private:
	int m_isLoaded;
	ResourceHeader m_header;
	ResourceObjectPtr *m_objectPtrs;
	vector<ResourceObject*> m_objects;
};

#endif
