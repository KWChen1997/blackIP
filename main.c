#include "request.h"

int main(const int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Usage: ./blackIP <IP>\n");
		return 1;
	}
	struct list list;
	list_init(&list);
	get_ip_list(&list);
	//list_print(&list);
	if(list_match(&list, str2ip(argv[1])))
		puts("hit");
	else
		puts("miss");
	return 0;
}
