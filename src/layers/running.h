#ifndef __RUNNING_H_
#define __RUNNING_H_

#include <pebble.h>

static Layer *s_running_layer;

static BitmapLayer *s_vol_up_layer, *s_vol_dn_layer, *s_pause_layer;
static GBitmap *s_vol_up_bitmap, *s_vol_dn_bitmap, *s_pause_bitmap;

static void add_running_layer(Window *window)
{
	layer_add_child(window_get_root_layer(window), s_running_layer);
	layer_set_hidden(s_running_layer, true);
}

static void show_running_layer(bool show)
{
	layer_set_hidden(s_running_layer, !show);
}

static void init_running_layer()
{
	// main layer
	s_running_layer = layer_create(GRect(114, 0, 27, 168));

	// pause icon
	s_pause_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PAUSE);
	s_pause_layer = bitmap_layer_create(GRect(0, 65, 32, 32));
	bitmap_layer_set_compositing_mode(s_pause_layer, GCompOpSet);
	bitmap_layer_set_bitmap(s_pause_layer, s_pause_bitmap);
	layer_add_child(s_running_layer, bitmap_layer_get_layer(s_pause_layer));

	// volume up icon
	s_vol_up_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VOLUME_UP);
	s_vol_up_layer = bitmap_layer_create(GRect(0, 10, 32, 32));
	bitmap_layer_set_compositing_mode(s_vol_up_layer, GCompOpSet);
	bitmap_layer_set_bitmap(s_vol_up_layer, s_vol_up_bitmap);
	layer_add_child(s_running_layer, bitmap_layer_get_layer(s_vol_up_layer));

	// volume down icon
	s_vol_dn_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VOLUME_DOWN);
	s_vol_dn_layer = bitmap_layer_create(GRect(0, 120, 32, 32));
	bitmap_layer_set_compositing_mode(s_vol_dn_layer, GCompOpSet);
	bitmap_layer_set_bitmap(s_vol_dn_layer, s_vol_dn_bitmap);
	layer_add_child(s_running_layer, bitmap_layer_get_layer(s_vol_dn_layer));
}

static void deinit_running_layer()
{
	layer_destroy(s_running_layer);

	gbitmap_destroy(s_pause_bitmap);
	gbitmap_destroy(s_vol_up_bitmap);
	gbitmap_destroy(s_vol_dn_bitmap);

	bitmap_layer_destroy(s_pause_layer);
	bitmap_layer_destroy(s_vol_up_layer);
	bitmap_layer_destroy(s_vol_dn_layer);
}

#endif
