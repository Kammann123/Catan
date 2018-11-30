#include "UIBuilder.h"

#include "../AllegroWidgets/SimpleButtonView.h"
#include "../AllegroWidgets/ButtonView.h"
#include "../AllegroWidgets/TextFieldView.h"

#include "../AllegroUI/MouseUI.h"
#include "../AllegroUI/TextUI.h"

#include "../AllegroUI/MouseController.h"
#include "../AllegroUI/TextController.h"

UIComponent* UIBuilder::
createSimpleButton(string id, const char* text, size_t height) {

	/* Construyo el view primero, para tener la informacion
	* del font y asi configurarle correctamente un width
	*/
	SimpleButtonView* buttonView = new SimpleButtonView();

	/* Construyo el model del button */
	TextUI* buttonModel = new TextUI(id, al_get_text_width(buttonView->setColors()[SIMPLE_BUTTON_TEXTFONT].font, text), height, strlen(text));

	/* Construyo los controllers, y hago los attachs */
	MouseController* buttonController = new MouseController(buttonModel);
	buttonView->setModel(buttonModel);
	buttonModel->attach(buttonView);
	
	/* Creo el UIComponent y lo devuelvo */
	UIComponent* component = new UIComponent(buttonModel, buttonView, { buttonController });
	return component;
}

UIComponent* UIBuilder::
createButton(string id)
{
	
		/* Creación del view */
		ButtonView* view = new ButtonView();

		/* Creación del model */
		MouseUI* model = new MouseUI(id, 
									al_get_bitmap_width(view->setImages()[(unsigned int)MouseUI::Status::IDLE].bitmap), 
									al_get_bitmap_height(view->setImages()[(unsigned int)MouseUI::Status::IDLE].bitmap)
									);

		/* Attach model-view */
		model->attach(view);
		view->setModel(model);

		/* Creación del controller */
		MouseController* controller = new MouseController(model);

		/* Creación del UIComponent */
		UIComponent* component = new UIComponent(model, view, { controller });

		return component;


}

UIComponent* UIBuilder::
createTextField(size_t height, string id, size_t size, TextUI::Mode mode) {

	/*Cracion de la View*/
	TextFieldView * textFieldView = new TextFieldView();

	string test(size, 'A'); 

	/*Cracion del modelo*/
	TextUI * textFieldModel = new TextUI(id, al_get_text_width(textFieldView->setFonts()[TF_FONT].font,test.c_str()), height, size, mode);


	/*Attach modelo-vista*/
	textFieldModel->attach(textFieldView);
	textFieldView->setModel(textFieldModel);

	/*Cracion el controller*/
	TextController * textController = new TextController(textFieldModel);
	MouseController * mouseController = new MouseController(textFieldModel);

	/* Creación del UIComponent */
	UIComponent* component = new UIComponent(textFieldModel, textFieldView, {textController, mouseController});

	return component;
}