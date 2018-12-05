#include "QuestionWindow.h"

#include "../../AllegroWidgets/UIBuilder.h"

#define QUESTION_BACKGROUND "CatanGui\\GUIDesigns\\QuestionWindow\\question_background.png"

#define YES_NORMAL "CatanGui\\GUIDesigns\\QuestionWindow\\yes.png"
#define YES_FOCUS "CatanGui\\GUIDesigns\\QuestionWindow\\yes_focus.png"

#define NO_NORMAL "CatanGui\\GUIDesigns\\QuestionWindow\\no.png"
#define NO_FOCUS "CatanGui\\GUIDesigns\\QuestionWindow\\no_focus.png"

QuestionWindow::
QuestionWindow(string id, Action onYes, Action onNo) : ChildWindowUI(id, 800, 500) {
	UIComponent* yesButton = UIBuilder::createButton("yesButton");
	UIComponent* noButton = UIBuilder::createButton("noButton");

	/* Configuro los botones */
	(*yesButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, YES_NORMAL);
	(*yesButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, YES_FOCUS);
	(*yesButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, YES_FOCUS);
	(*yesButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, YES_FOCUS);

	(*noButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, NO_NORMAL);
	(*noButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, NO_FOCUS);
	(*noButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, NO_FOCUS);
	(*noButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, NO_FOCUS);

	/* Posiciones */
	MODEL(yesButton, MouseUI*)->setPosition(520, 250);
	MODEL(noButton, MouseUI*)->setPosition(520, 330);

	/* Attach de componentes */
	this->attachComponent(yesButton);
	this->attachComponent(noButton);

	/* Callbacks */
	MODEL(yesButton, MouseUI*)->setClickAction(onYes);
	MODEL(noButton, MouseUI*)->setClickAction(onNo);

	/* Configuracion general */
	this->setBackground(QUESTION_BACKGROUND);

	/* Pongo los botones visibles */
	yesButton->getModel()->setVisible(true);
	yesButton->getModel()->setEnable(true);
	noButton->getModel()->setVisible(true);
	noButton->getModel()->setEnable(true);
}