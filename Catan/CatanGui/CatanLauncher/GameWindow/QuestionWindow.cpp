#include "QuestionWindow.h"

#include "../../AllegroWidgets/UIBuilder.h"

#define QUESTION_BACKGROUND "CatanGui\\GUIDesigns\\QuestionWindow\\question_background.png"

#define YES_NORMAL "CatanGui\\GUIDesigns\\QuestionWindow\\yes.png"
#define YES_FOCUS "CatanGui\\GUIDesigns\\QuestionWindow\\yes_focus.png"

#define NO_NORMAL "CatanGui\\GUIDesigns\\QuestionWindow\\no.png"
#define NO_FOCUS "CatanGui\\GUIDesigns\\QuestionWindow\\no_focus.png"

QuestionWindow::
QuestionWindow(string id) : ChildWindowUI(id, 800, 500) {
	UIComponent* yesButton = UIBuilder::createButton("yesButton");
	UIComponent* noButton = UIBuilder::createButton("noButton");
	UIComponent* label = UIBuilder::createMultiLabel("message", 215, 15);

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
	MODEL(label, TextUI*)->setPosition(345, 120);

	/* Attach de componentes */
	this->attachComponent(yesButton);
	this->attachComponent(noButton);
	this->attachComponent(label);

	/* Configuracion general */
	this->setBackground(QUESTION_BACKGROUND);

	/* Pongo los botones visibles */
	yesButton->getModel()->setVisible(true);
	yesButton->getModel()->setEnable(true);
	noButton->getModel()->setVisible(true);
	noButton->getModel()->setEnable(true);
	label->getModel()->setVisible(true);
	label->getModel()->setEnable(true);
}

void
QuestionWindow::question(string msg, Action onYes, Action onNo) {

	/* Se configuran los callbacks de la respuesta, modifica
	* el texto actual del mensaje de mi amigo Gandalf, y luego
	* se activa la ventana.
	*/
	MODEL((*this)["message"], TextUI*)->setText(msg);
	MODEL((*this)["yesButton"], MouseUI*)->setClickAction(onYes);
	MODEL((*this)["noButton"], MouseUI*)->setClickAction(onNo);
	this->setEnable(true);
}