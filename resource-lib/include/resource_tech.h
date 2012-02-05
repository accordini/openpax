#include "resource.h"

#ifndef __HEADER_RESOURCE_TECH_H
#define __HEADER_RESOURCE_TECH_H

// on-disk object signature 
#define OPX_RES_TYPE_TECH 	PACK('T', 'E', 'C', 'H')

// object header
struct TechResourceObjectHeader {
	uint32 sign;
	uint32 id;
	uint32 imageIndex;
	uint32 researchField;
	uint32 researchCost;
	uint32 maintainceCost;
	uint32 buildCost;
	uint32 techClass;
	uint32 techDependency;
	uint32 techRequirements;
	uint32 unknowns[3];
} PACKED;

// TechResourceObject class
class TechResourceObject : public ResourceObject {
public:
	TechResourceObject(ResourceObjectPtr *objectPtr, void *buffer);
	virtual ~TechResourceObject();
	
	// inherited interface
	uint32 getType();
	
	// TechResourceObject interface
	uint32 getImageIndex();
	uint32 getResearchField();
	uint32 getResearchCost();
	uint32 getMaintainceCost();
	uint32 getBuildCost();
	uint32 getTechClass();
	uint32 getTechDependency();
	uint32 getTechRequirements();

private:
	TechResourceObjectHeader m_header;
};

#endif