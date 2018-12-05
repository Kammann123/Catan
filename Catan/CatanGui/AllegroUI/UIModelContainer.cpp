#include "UIModelContainer.h"

UIModelContainer::
UIModelContainer(string id) : FrameUI(id, 0, 0) {}

UIModelContainer::
~UIModelContainer() {
	for (auto model : models) {
		if (model.first) {
			delete model.first;
		}
	}
}

void
UIModelContainer::setPosition(pos_t x, pos_t y) {
	this->x = x;
	this->y = y;

	for (auto model : models) {
		if (model.first) {
			model.first->setPosition(model.second.x + x, model.second.y + y);
		}
	}
}

void
UIModelContainer::addPosition(pos_t x, pos_t y) {
	this->x += x;
	this->y += y;

	for (auto model : models) {
		if (model.first) {
			model.first->addPosition(x, y);
		}
	}
}

void
UIModelContainer::setVisible(bool visibleStatus) {
	this->visible = visibleStatus;

	for (auto model : models) {
		if (model.first) {
			model.first->setVisible(visibleStatus);
		}
	}
}

void
UIModelContainer::setEnable(bool enableStatus) {
	this->enable = enableStatus;

	for (auto model : models) {
		if (model.first) {
			model.first->setEnable(enableStatus);
		}
	}
}

void
UIModelContainer::setUIDestroy(bool destroys) {
	this->UIDestroys = destroys;

	for (auto model : models) {
		if (model.first) {
			model.first->setUIDestroy(destroys);
		}
	}
}

void
UIModelContainer::refactor(void) {
	for (auto model : models) {
		if (model.first) {
			model.first->refactor();
		}
	}
}

void
UIModelContainer::attachModel(FrameUI* model, double x, double y) {
	models.insert(pair<FrameUI*, relative_t>(model, { x, y }));
}

void
UIModelContainer::detachModel(FrameUI* model) {
	models.erase(model);
}

list<FrameUI*>
UIModelContainer::getModels(void) {
	list<FrameUI*> myModels;

	for (auto model : models) {
		if (model.first) {
			myModels.push_back(model.first);
		}
	}
	return myModels;
}