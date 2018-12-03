#include "ContainerUI.h"

ContainerUI::
ContainerUI(string id, size_t width, size_t height) : FrameUI(id, width, height) {
	iCont.clear();
	sCont.clear();
}

bool
ContainerUI::has(unsigned int index) {
	return iCont.find(index) != iCont.end();
}

bool
ContainerUI::has(string index) {
	return sCont.find(index) != sCont.end();
}

container_t
ContainerUI::operator[](unsigned int index) {
	if (has(index)) {
		return iCont[index];
	}
	throw exception("ContainerUI - index not found!");
}

container_t
ContainerUI::operator[](string index) {
	if (has(index)) {
		return sCont[index];
	}
	throw exception("ContainerUI - index not found!");
}

void
ContainerUI::set(unsigned int index, double x, double y, unsigned int info) {
	iCont[index] = {x, y, info};
}

void
ContainerUI::set(string index, double x, double y, unsigned int info) {
	sCont[index] = {x, y, info};
}

void
ContainerUI::remove(unsigned int index) {
	if (has(index)) {
		iCont.erase(index);
	}
}

void
ContainerUI::remove(string index) {
	if (has(index)) {
		sCont.erase(index);
	}
}