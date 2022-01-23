#include "request.h"

int main(const int argc, char *argv[]){
	char ip[17]={0};
	struct list list;
	list_init(&list);
	get_ip_list(&list);
	list_clear(&list);
	get_ip_list(&list);
	//list_print(&list);
	while(1){
		printf("Search ip: ");
		scanf("%s", ip);
		if(ip[0] > '9' || ip[0] < '0')
			break;
		if(list_match(&list, str2ip(ip)))
			puts("hit");
		else
			puts("miss");
	}
	return 0;
}
