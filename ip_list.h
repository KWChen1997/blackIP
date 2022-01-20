#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#define BUCKET_SIZE 3000


struct node {
	uint32_t ip;
	uint32_t mask; 
};

struct list {
	struct node *data;
	uint32_t count;
	uint32_t cap;
};

void node_print(struct node *node);

int list_init(struct list *list);
int list_insert(struct list *list, uint32_t ip, uint32_t mask);
int list_expand(struct list *list);
int list_match(struct list *list, uint32_t ip);
int list_clear(struct list *list);
int list_destroy(struct list *list);
void list_print(struct list *list);

uint32_t str2ip(char *sip);
uint32_t create_mask(unsigned int m);
int inrange(struct node *node, uint32_t ip);
