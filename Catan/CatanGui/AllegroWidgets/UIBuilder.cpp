#include "UIBuilder.h"

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