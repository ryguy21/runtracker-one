#ifndef __LOG_H_
#define __LOG_H_

#include <pebble.h>

#include "../layers/song_text.h"

static void log_str(const char* msg)
{
	set_song_text(msg);
	text_layer_set_background_color(s_songtext_layer, GColorYellow);
}

static void log_num(const char* fmtMsg, int a)
{
	static char buffer[64];
	snprintf(buffer, 64, fmtMsg, a);
	log_str(buffer);
}

#endif
