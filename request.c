#include "request.h"

void get_ip_list(struct list *list){
	pid_t pid;
	int fd[2];
	int status;
	pipe(fd);
	if( (pid = fork()) < 0){
		perror("Failed to fork()");
		exit(1);
	}
	
	if(pid == 0){
		close(fd[0]);
		dup2(fd[1],1);
		
		request();
		exit(0);
	}
	close(fd[1]);

	char buf[1024];
	char *ip_token;
	char *mask_token;
	if(list->data == NULL) list_init(list);

	while(readline(fd[0],buf,0)){
		if(buf[0] == '#')
			continue;
		//printf("%s",buf);
		ip_token = strtok(buf, "/");
		mask_token = strtok(NULL, "/");
		list_insert(list, str2ip(ip_token), create_mask(atoi(mask_token)));	
	}
	
	waitpid(pid, &status, 0);

	return;
}

void request(){
	CURL *curl;
	if( (curl = curl_easy_init()) == NULL){
		perror("Fail to init curl object");
		exit(1);
	}
	CURLcode res;
	curl_easy_setopt(curl, CURLOPT_URL, TARGET_URL);
	res = curl_easy_perform(curl);

	if(res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

	curl_easy_cleanup(curl);
	return;
}

size_t readline(int fd, char *buf, int offset){
	size_t len = 0;
	while(read(fd, buf + offset + len, 1)){
		if(buf[offset + len] == '\n')
			break;
		len++;
	}
	buf[offset + len + 1] = '\0';
	return len;
}


