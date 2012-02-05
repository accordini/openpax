#include "include/resource_tech.h"

TechResourceObject::TechResourceObject(ResourceObjectPtr *objectPtr, void *buffer) {
	// setup id
	setId(objectPtr->id);
	
	// copy header
	memcpy((void*)&m_header, buffer, sizeof(TechResourceObjectHeader));
}

TechResourceObject::~TechResourceObject() {
	// do nothing.
}

// inherited interface
uint32 TechResourceObject::getType() { return OPX_RES_TYPE_TECH; }

// TechResourceObject interface
uint32 TechResourceObject::getImageIndex() { return m_header.imageIndex; }
uint32 TechResourceObject::getResearchField() { return m_header.researchField; }
uint32 TechResourceObject::getResearchCost() { return m_header.researchCost; }
uint32 TechResourceObject::getMaintainceCost() { return m_header.maintainceCost; }
uint32 TechResourceObject::getBuildCost() { return m_header.buildCost; }
uint32 TechResourceObject::getTechClass() { return m_header.techClass; }
uint32 TechResourceObject::getTechDependency() { return m_header.techDependency; }
uint32 TechResourceObject::getTechRequirements() { return m_header.techRequirements; };