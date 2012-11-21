#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static char brightness_path[] = "/sys/devices/platform/s3c24xx-pwm.0/pwm-backlight.0/backlight/pwm-backlight.0/brightness";

#ifdef BRIGHTNESS_UP
  #define INCREMENT 25
#endif

#ifdef BRIGHTNESS_DOWN
  #define INCREMENT -25
#endif

int main(int argc, char **argv) {
  char brightness_string[4];
  int brightness;
  size_t read;
  int ret;
  FILE *fp = fopen(brightness_path, "r+");
  if (fp == NULL) {
    printf("FAILED to open file (%d, %d).\n", 0, errno);
    return -1;
  }
  
  read = fread(brightness_string, 1, 4, fp);
  if (read > 4) {
    printf("FAILED to read file (%d, %d).\n", read, errno);
    fclose(fp);
    return -2;
  }

  brightness = atoi(brightness_string);
  if (brightness < 0 || brightness > 255) {
    printf("Unexpected brightness value: %d.\n", brightness);
    fclose(fp);
    return -3;
  }

  brightness += INCREMENT;
  if (brightness > 255) {
    brightness = 255;
  }

  if (brightness < 0) {
    brightness = 0;
  }

  ret = snprintf(brightness_string, 4, "%d", brightness);
  if (ret < 0) {
    printf("FAILED to convert brightness to string (%d, %d).\n", ret, errno);
    fclose(fp);
    return -4;
  }

  rewind(fp);
  read = fwrite(brightness_string, 1, 4, fp);
  if (read != strlen(brightness_string) + 1) {
    printf("FAILED to write file (%d, %d).\n", read, errno);
    fclose(fp);
    return -5;
  }

  printf("new brightness: %s\n", brightness_string);

  fclose(fp);
  return 0;
}
