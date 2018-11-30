#include "SoundStatusView.h"

SoundStatusView::SoundStatusView(MouseUI * model_) : UIView(model_){
	samples.setConfig(MouseUI::Status::FOCUSED, DEFAULT_FOCUSED_SAMPLE);
	prevStatus = MouseUI::Status::IDLE;
}

void SoundStatusView::draw(void)
{
	if (model->getVisible())
	{
		MouseUI* pointer = (MouseUI*)model;
		MouseUI::Status currStatus = pointer->getStatus();
		if (currStatus != prevStatus)
		{
			if (samples.has(currStatus))
				al_play_sample(samples[currStatus].sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			prevStatus = currStatus;
		}
	}
}
