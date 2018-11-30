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
createButton(string id, const char* focused, const char* selected, const char* idle, WindowUI* interface_)
{
	
	ALLEGRO_BITMAP* focusedBitmap = al_load_bitmap(focused);
	ALLEGRO_BITMAP* selectedBitmap = al_load_bitmap(selected);
	ALLEGRO_BITMAP* idleBitmap = al_load_bitmap(idle);

	UIComponent* ret = nullptr;

	if (focusedBitmap != nullptr && selectedBitmap != nullptr && idleBitmap != nullptr)
	{
		/* Creación del model */
		MouseUI* model = new MouseUI(id, al_get_bitmap_width(idleBitmap), al_get_bitmap_height(idleBitmap));

		/* Creación del controller */
		MouseController* controller = new MouseController(model);

		/* Creación del view */
		ButtonView* view = new ButtonView(focusedBitmap, selectedBitmap, idleBitmap, interface_, model);

		/* Attach model-view */
		model->attach(view);

		/* Creación del UIComponent */
		UIComponent* component = new UIComponent(model, view, { controller });

		ret = component;
	}

	return ret;

}

UIComponent* UIBuilder::
createTextField(ALLEGRO_FONT * font_, size_t width, size_t height, ALLEGRO_COLOR textColor_, WindowUI* interface_, string id, size_t size, TextUI::Mode mode) {

	/*Cracion del modelo*/
	TextUI * textFieldModel = new TextUI(id, width, height, size, mode);

	/*Cracion la View*/
	TextFieldView * textFieldView = new TextFieldView(font_, textColor_, textFieldModel, interface_);

	/*Attach modelo-vista*/
	textFieldModel->attach(textFieldView);

	/*Cracion el controller*/
	TextController * textController = new TextController(textFieldModel);
	MouseController * mouseController = new MouseController(textFieldModel);

	/* Creación del UIComponent */
	UIComponent* component = new UIComponent(textFieldModel, textFieldView, {textController, mouseController});

	return component;
}