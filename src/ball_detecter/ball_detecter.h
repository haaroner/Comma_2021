#include "project_config.h"
#include "pin_setup.h"

class ball_detecter
{
public:
	ball_detecter(pin &ball_led,
					pin &ball_phototransistor);
	bool getData();
};