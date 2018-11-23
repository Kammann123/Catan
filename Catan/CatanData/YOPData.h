#pragma once

#include "CatanData.h"

/*
* YOPData
* Implementacion de la informacion para utilizar una carta de desarrollo
* del tipo Years of Plenty
*/
class YOPData : public CatanData {
public:

	/* Constructores */
	YOPData(ResourceId fRes, ResourceId sRes);
	YOPData();

	/* Getters y setters */
	void setFirstResource(ResourceId res);
	void setSecondResource(ResourceId res);
	ResourceId getFirstResource(void);
	ResourceId getSecondResource(void);
private:
	ResourceId fResource;
	ResourceId sResource;
};