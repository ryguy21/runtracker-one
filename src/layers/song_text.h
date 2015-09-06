#ifndef __SONG_TEXT_H_
#define __SONG_TEXT_H_

#include <pebble.h>

static TextLayer *s_songtext_layer;
static GFont s_songtext_font;

static void set_song_text(const char* title)
{
	static char buffer[50];

	strcpy(buffer, title);

	text_layer_set_text(s_songtext_layer, buffer);
}

static void add_songtext_layer(Window *window)
{
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_songtext_layer));
}

static void init_songtext_layer()
{
	s_songtext_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IMPACT_18));
	s_songtext_layer = text_layer_create(GRect(3, 90, 117, 24));
	text_layer_set_background_color(s_songtext_layer, GColorClear);
	text_layer_set_text_color(s_songtext_layer, GColorBlack);
	text_layer_set_font(s_songtext_layer, s_songtext_font);
	text_layer_set_text_alignment(s_songtext_layer, GTextAlignmentLeft);
	set_song_text("Test song name");
}

static void deinit_songtext_layer()
{
	text_layer_destroy(s_songtext_layer);
	fonts_unload_custom_font(s_songtext_font);
}

#endif
