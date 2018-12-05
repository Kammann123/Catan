#include "SoundStatusView.h"

SoundStatusView::SoundStatusView(MouseUI * model_) : UIView(model_){
	prevStatus = MouseUI::Status::IDLE;
	isPlaying = false;
}

void SoundStatusView::draw(void)
{
	if (model->getVisible())
	{
		MouseUI* pointer = (MouseUI*)model;
		MouseUI::Status currStatus = pointer->getStatus();

		/* Si hubo cambio de estado */
		if (currStatus != prevStatus)
		{
			/* Cambio estado */
			prevStatus = currStatus;

			/* Me fijo si hay un sonido */
			if (samples.has(currStatus)) {

				/* Me fijo si tengo que parar algo */
				if (isPlaying) {
					al_stop_sample(&music);
				}
				else {
					isPlaying = true;
				}

				/* Pongo nuevo sonido */
				al_play_sample(samples[currStatus].sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &music);
			}
		}
	}
}