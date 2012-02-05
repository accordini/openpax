#include "resource.h"

#ifndef __HEADER_RESOURCE_STRING_H
#define __HEADER_RESOURCE_STRING_H

// on-disk obbject signature
#define OPX_RES_TYPE_STRING 	PACK('S', 'T', 'R', '#')

// object header
struct StringResourceObjectHeader {
	uint32 magic;
	uint16 numitems;
	uint16 unknown1;
} PACKED;

// string resource class
class StringResourceObject : public ResourceObject {
public:
	StringResourceObject(ResourceObjectPtr *objectPtr, void *objectBuffer);
	virtual ~StringResourceObject();
	
	// inherited interface
	uint32 getType();
	
	// StringResourceObject interface
	uint32 getStringsCount();
	const string getStringByIndex(uint32 index);
	
private:
	StringResourceObjectHeader m_objectHeader;
	vector<string> m_strings;
};

#endif