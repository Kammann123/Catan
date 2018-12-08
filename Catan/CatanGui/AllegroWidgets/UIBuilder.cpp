#include "UIBuilder.h"

#include "../AllegroWidgets/SimpleButtonView.h"
#include "../AllegroWidgets/ButtonView.h"
#include "../AllegroWidgets/TextFieldView.h"
#include "../AllegroWidgets/TextBoxView.h"
#include "../AllegroWidgets/LabelView.h"
#include "../AllegroWidgets/SoundStatusView.h"
#include "../AllegroWidgets/ImageView.h"
#include "../AllegroWidgets/CounterView.h"
#include "../AllegroWidgets/MultiLabelView.h"

#include "../AllegroUI/MouseUI.h"
#include "../AllegroUI/TextUI.h"
#include "../AllegroUI/ComponentConnector.h"
#include "../AllegroUI/CounterUI.h"
#include "../AllegroUI/WindowUI.h"

#include "../AllegroUI/MouseController.h"
#include "../AllegroUI/TextController.h"

/************************************
* Layout por defecto del CounterBox *
************************************/
#define PLUS_IMG	"CatanGui\\Buttons\\plusButton.png"
#define MINUS_IMG	"CatanGui\\Buttons\\minusButton.png"

/*********************************
* Layout por defecto del InfoBox *
*********************************/
#define INFO_FRAME	"CatanGui\\InfoBox\\frame_v3.png"
#define INFO_TITLE_FONT	"CatanGui\\Fonts\\RifficFree-Bold.ttf"
#define INFO_TITLE_SIZE	15
#define INFO_INFO_FONT "CatanGui\\Fonts\\NewAmsterdam.ttf"
#define INFO_INFO_SIZE	12
#define INFO_BUTTON		"CatanGui\\InfoBox\\button_v2.png"

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

UIComponent* 
UIBuilder::createCounter(string id, unsigned int max) {

	/* Creo el modelo */
	UIModel* counterModel = new CounterUI(id, max);

	/* Creo el view y hago un attach */
	UIView* counterView = new CounterView((CounterUI*)counterModel);
	counterModel->attach(counterView);

	/* Creo el component */
	UIComponent* counterComponent = new UIComponent(counterModel, { counterView }, {});
	return counterComponent;
}

UIComponent* 
UIBuilder::createCounterBox(string id, unsigned int max) {

	/* Creo el component */
	UIComponent* box = new UIComponent(id);

	/* Creo los subcomponents */
	UIComponent* plusButton = createButton(id + "_plus");
	UIComponent* counter = createCounter(id + "_counter", max);
	UIComponent* minusButton = createButton(id + "_minus");

	/* Configuro frames de botones */
	(*plusButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, PLUS_IMG);
	(*plusButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, PLUS_IMG);
	(*plusButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, PLUS_IMG);
	(*plusButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, PLUS_IMG);

	(*minusButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, MINUS_IMG);
	(*minusButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, MINUS_IMG);
	(*minusButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, MINUS_IMG);
	(*minusButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, MINUS_IMG);

	/* Configuro las posiciones relativas dentro del component */
	MODEL(plusButton, FrameUI*)->setPosition(0, 0);
	MODEL(counter, FrameUI*)->setPosition(30, 0);
	MODEL(minusButton, FrameUI*)->setPosition(60, 0);

	/* Agrego los subcomponents */
	box->attachComponent(plusButton);
	box->attachComponent(counter);
	box->attachComponent(minusButton);

	/* Creo los pipes o connectores :D !! */
	MODEL(plusButton, MouseUI*)->setClickAction(CREATE_CONNECTOR(unsigned int, std::bind(&CounterUI::plusValue, (CounterUI*)counter->getModel(), _1), 1));
	MODEL(minusButton, MouseUI*)->setClickAction(CREATE_CONNECTOR(unsigned int, std::bind(&CounterUI::minusValue, (CounterUI*)counter->getModel(), _1), 1));
	
	/* Devuelvo */
	return box;
}

UIComponent*
UIBuilder::createMultiLabel(string id, double width, double height){
	/* Creación de la View */
	MultiLabelView* labelView = new MultiLabelView();
	((MultiLabelView*)labelView)->setWidth(width);
	((MultiLabelView*)labelView)->setHeight(height);

	/* Creación del modelo */
	TextUI* labelModel = new TextUI(id, width, height);

	/*Attach modelo-vista*/
	labelModel->attach(labelView);
	labelView->setModel(labelModel);

	UIComponent* component = new UIComponent(labelModel, { labelView }, {});
	return component;
}

UIComponent* 
UIBuilder::createInfoBox(string id, size_t size, double width, double height) {

	/* Creo los components */
	UIComponent* frame = createImage(id + "_frame");
	UIComponent* title = createLabel(id + "_title", size);
	UIComponent* info = createMultiLabel(id + "_info", width, height);

	/* Creo el component container */
	UIComponent* infoBox = new UIComponent(id);

	/* Posiciones relativas */
	MODEL(frame, FrameUI*)->setPosition(0, 0);
	MODEL(title, TextUI*)->setPosition(35, 8);
	MODEL(info, TextUI*)->setPosition(15, 35);

	/* Configuro los subcomponentes */
	(*frame)[0]->getImages().setConfig(IV_BITMAP, INFO_FRAME);
	(*title)[0]->getColors().setConfig(LA_TEXT_COLOR, 240, 170, 100);
	(*title)[0]->getFonts().setConfig(LA_FONT, INFO_TITLE_FONT, INFO_TITLE_SIZE);
	(*info)[0]->getColors().setConfig(MLA_TEXT_COLOR, 220, 190, 150);
	(*info)[0]->getFonts().setConfig(MLA_FONT, INFO_INFO_FONT, INFO_INFO_SIZE);

	/* Attachment de subcomponents */
	infoBox->attachComponent(frame);
	infoBox->attachComponent(title);
	infoBox->attachComponent(info);

	/* Devuelvo */
	infoBox->refactor();
	return infoBox;
}

UIComponent* 
UIBuilder::createToggleInfoBox(string id, size_t size, double width, double height) {

	/* Creo los componentes */
	UIComponent* infoBox = createInfoBox(id + "_infobox", size, width, height);
	UIComponent* toggleButton = createButton(id + "_button");

	/* Creo el componente */
	UIComponent* toggleComponent = new UIComponent(id);

	/* Configuro los componentes */
	(*toggleButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, INFO_BUTTON);
	(*toggleButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, INFO_BUTTON);
	(*toggleButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, INFO_BUTTON);
	(*toggleButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, INFO_BUTTON);
	MODEL(infoBox, UIModel*)->setVisible(false);

	/* Configuro las posiciones relativas */
	MODEL(infoBox, UIModelContainer*)->setPosition(0, 5);
	MODEL(toggleButton, MouseUI*)->setPosition(125, 5);

	/* Hago un attachment de subcomponentes */
	toggleComponent->attachComponent(toggleButton);
	toggleComponent->attachComponent(infoBox);

	/* Connector... :D */
	MODEL(toggleButton, MouseUI*)->setFocusAction(CREATE_CONNECTOR(bool, bind(&UIModel::setVisible, infoBox->getModel(), _1), true));
	MODEL(toggleButton, MouseUI*)->setExitAction(CREATE_CONNECTOR(bool, bind(&UIModel::setVisible, infoBox->getModel(), _1), false));

	/* Devuelvo */
	return toggleComponent;
}