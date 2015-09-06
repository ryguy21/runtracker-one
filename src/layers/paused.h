#ifndef __PAUSED_H_
#define __PAUSED_H_

#include <pebble.h>

static Layer *s_paused_layer;

static BitmapLayer *s_stop_layer, *s_resume_layer, *s_skip_layer;
static GBitmap *s_stop_bitmap, *s_resume_bitmap, *s_skip_bitmap;

static void add_paused_layer(Window *window)
{
	layer_add_child(window_get_root_layer(window), s_paused_layer);
	layer_set_hidden(s_paused_layer, true);
}

static void show_paused_layer(bool show)
{
	layer_set_hidden(s_paused_layer, !show);
}

static void init_paused_layer()
{
	// main layer
	s_paused_layer = layer_create(GRect(114, 0, 27, 168));

	// resume icon
	s_resume_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PLAY);
	s_resume_layer = bitmap_layer_create(GRect(0, 10, 32, 32));
	bitmap_layer_set_compositing_mode(s_resume_layer, GCompOpSet);
	bitmap_layer_set_bitmap(s_resume_layer, s_resume_bitmap);
	layer_add_child(s_paused_layer, bitmap_layer_get_layer(s_resume_layer));

	// skip next icon
	s_skip_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEXT);
	s_skip_layer = bitmap_layer_create(GRect(0, 65, 32, 32));
	bitmap_layer_set_compositing_mode(s_skip_layer, GCompOpSet);
	bitmap_layer_set_bitmap(s_skip_layer, s_skip_bitmap);
	layer_add_child(s_paused_layer, bitmap_layer_get_layer(s_skip_layer));

	// stop icon
	s_stop_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_STOP);
	s_stop_layer = bitmap_layer_create(GRect(0, 120, 32, 32));
	bitmap_layer_set_compositing_mode(s_stop_layer, GCompOpSet);
	bitmap_layer_set_bitmap(s_stop_layer, s_stop_bitmap);
	layer_add_child(s_paused_layer, bitmap_layer_get_layer(s_stop_layer));
}

static void deinit_paused_layer()
{
	layer_destroy(s_paused_layer);

	gbitmap_destroy(s_resume_bitmap);
	gbitmap_destroy(s_stop_bitmap);
	gbitmap_destroy(s_skip_bitmap);

	bitmap_layer_destroy(s_resume_layer);
	bitmap_layer_destroy(s_stop_layer);
	bitmap_layer_destroy(s_skip_layer);
}

#endif
