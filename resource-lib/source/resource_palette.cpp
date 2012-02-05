#include "include/resource_palette.h"

PaletteResourceObject::PaletteResourceObject(ResourceObjectPtr *objectPtr, void *buffer) {
	// setup id
	setId(objectPtr->id);
	
	// read header
	memcpy(&m_header, buffer, sizeof(PaletteResourceObjectHeader));
	
	// copy data skipping 4 bytes
	uint8 *dataPtr = (uint8*)&((uint8*)buffer)[sizeof(uint32)];
	memcpy(&m_paletteColors, (void*)dataPtr, sizeof(PaletteEntry) * 256);
}

PaletteResourceObject::~PaletteResourceObject() {
	// nothing to do :P
}

// inherited interface
uint32 PaletteResourceObject::getType() { return OPX_RES_TYPE_PALETTE; }

// PaletteResourceObject interface
uint32 PaletteResourceObject::getColorsCount() { return 256; }
PaletteEntry *PaletteResourceObject::getColorByIndex(uint8 index) { 
	return (PaletteEntry*)&m_paletteColors[index];
}
