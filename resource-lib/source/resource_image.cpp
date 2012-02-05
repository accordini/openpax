#include "include/resource_image.h"

ImageResourceObject::ImageResourceObject(ResourceObjectPtr *objectPtr, void *buffer) {
	// setup id 
	setId(objectPtr->id);
	
	// load header
	memcpy(&m_header, buffer, sizeof(ImageResourceObjectHeader));
	
	// get data pointer 
	uint8 *dataPtr = (uint8*)&((uint8*)buffer)[sizeof(ImageResourceObjectHeader)];
	
	// load lines data 
	m_compressedLineIndexes = (uint32*)calloc(sizeof(uint32), m_header.height);
	memcpy(m_compressedLineIndexes, dataPtr, sizeof(uint32) * m_header.height);
	
	// load image data
	m_compressedImageData = (uint8*)calloc(m_header.size, 1);
	dataPtr = (uint8*)&((uint8*)buffer)[sizeof(ImageResourceObjectHeader) + sizeof(uint32)*m_header.height];
	memcpy(m_compressedImageData, dataPtr, m_header.size);
	
	// uncompress image
	m_imageData = (uint8*)calloc(m_header.width * m_header.height, 1);
	uint32 decompSize = 0;
	uint8 *p = m_imageData;
	for (int i=0;i<m_header.height;i++) {
		decompSize += getUncompressedLine(i, p);
		p = (uint8*)&m_imageData[decompSize];
	}
	
	if (decompSize != width() * height()) 
		cout << "ImageResourceObject::ImageResourceObject: image " << getId() << " incorrectly decompressed. Expected size: " << height() * width() << " , got " << decompSize << " ." << endl;
}

ImageResourceObject::~ImageResourceObject() {
	free(m_compressedLineIndexes);
	free(m_compressedImageData);
	free(m_imageData);
}

// inherited from ResourceObject
uint32 ImageResourceObject::getType() { return OPX_RES_TYPE_IMAGE; }

// ImageResourceObject interface 
uint32 ImageResourceObject::width() { return m_header.width; }
uint32 ImageResourceObject::height() { return m_header.height; }
uint8 *ImageResourceObject::pixels() { return m_imageData; }
uint32 ImageResourceObject::unknown1() { return m_header.unknown1; }
uint32 ImageResourceObject::unknown2() { return m_header.unknown2; }

// implement the RLE image encoding
uint32 ImageResourceObject::getUncompressedLineSize(uint32 lineIndex) {
	uint32 decompressedSize = 0;
	uint32 position = m_compressedLineIndexes[lineIndex];
	uint8 *ptr = (uint8*)&m_compressedImageData[position];

	while (decompressedSize < m_header.width) {
		if (((*ptr & 0xc0)>>6)==3) {
			decompressedSize += ((*ptr&0x30)>>4)*16 + (*ptr&0x0f);
			ptr++;
		} else 
			decompressedSize++;

		ptr++;
	}

	return decompressedSize;	
}

uint32 ImageResourceObject::getUncompressedLine(uint32 lineIndex, uint8 *buffer) {
	uint32 decompressedSize = 0;
	uint32 position = m_compressedLineIndexes[lineIndex];
	uint8 *ptr = (uint8*)&m_compressedImageData[position];

	while (decompressedSize < m_header.width) {
		if (((*ptr & 0xc0)>>6)==3) {
			uint32 repetitionSize = ((*ptr&0x30)>>4)*16 + (*ptr&0x0f);
			decompressedSize += repetitionSize;
			ptr++;
			for (int i=0;i<repetitionSize;i++) 
				*buffer++ = *ptr;
		} else {
			*buffer++ = *ptr;
			decompressedSize++;
		}
		ptr++;
	}
	
	return decompressedSize;
}