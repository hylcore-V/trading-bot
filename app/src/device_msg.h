#ifndef SC_DEVICEMSG_H
#define SC_DEVICEMSG_H

#include "common.h"

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#define DEVICE_MSG_MAX_SIZE (1 << 18) // 256k
// type: 1 byte; length: 4 bytes
#define DEVICE_MSG_TEXT_MAX_LENGTH (DEVICE_MSG_MAX_SIZE - 5)

enum sc_device_msg_type {
    DEVICE_MSG_TYPE_CLIPBOARD,
    DEVICE_MSG_TYPE_ACK_CLIPBOARD,
};

struct sc_device_msg {
    enum sc_device_msg_type type;
    union {
        struct {
            char *text; // owned, to be freed by free()
        } clipboard;
        struct {
            uint64_t sequence;
        } ack_clipboard;
    };
};

// return the number of bytes consumed (0 for no msg available, -1 on error)
ssize_t
sc_device_msg_deserialize(const uint8_t *buf, size_t len,
                          struct sc_device_msg *msg);

void
sc_device_msg_destroy(struct sc_device_msg *msg);

#endif
