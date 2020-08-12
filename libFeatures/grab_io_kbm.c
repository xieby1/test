// Copy from https://gist.github.com/matthewaveryusa/a721aad80ae89a5c69f7c964fa20fec1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <time.h>
#include <stdint.h>

int main(int argc, char* argv[]){ 
  sleep(1);
  int rcode = 0;

  char keyboard_name[256] = "Unknown";
  int keyboard_fd = open("/dev/input/event1", O_RDONLY | O_NONBLOCK);
  if ( keyboard_fd == -1 ) {
    printf("Failed to open keyboard.\n");
    exit(1);
  }
  rcode = ioctl(keyboard_fd, EVIOCGNAME(sizeof(keyboard_name)), keyboard_name);
  printf("Reading From : %s \n", keyboard_name);

  printf("Getting exclusive access: ");
  rcode = ioctl(keyboard_fd, EVIOCGRAB, 1);
  printf("%s\n", (rcode == 0) ? "SUCCESS" : "FAILURE");
  struct input_event keyboard_event;
  
  char mouse_name[256] = "Unknown";
  int mouse_fd = open("/dev/input/event2", O_RDONLY | O_NONBLOCK);
  if ( mouse_fd == -1 ) {
    printf("Failed to open mouse.\n");
    exit(1);
  }
  rcode = ioctl(mouse_fd, EVIOCGNAME(sizeof(mouse_name)), mouse_name);
  printf("Reading From : %s \n", mouse_name);

  printf("Getting exclusive access: ");
  rcode = ioctl(mouse_fd, EVIOCGRAB, 1);
  printf("%s\n", (rcode == 0) ? "SUCCESS" : "FAILURE");
  struct input_event mouse_event;
  
  int end = time(NULL) + 10;
  while ( time(NULL) < end ) {
    if ( read(keyboard_fd, &keyboard_event, sizeof(keyboard_event)) != -1 ) {
      printf("keyboard event: type %d code %d value %d  \n", keyboard_event.type, keyboard_event.code, keyboard_event.value);
    }
    int sz;
    if (sz = read(mouse_fd, &mouse_event, sizeof(mouse_event)) ) {
      if(sz != -1) {
      printf("mouse event: type %d code %d value %d  \n", mouse_event.type, mouse_event.code, mouse_event.value);
      }
    }
  }

  printf("Exiting.\n");
  rcode = ioctl(keyboard_fd, EVIOCGRAB, 1);
  close(keyboard_fd);
  rcode = ioctl(mouse_fd, EVIOCGRAB, 1);
  close(mouse_fd);
  return 0;
}
