#include "include/resource_string.h"

StringResourceObject::StringResourceObject(ResourceObjectPtr *objectPtr, void *objectBuffer) {
	// setup id
	setId(objectPtr->id);
	
	// load header
	memcpy((void*)&m_objectHeader, objectBuffer, sizeof(StringResourceObjectHeader));
	
	// load strings 
	char *buffer = NULL;
	uint8 *dataPtr = (uint8*) &((uint8*)objectBuffer)[sizeof(StringResourceObjectHeader)];
	for (int i=0;i<m_objectHeader.numitems;i++) {
		// get string length
		uint16 stringLength = *((uint16*)dataPtr);
		dataPtr++; dataPtr++;
		
		// reallocate buffer
		buffer = (char*)malloc(stringLength+1);
		
		// copy string into buffer
		int j;
		for (j=0;j<stringLength;j++)
			buffer[j] = *dataPtr++;
		buffer[j] = 0;
		
		// save string 
		m_strings.push_back(string(buffer));
		
		// free buffer
		free(buffer);
	}
}

StringResourceObject::~StringResourceObject() {
	// TODO: implement me.
}

// inherited interface
uint32 StringResourceObject::getType() { return OPX_RES_TYPE_STRING; }

// StringResourceObject interface
uint32 StringResourceObject::getStringsCount() {
	return m_strings.size();
}

const string StringResourceObject::getStringByIndex(uint32 index) {
	if (index < getStringsCount()) {
		return m_strings[index];
	} else {
		return string("");
	}
}
