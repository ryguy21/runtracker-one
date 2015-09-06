#ifndef __STRAP_H_
#define __STRAP_H_

#include <pebble.h>

#include "../layers/song_text.h"
#include "../layers/timer.h"

#define SERVICE_ID					0x1021
#define COMMAND_ID					0x0001
#define SONG_TITLE_ID				0x0002
#define COMMAND_BUFFER_LENGTH		1
#define SONG_TITLE_BUFFER_LENGTH	256

#define COMMAND_START				0x01
#define COMMAND_STOP				0x02
#define COMMAND_PAUSE				0x04
#define COMMAND_RESUME				0x08
#define COMMAND_SKIP_FORWARD		0x10
#define COMMAND_SKIP_BACKWARD		0x20
#define COMMAND_VOLUME_UP			0x40
#define COMMAND_VOLUME_DOWN			0x80

SmartstrapAttribute *command_attr;
SmartstrapAttribute *song_name_attr;

static void write_command(uint8_t command)
{
	// Pointer to the attribute buffer
	size_t buff_size;
	uint8_t *buffer;

	// Begin the write request, getting the buffer and its length
	smartstrap_attribute_begin_write(command_attr, &buffer, &buff_size);

	// Write to the buffer
	buffer[0] = command;

	// End the write request, and send the data, not expecting a response
	smartstrap_attribute_end_write(command_attr, buff_size, false);
}

static void update_song_title()
{
	smartstrap_attribute_read(song_name_attr);
}

static void start()
{
	write_command(COMMAND_START);
}

static void pause()
{
	write_command(COMMAND_PAUSE);
}

static void resume()
{
	write_command(COMMAND_RESUME);
}

static void stop()
{
	write_command(COMMAND_STOP);
}

static void skip_forward()
{
	write_command(COMMAND_SKIP_FORWARD);
}

static void skip_backward()
{
	write_command(COMMAND_SKIP_BACKWARD);
}

static void volume_up()
{
	write_command(COMMAND_VOLUME_UP);
}

static void volume_down()
{
	write_command(COMMAND_VOLUME_DOWN);
}

static void strap_availability_handler(SmartstrapServiceId service_id,
	bool is_available)
{
	// A service's availability has changed
	if (service_id == SERVICE_ID)
	{
		set_connection_status(is_available);
	}
}

static void strap_write_handler(SmartstrapAttribute *attribute,
	SmartstrapResult result)
{
	// A write operation has been attempted
	if(result == SmartstrapResultOk)
	{
		// The write was successful!
	}
	else
	{
		// Handle the failure
	}
}

static void strap_read_handler(SmartstrapAttribute *attribute, SmartstrapResult result, const uint8_t *data, size_t length)
{
	if (result != SmartstrapResultOk)
	{
		return;
	}

	if (attribute == song_name_attr)
	{
		char buffer[256];
		strcpy(buffer, (char*)data);
		set_song_text(buffer);
	}
}

static void strap_notified_handler(SmartstrapAttribute *attribute)
{
	if (attribute == song_name_attr)
	{
		update_song_title();
	}
}

static void init_strap()
{
	command_attr = smartstrap_attribute_create(SERVICE_ID, COMMAND_ID, COMMAND_BUFFER_LENGTH);
	song_name_attr = smartstrap_attribute_create(SERVICE_ID, SONG_TITLE_ID, SONG_TITLE_BUFFER_LENGTH);

	smartstrap_subscribe((SmartstrapHandlers) {
		.availability_did_change = strap_availability_handler,
		.did_write = strap_write_handler,
		.did_read = strap_read_handler,
		.notified = strap_notified_handler
	});

	set_connection_status(smartstrap_service_is_available(SERVICE_ID));
}

static void deinit_strap()
{
	smartstrap_unsubscribe();
	smartstrap_attribute_destroy(command_attr);
	smartstrap_attribute_destroy(song_name_attr);
}

#endif
