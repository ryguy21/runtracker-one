#include <pebble.h>

#include "comm/log.h"
#include "layers/timer.h"
#include "layers/song_text.h"
#include "layers/gps_status.h"
#include "layers/stopped.h"
#include "layers/running.h"
#include "layers/paused.h"

#include "comm/strap.h"

#define STOPPED_WINDOW 1
#define RUNNING_WINDOW 2
#define PAUSED_WINDOW 3

static Window *s_main_window;

static int s_current_window;

static void set_current_window(int window)
{
    s_current_window = window;
    show_stopped_layer(window == STOPPED_WINDOW);
    show_running_layer(window == RUNNING_WINDOW);
    show_paused_layer(window == PAUSED_WINDOW);

    bool connected = get_gps_status();
    switch (window)
    {
        case STOPPED_WINDOW:
            show_gps_status(connected, false);
            break;
        case RUNNING_WINDOW:
            show_gps_status(connected, true);
            break;
        case PAUSED_WINDOW:
            show_gps_status(connected, false);
            break;
    }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
    switch (s_current_window)
    {
        case STOPPED_WINDOW:
            skip_forward();
            break;
        case RUNNING_WINDOW:
            volume_up();
            break;
        case PAUSED_WINDOW:
            set_current_window(RUNNING_WINDOW);
            resume();
            break;
    }
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
    switch (s_current_window)
    {
        case STOPPED_WINDOW:
            set_current_window(RUNNING_WINDOW);
            start();
            break;
        case RUNNING_WINDOW:
            set_current_window(PAUSED_WINDOW);
            pause();
            break;
        case PAUSED_WINDOW:
            skip_forward();
            break;
    }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
    switch (s_current_window)
    {
        case STOPPED_WINDOW:
            skip_backward();
            break;
        case RUNNING_WINDOW:
            volume_down();
            break;
        case PAUSED_WINDOW:
            set_current_window(STOPPED_WINDOW);
            stop();
            break;
    }
}

static void up_long_click_handler(ClickRecognizerRef recognizer, void *context)
{
    switch (s_current_window)
    {
        case STOPPED_WINDOW:
            // do nothing
            break;
        case RUNNING_WINDOW:
            skip_forward();
            break;
        case PAUSED_WINDOW:
            // do nothing
            break;
    }
}

static void down_long_click_handler(ClickRecognizerRef recognizer, void *context)
{
    switch (s_current_window)
    {
        case STOPPED_WINDOW:
            // do nothing
            break;
        case RUNNING_WINDOW:
            skip_backward();
            break;
        case PAUSED_WINDOW:
            // do nothing
            break;
    }
}

static void init_layers()
{
    init_timer_layer();
    init_songtext_layer();
    init_gps_layer();
    init_stopped_layer();
    init_running_layer();
    init_paused_layer();
}

static void init_comm()
{
    init_strap();
}

static void main_window_load(Window *window)
{
    init_layers();
    init_comm();

    add_timer_layer(window);
    add_songtext_layer(window);
    add_gps_layer(window);

    add_stopped_layer(window);
    add_running_layer(window);
    add_paused_layer(window);

    set_current_window(STOPPED_WINDOW);
}

static void deinit_layers()
{
    deinit_timer_layer();
    deinit_songtext_layer();
    deinit_gps_layer();
    deinit_stopped_layer();
    deinit_running_layer();
    deinit_paused_layer();
}

static void deinit_comm()
{
    deinit_strap();
}

static void main_window_unload(Window *window)
{
    deinit_layers();
    deinit_comm();
}

static void click_config_provider(void *context)
{
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);

    uint16_t delay_ms = 750;

    window_long_click_subscribe(BUTTON_ID_UP, delay_ms, up_long_click_handler, NULL);
    window_long_click_subscribe(BUTTON_ID_DOWN, delay_ms, down_long_click_handler, NULL);
}

static void init()
{
    s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload
    });

    window_set_click_config_provider(s_main_window, click_config_provider);
    window_stack_push(s_main_window, true);
}

static void deinit()
{
    window_destroy(s_main_window);
}

int main(void)
{
    init();
    app_event_loop();
    deinit();
}
