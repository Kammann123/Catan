#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_color.h"

#include "CatanGui/AllegroUI/MouseDecorator.h"
#include "CatanGui/AllegroUI/MouseController.h"

class BoxView : public Observer {
public:
	BoxView(UIModel* frame);

	void draw(void);
	virtual void update(void);
private:
	UIModel * frame;
};

int main(int argc, char** argv) {

	al_init();
	al_init_primitives_addon();
	al_install_mouse();

	ALLEGRO_DISPLAY* display = al_create_display(600, 600);

	al_clear_to_color(al_map_rgb(100, 100, 100));
	al_flip_display();

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());

	MouseDecorator myFrame = MouseDecorator(new FrameUI(100, 100, 50, 50), true);
	MouseController myController = MouseController(&myFrame);
	BoxView myView = BoxView(&myFrame);
	myFrame.attach(&myView);
	myView.draw();

	ALLEGRO_EVENT event;
	while (true) {
		if (al_get_next_event(queue, &event)) {
			myController.parse(&event);
		}
	}

	al_destroy_display(display);
}

BoxView::
BoxView(UIModel* frame) {
	this->frame = frame;
}

void
BoxView::update(void) {
	this->draw();
}

void
BoxView::draw(void) {

	MouseDecorator* decorator = (MouseDecorator*)frame;
	FrameUI* myFrame = (FrameUI*)decorator->getModel();

	ALLEGRO_COLOR background = al_map_rgb(255, 255, 255);

	switch (myFrame->getStatus()) {

		case FrameUI::Status::IDLE:
			background = al_map_rgb(255, 0, 0);
			break;

		case FrameUI::Status::FOCUSED:
			background = al_map_rgb(255, 255, 0);
			break;

		case FrameUI::Status::SELECTED:
			background = al_map_rgb(0, 255, 255);
			break;

		case FrameUI::Status::DRAGGED:
			background = al_map_rgb(255, 0, 255);
			break;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_filled_rectangle(
		myFrame->xPos(),
		myFrame->yPos(),
		myFrame->xPos() + myFrame->getWidth(),
		myFrame->yPos() + myFrame->getHeight(),
		background
	);

	al_flip_display();
}