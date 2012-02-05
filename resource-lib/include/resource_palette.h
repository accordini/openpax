#include "resource.h"

#ifndef __HEADER_RESOURCE_PALETTE_H
#define __HEADER_RESOURCE_PALETTE_H

// on-disk object signature 
#define OPX_RES_TYPE_PALETTE 	PACK('C', 'P', 'L', 'T')

// object header 
struct PaletteEntry {
	uint8 r, g, b;
} PACKED;

struct PaletteResourceObjectHeader {
	uint32 sign;
};

// palette resource object class
class PaletteResourceObject : public ResourceObject {
public:
	PaletteResourceObject(ResourceObjectPtr *objectPtr, void *buffer);
	virtual ~PaletteResourceObject();
	
	// inherited interface
	uint32 getType();
	
	// PaletteResourceObject interface
	uint32 getColorsCount();
	PaletteEntry *getColorByIndex(uint8 index);
	
private:
	PaletteResourceObjectHeader m_header;
	PaletteEntry m_paletteColors[256];	
};


#endif