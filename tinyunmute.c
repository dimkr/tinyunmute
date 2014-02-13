#include <stdlib.h>
#include <tinyalsa/asoundlib.h>

/* the sound card ID */
#define CARD_ID (0)

int main() {
	/* the exit code */
	int exit_code = EXIT_FAILURE;

	/* the mixer */
	struct mixer *mixer;

	/* the number of mixer controls */
	unsigned int controls_count;

	/* a mixer control */
	struct mixer_ctl *control;

	/* the control type */
	enum mixer_ctl_type type;

	/* the number of control values */
	unsigned int values_count;

	/* loop counters */
	unsigned int i;
	unsigned int j;

	/* open the mixer */
	mixer = mixer_open(CARD_ID);
	if (NULL == mixer)
		goto end;

	/* get the number of controls */
	controls_count = mixer_get_num_ctls(mixer);

	for (i = 0; controls_count > i; ++i) {
		/* read the control information */
		control = mixer_get_ctl(mixer, i);
		type = mixer_ctl_get_type(control);
		values_count = mixer_ctl_get_num_values(control);

		/* ignore non-boolean controls */
		if (MIXER_CTL_TYPE_BOOL != type)
			continue;

		/* unmute the control */
		for (j = 0; values_count > j; ++j) {
			if (0 != mixer_ctl_set_value(control, j, 1))
				goto close_mixer;
		}
	}

	/* report success */
	exit_code = EXIT_SUCCESS;

close_mixer:
	/* close the mixer */
	mixer_close(mixer);

end:
	return exit_code;
}