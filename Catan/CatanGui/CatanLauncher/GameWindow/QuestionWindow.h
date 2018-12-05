#pragma once

#include "../../AllegroUI/ChildWindowUI.h"

#include <string>

using namespace std;

class QuestionWindow : public ChildWindowUI {
public:
	QuestionWindow(string id, Action onYes, Action onNo);
};