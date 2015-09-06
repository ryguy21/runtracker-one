#ifndef __STOPPED_H_
#define __STOPPED_H_

#include <pebble.h>

static Layer *s_stopped_layer;

static BitmapLayer *s_skip_fwd_layer, *s_skip_bwd_layer;
static GBitmap *s_next_bitmap, *s_prev_bitmap;

static TextLayer *s_go_text_layer;
static GFont *s_go_font;

static void add_stopped_layer(Window *window)
{
	layer_add_child(window_get_root_layer(window), s_stopped_layer);
	layer_set_hidden(s_stopped_layer, true);
}

static void show_stopped_layer(bool show)
{
	layer_set_hidden(s_stopped_layer, !show);
}

static void init_stopped_layer()
{
	// main layer
	s_stopped_layer = layer_create(GRect(115, 0, 27, 168));

	// GO icon
	s_go_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IMPACT_21));
	s_go_text_layer = text_layer_create(GRect(2, 71, 27, 27));
	text_layer_set_background_color(s_go_text_layer, GColorClear);
	text_layer_set_text_color(s_go_text_layer, GColorBlack);
	text_layer_set_font(s_go_text_layer, s_go_font);
	text_layer_set_text_alignment(s_go_text_layer, GTextAlignmentCenter);
	text_layer_set_text(s_go_text_layer, "GO");
	layer_add_child(s_stopped_layer, text_layer_get_layer(s_go_text_layer));

	// NEXT icon
	s_next_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEXT);
	s_skip_fwd_layer = bitmap_layer_create(GRect(0, 10, 32, 32));
	bitmap_layer_set_compositing_mode(s_skip_fwd_layer, GCompOpSet);
	bitmap_layer_set_bitmap(s_skip_fwd_layer, s_next_bitmap);
	layer_add_child(s_stopped_layer, bitmap_layer_get_layer(s_skip_fwd_layer));

	// PREV icon
	s_prev_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PREV);
	s_skip_bwd_layer = bitmap_layer_create(GRect(0, 120, 32, 32));
	bitmap_layer_set_compositing_mode(s_skip_bwd_layer, GCompOpSet);
	bitmap_layer_set_bitmap(s_skip_bwd_layer, s_prev_bitmap);
	layer_add_child(s_stopped_layer, bitmap_layer_get_layer(s_skip_bwd_layer));
}

static void deinit_stopped_layer()
{
	layer_destroy(s_stopped_layer);

	text_layer_destroy(s_go_text_layer);
	fonts_unload_custom_font(s_go_font);

	gbitmap_destroy(s_next_bitmap);
	gbitmap_destroy(s_prev_bitmap);

	bitmap_layer_destroy(s_skip_fwd_layer);
	bitmap_layer_destroy(s_skip_bwd_layer);
}

#endif
