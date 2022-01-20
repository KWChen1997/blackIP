#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <curl/curl.h>

#include "ip_list.h"

#define TARGET_URL "https://iplists.firehol.org/files/firehol_level1.netset"

void get_ip_list();
void request();
size_t readline(int fd, char *buf, int offset);
