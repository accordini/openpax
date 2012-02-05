#include "include/resource.h"

// includes all types of resources
#include "include/resource_image.h"
#include "include/resource_string.h"
#include "include/resource_palette.h"
#include "include/resource_tech.h"

uint32 ResourceObject::getId() { return m_id; }
void ResourceObject::setId(uint32 id) { m_id = id; }


Resource::Resource() {
	m_isLoaded = 0;
}

Resource::Resource(string path) {
	m_isLoaded = 0;
	load(path);
}

Resource::~Resource() {
	if (isLoaded())
		unload();
}


int Resource::load(string path) {
	// open stream
	FILE *stream = fopen(path.c_str(), "rb");
	if (!stream) {
		cout << "Resource::load: cannot open \'" << path << "\' for reading." << endl;
		return OPX_STATUS_ERROR;
	}
	
	// get filelength 
	fseek(stream, 0, SEEK_END);
	uint32 fileSize = ftell(stream);
	fseek(stream, 0, SEEK_SET);
	
	// read data. TODO: perform some sanity checks
	fread(&m_header, sizeof(ResourceHeader), 1, stream);
	if (m_header.magic != OPX_RES_MAGIC) {
		cout << "Resource::load: file \'" << path << "\' is not a valid OPX resource file." << endl;
		fclose(stream);
		return OPX_STATUS_ERROR;
	}
	
	// read indexes
	m_objectPtrs = (ResourceObjectPtr*)calloc(sizeof(ResourceObjectPtr), m_header.numitems);
	fread(m_objectPtrs, sizeof(ResourceObjectPtr), m_header.numitems, stream);
	
	// read each object
	for (int i=0;i<m_header.numitems;i++) {
		// seek to the right location 
		fseek(stream, m_objectPtrs[i].position, SEEK_SET);
		
		// calculate how much data we have to read
		uint32 dataSize = 0;
		if (i != m_header.numitems-1)
			dataSize = m_objectPtrs[i+1].position - m_objectPtrs[i].position;
		else
			dataSize = fileSize - m_objectPtrs[i].position;
			
		// allocate buffer
		void *buffer = malloc(dataSize);
		
		// read data 
		fread(buffer, dataSize, 1, stream);
		
		// create a new resource object
		ResourceObject *newResource = NULL;

		switch (m_header.type) {
			case OPX_RES_TYPE_STRING: {
				newResource = (ResourceObject*)new StringResourceObject((ResourceObjectPtr*)&m_objectPtrs[i], buffer);
			} break;
			
			case OPX_RES_TYPE_IMAGE: {
				newResource = (ResourceObject*)new ImageResourceObject((ResourceObjectPtr*)&m_objectPtrs[i], buffer);
			} break;
			
			case OPX_RES_TYPE_PALETTE: {
				newResource = (ResourceObject*)new PaletteResourceObject((ResourceObjectPtr*)&m_objectPtrs[i], buffer);				
			} break;
			
			case OPX_RES_TYPE_TECH: {
				newResource = (ResourceObject*)new TechResourceObject((ResourceObjectPtr*)&m_objectPtrs[i], buffer);
			} break;
		}
		
		// append the new object
		if (newResource)
			m_objects.push_back(newResource);
			
		// free buffer
		free(buffer);
	}
	
	// close file 
	fclose(stream);
	
	// mark as "loaded"
	m_isLoaded = 1;
	
	return OPX_STATUS_OK;
}

void Resource::unload() { 
	if (isLoaded()) {
		// free up all resources
		for (int i=0;i<m_objects.size();i++)
			delete m_objects[i];
		
		// free pointers
		free(m_objectPtrs);
	}
	
	// reset flag
	m_isLoaded = 0;
}

int Resource::isLoaded() { 
	return m_isLoaded; 
}

ResourceObject *Resource::getObject(uint32 objectId) {
	int i;
	for (i=0;i<m_objects.size();i++)
		if (m_objects[i]->getId() == objectId) 
			return m_objects[i];
			
	return NULL;
}

uint32 Resource::getObjectsCount() {
	return m_objects.size();
}

ResourceObject *Resource::getObjectByIndex(uint32 index) {
	if (index < m_objects.size()) 
		return m_objects[index];
	return NULL;
}