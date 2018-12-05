#pragma once

#include "../../AllegroUI/ChildWindowUI.h"

#include <string>

using namespace std;

class QuestionWindow : public ChildWindowUI {
public:
	QuestionWindow(string id);
	void question(string msg, Action onYes, Action onNo);
};