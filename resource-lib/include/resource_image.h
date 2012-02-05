#include "resource.h"

#ifndef __HEADER_RESOURCE_IMAGE_H
#define __HEADER_RESOURCE_IMAGE_H

// on-disk object signature
#define OPX_RES_TYPE_IMAGE 		PACK('P', 'P', 'I', 'C')

// object header
struct ImageResourceObjectHeader {
	uint32 sign;
	uint32 unknown1, unknown2;
	uint32 width, height;
	uint32 size;
} PACKED;

// image resource class 
class ImageResourceObject : public ResourceObject {
public:
	ImageResourceObject(ResourceObjectPtr *objectPtr, void *buffer);
	virtual ~ImageResourceObject();
	
	// inherited from ResourceObject
	uint32 getType();
	
	// ImageResourceObject interface 
	uint32 width();
	uint32 height();
	uint8 *pixels();
	uint32 unknown1();
	uint32 unknown2();
	
protected:
	// implement the RLE image encoding
	uint32 getUncompressedLineSize(uint32 lineIndex);
	uint32 getUncompressedLine(uint32 lineIndex, uint8 *buffer);
		
private:
	ImageResourceObjectHeader m_header;
	uint8 *m_compressedImageData;
	uint32 *m_compressedLineIndexes;
	uint8 *m_imageData;
};

#endif