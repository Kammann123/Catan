#pragma once

class ResourceCard {
public:
	ResourceCard();
	ResourceCard(unsigned int resourceId);
	unsigned int getResourceId();
	unsigned int getPlayerId();
	void setResourceId(unsigned int resourceId);
	void setPlayerId(unsigned int playerId);
private:
	unsigned int resourceId;
	unsigned int playerId;
};
