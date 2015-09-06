#ifndef __GPS_STATUS_H_
#define __GPS_STATUS_H_

#include <pebble.h>

#define GPS_AVAILABLE false

static BitmapLayer *s_gps_layer;
static GBitmap *s_gps_fixed_bitmap, *s_gps_lost_bitmap;

static bool s_connected;

static void set_gps_layer_visible(bool visible)
{
	layer_set_hidden(bitmap_layer_get_layer(s_gps_layer), !visible);
}

static void show_gps_status(bool connected, bool hide_if_connected)
{
#if GPS_AVAILABLE
	if (connected)
	{
		bitmap_layer_set_bitmap(s_gps_layer, s_gps_fixed_bitmap);
	}
	else
	{
		if (s_connected)
		{
			// lost connection!
			vibes_double_pulse();
		}

		bitmap_layer_set_bitmap(s_gps_layer, s_gps_lost_bitmap);
	}

	s_connected = connected;

	set_gps_layer_visible(!(connected && hide_if_connected));
#else
	set_gps_layer_visible(false);
#endif
}

static bool get_gps_status()
{
	return s_connected;
}

static void add_gps_layer(Window *window)
{
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_gps_layer));
}

static void init_gps_layer()
{
	s_gps_fixed_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GPS_FIXED);
	s_gps_lost_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GPS_LOST);
    s_gps_layer = bitmap_layer_create(GRect(45, 125, 32, 32));
	bitmap_layer_set_compositing_mode(s_gps_layer, GCompOpSet);

	s_connected = false;
	show_gps_status(false, false);
}

static void deinit_gps_layer()
{
	gbitmap_destroy(s_gps_fixed_bitmap);
	gbitmap_destroy(s_gps_lost_bitmap);
	bitmap_layer_destroy(s_gps_layer);
}

#endif
