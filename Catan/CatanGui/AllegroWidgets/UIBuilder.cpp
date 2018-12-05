#include "UIBuilder.h"

#include "../AllegroWidgets/SimpleButtonView.h"
#include "../AllegroWidgets/ButtonView.h"
#include "../AllegroWidgets/TextFieldView.h"
#include "../AllegroWidgets/TextBoxView.h"
#include "../AllegroWidgets/LabelView.h"
#include "../AllegroWidgets/SoundStatusView.h"
#include "../AllegroWidgets/ImageView.h"

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
	TextUI* buttonModel = new TextUI(id, 2 * PADDING_X + al_get_text_width(buttonView->getFonts()[SIMPLE_BUTTON_TEXTFONT].font, text), height, strlen(text));
	buttonModel->setText(text);

	/* Construyo los controllers, y hago los attachs */
	MouseController* buttonController = new MouseController(buttonModel);
	buttonView->setModel(buttonModel);
	buttonModel->attach(buttonView);
	
	/* Creo el UIComponent y lo devuelvo */
	UIComponent* component = new UIComponent(buttonModel, { buttonView }, { buttonController });
	return component;
}

UIComponent* UIBuilder::
createButton(string id)
{
	
		/* Creación del view */
		ButtonView* view = new ButtonView();

		/* Creación del model */
		MouseUI* model = new MouseUI(id, 
									al_get_bitmap_width(view->getImages()[(unsigned int)MouseUI::Status::IDLE].bitmap), 
									al_get_bitmap_height(view->getImages()[(unsigned int)MouseUI::Status::IDLE].bitmap)
									);

		/* Attach model-view */
		model->attach(view);
		view->setModel(model);

		/* Creación del controller */
		MouseController* controller = new MouseController(model);

		/* Creación del UIComponent */
		UIComponent* component = new UIComponent(model, { view }, { controller });

		return component;
}

UIComponent* UIBuilder::
createTextField(string id, size_t size, TextUI::Mode mode) {

	/*Cracion de la View*/
	TextFieldView * textFieldView = new TextFieldView();

	string test(size, 'A'); 

	/*Cracion del modelo*/
	TextUI * textFieldModel = new TextUI(id, TF_PADDING_X * 2 + al_get_text_width(textFieldView->getFonts()[TF_FONT].font,test.c_str()), TF_PADDING_Y * 2 + al_get_font_line_height(textFieldView->getFonts()[TF_FONT].font), size, mode);

	/*Attach modelo-vista*/
	textFieldModel->attach(textFieldView);
	textFieldView->setModel(textFieldModel);

	/*Cracion el controller*/
	TextController * textController = new TextController(textFieldModel);
	MouseController * mouseController = new MouseController(textFieldModel);

	/* Creación del UIComponent */
	UIComponent* component = new UIComponent(textFieldModel, { textFieldView }, { textController, mouseController });

	return component;
}

UIComponent* UIBuilder::
createTextBox(string id, size_t size, TextUI::Mode mode)
{
	/*Cracion de la View*/
	TextBoxView * textBoxView = new TextBoxView();

	/*Cracion del modelo*/
	TextUI * textBoxModel = new TextUI(id,
		al_get_bitmap_width(textBoxView->getImages()[MouseUI::Status::IDLE].bitmap),
		al_get_bitmap_height(textBoxView->getImages()[MouseUI::Status::IDLE].bitmap),
		size, mode);


	/*Attach modelo-vista*/
	textBoxModel->attach(textBoxView);
	textBoxView->setModel(textBoxModel);

	/*Cracion el controller*/
	TextController * textController = new TextController(textBoxModel);
	MouseController * mouseController = new MouseController(textBoxModel);

	/* Creación del UIComponent */
	UIComponent* component = new UIComponent(textBoxModel, { textBoxView }, { textController, mouseController });

	return component;
}

UIComponent* UIBuilder::
createLabel(string id, size_t size)
{
	/* Creación de la View */
	LabelView* labelView = new LabelView();

	string test(size, 'A');

	/* Creación del modelo */
	TextUI* labelModel = new TextUI(id, TF_PADDING_X * 2 + al_get_text_width(labelView->getFonts()[TF_FONT].font, test.c_str()), TF_PADDING_Y * 2 + al_get_font_line_height(labelView->getFonts()[TF_FONT].font), size, TextUI::EVERYTHING);

	/*Attach modelo-vista*/
	labelModel->attach(labelView);
	labelView->setModel(labelModel);

	UIComponent* component = new UIComponent(labelModel, { labelView }, {});
	return component;
}

UIComponent * UIBuilder::attachSample(UIComponent * component)
{
	SoundStatusView * soundView = new SoundStatusView((MouseUI *)(component)->getModel());
	(component)->getModel()->attach(soundView);
	component->appendView(soundView);
	return component;
}

UIComponent* UIBuilder::
createImage(string id)
{
	/* Creación de la view */
	ImageView* imageView = new ImageView();

	/* Creación del modelo */
	FrameUI* imageModel = new FrameUI(id, 0, 0);

	/* Attach modelo-vista */
	imageModel->attach(imageView);
	imageView->setModel(imageModel);

	UIComponent* component = new UIComponent(imageModel, { imageView }, {});
	return component;
}