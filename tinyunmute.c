#include <stdlib.h>
#include <tinyalsa/asoundlib.h>

/* the sound card ID */
#define CARD_ID (0)

int main() {
	/* the exit code */
	int exit_code = EXIT_FAILURE;

	/* the number of mixer controls */
	unsigned int controls_count = 0;

	/* the control type */
	enum mixer_ctl_type type = MIXER_CTL_TYPE_BOOL;

	/* the number of control values */
	unsigned int values_count = 0;

	/* a control value */
	int value = 0;

	/* loop counters */
	unsigned int i = 0;
	unsigned int j = 0;

	/* a mixer control */
	struct mixer_ctl *control = NULL;

	/* the mixer */
	struct mixer *mixer = NULL;

	/* open the mixer */
	mixer = mixer_open(CARD_ID);
	if (NULL == mixer) {
		goto end;
	}

	/* get the number of controls */
	controls_count = mixer_get_num_ctls(mixer);

	for ( ; controls_count > i; ++i) {
		/* read the control information */
		control = mixer_get_ctl(mixer, i);
		type = mixer_ctl_get_type(control);

		/* decide which value to assign */
		switch (type) {
			case MIXER_CTL_TYPE_BOOL:
				value = 1;
				break;

			case MIXER_CTL_TYPE_INT:
				value = 50;
				break;

			default:
				continue;
		}

		/* unmute the control */
		values_count = mixer_ctl_get_num_values(control);
		for (j = 0; values_count > j; ++j) {
			if (0 == mixer_ctl_set_value(control, j, value)) {
				exit_code = EXIT_SUCCESS;
			}
		}
	}

	/* close the mixer */
	mixer_close(mixer);

end:
	return exit_code;
}
