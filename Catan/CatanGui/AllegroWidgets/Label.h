#pragma once
#include "../AllegroUI/FrameUI.h"

using namespace std;

class Label: public FrameUI
{
public:
	Label(size_t width, size_t height, pos_t x = 0, pos_t y = 0, Status status = IDLE,string text = "");
	~Label();

	string getText(void);
	void setText(string newText);

private:
	string text;
};