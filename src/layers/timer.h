#ifndef __TIMER_H_
#define __TIMER_H_

#include <pebble.h>

static TextLayer *s_timer_layer;
static GFont s_timer_font;

static void set_timer_time(int seconds)
{
	time_t temp = seconds;
	static char buffer[] = "00:00";
    struct tm *tick_time = gmtime(&temp);

	strftime(buffer, sizeof("00:00"), "%M:%S", tick_time);
	text_layer_set_text(s_timer_layer, buffer);
}

static void set_connection_status(bool connected)
{
	if (connected)
	{
		text_layer_set_background_color(s_timer_layer, GColorGreen);
	}
	else
	{
		text_layer_set_background_color(s_timer_layer, GColorRed);
	}
}

static void add_timer_layer(Window *window)
{
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_timer_layer));
}

static void init_timer_layer()
{
	s_timer_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IMPACT_44));
	s_timer_layer = text_layer_create(GRect(6, 20, 108, 50));
	text_layer_set_background_color(s_timer_layer, GColorClear);
	text_layer_set_text_color(s_timer_layer, GColorBlack);
	text_layer_set_font(s_timer_layer, s_timer_font);
	text_layer_set_text_alignment(s_timer_layer, GTextAlignmentCenter);
	set_timer_time(0);
}

static void deinit_timer_layer()
{
	text_layer_destroy(s_timer_layer);
	fonts_unload_custom_font(s_timer_font);
}

#endif
