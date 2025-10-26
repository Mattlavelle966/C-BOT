#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <linux/uinput.h>
#include <sys/ioctl.h>

// Helper to send one input event
void emit(int fd, int type, int code, int val) {
    struct input_event ie;
    memset(&ie, 0, sizeof(ie));
    ie.type = type;
    ie.code = code;
    ie.value = val;
    write(fd, &ie, sizeof(ie));
}

// Simple function to press and release a key
void press_key(int fd, int keycode) {
    emit(fd, EV_KEY, keycode, 1);   // key down
    emit(fd, EV_SYN, SYN_REPORT, 0);
    usleep(20000);
    emit(fd, EV_KEY, keycode, 0);   // key up
    emit(fd, EV_SYN, SYN_REPORT, 0);
    usleep(20000);
}

int main(void) {
    // Open uinput device (must run with sudo if /dev/uinput is root-owned)
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0) { perror("open"); return 1; }
    sleep(5);
    // Enable keyboard events
    ioctl(fd, UI_SET_EVBIT, EV_KEY);

    // Enable letters we’ll use
    ioctl(fd, UI_SET_KEYBIT, KEY_H);
    ioctl(fd, UI_SET_KEYBIT, KEY_E);
    ioctl(fd, UI_SET_KEYBIT, KEY_L);
    ioctl(fd, UI_SET_KEYBIT, KEY_O);

    // Describe our virtual keyboard
    struct uinput_user_dev uidev;
    memset(&uidev, 0, sizeof(uidev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "hello-bot");
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor  = 0x1234;
    uidev.id.product = 0x5678;
    uidev.id.version = 1;

    // Create the virtual device
    write(fd, &uidev, sizeof(uidev));
    ioctl(fd, UI_DEV_CREATE);
    usleep(100000);  // wait a bit for device to register

    // Type “hello”
    press_key(fd, KEY_H);
    press_key(fd, KEY_E);
    press_key(fd, KEY_L);
    press_key(fd, KEY_L);
    press_key(fd, KEY_O);

    // Wait before cleaning up
    sleep(1);

    // Destroy the virtual keyboard
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
    return 0;
}

