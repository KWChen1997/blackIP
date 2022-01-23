#include "ip_list.h"

void node_print(struct node *node){
	unsigned char *ip = (unsigned char*)&node->ip;
	char sip[17] = {0};
	snprintf(sip,17,"%u.%u.%u.%u", ip[3], ip[2], ip[1], ip[0]); 
	printf("%-17s 0x%x\n", sip, node->mask);
	return;
}

int list_init(struct list *list){
	list->data = (struct node*)malloc(sizeof(struct node) * BUCKET_SIZE);
	if(list->data == NULL)
		return 1;
	list->cap = BUCKET_SIZE;
	list->count = 0;
	return 0;
}

int list_insert(struct list *list, uint32_t ip, uint32_t mask){
	int idx = list->count;
	list->data[idx].ip = ip;
	list->data[idx].mask = mask;
	list->count++;
	if(list->count == list->cap && list_expand(list))
		return 1;
	return 0;
}

int list_expand(struct list *list){
	list->data = (struct node*)realloc(list->data, sizeof(struct node) * (list->cap + BUCKET_SIZE));
	if(list->data == NULL)
		return 1;
	list->cap = list->cap + BUCKET_SIZE;
	return 0;
}

int list_match(struct list *list, uint32_t ip){
	int s = 0;
	int e = list->count;
	int mid = (s+e)/2;
	while(s != e){
		mid = (s+e)/2;
		if(inrange(list->data+mid,ip)){
			return 1;
		}
		if(s == mid)
			return 0;
		if(ip > list->data[mid].ip)
			s = mid;
		else
			e = mid;
	}
	return 0;
}

int list_clear(struct list *list){
	list->count = 0;
	return list->count;
}

int list_destroy(struct list *list){
	if(list->data){
		free(list->data);
		list->data = NULL;
	}

	return 0;
}

void list_print(struct list *list){
	int i = 0;
	for(i = 0; i < list->count; i++){
		node_print(list->data + i);
	}
	return;
}

uint32_t str2ip(char *sip){
	char tmp[17];
	char *token;
	uint32_t ip = 0;
	strncpy(tmp,sip,16);

	token = strtok(tmp,".");
	ip += atoi(token);
	while((token = strtok(NULL,".")) != NULL){
		ip = ip << 8;
		ip += atoi(token);
	}
	return ip;
}

int inrange(struct node *node, uint32_t ip){
	return (node->ip & node->mask) == (ip & node->mask);
}

uint32_t create_mask(unsigned int m){
	uint32_t mask = 0xffffffff;
	int i = 0;
	
	for(i = 0; i < 32 - m; i++){
		mask ^= (1 << i);
	}

	return mask;
}

