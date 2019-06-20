#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <errno.h>

#define SERUM_BYTE_16   88
#define SYLENTH_BYTE_16 115

bool do_rename = false;
char* path;

void detect(char* filename, int count){
	FILE *fp;
	char *buf;
	long filelen;
	char fullpath[256];

	snprintf(fullpath, sizeof fullpath, "%s/%s", path, filename);

	fp = fopen(fullpath, "rb");
	if(!fp) fprintf(stderr, "Error opening %s \n", fullpath);
	
	fseek(fp, 0, SEEK_END);
	filelen = ftell(fp);
	rewind(fp);

	buf = (char *)malloc((filelen + 1)*sizeof(char));
	fread(buf, filelen, 1, fp);
	fclose(fp);

	switch(buf[16]){
		case SERUM_BYTE_16:
			printf("%d. %s is SERUM preset \n", count, filename);
			
			if(do_rename && strstr(filename, "SERUM") == NULL){
				char nbuf[256];
				snprintf(nbuf, sizeof nbuf, "%s/%s %s", path, "SERUM", filename);
				printf("renaming to %s \n", nbuf);
				int ret = rename(fullpath, nbuf);
				if(ret == -1) printf("error renaming: %s \n", strerror(errno));
			}

			break;
		case SYLENTH_BYTE_16:
			printf("%d. %s is SYLENTH preset \n", count, filename);
			
			if(do_rename && strstr(filename, "SYLENTH") == NULL){
				char nbuf[256];
				snprintf(nbuf, sizeof nbuf, "%s/%s %s", path, "SYLENTH", filename);
				printf("renaming to %s \n", nbuf);
				int ret = rename(fullpath, nbuf);
				if(ret == -1) printf("error renaming: %s \n", strerror(errno));
			}

			break;
		default:
			printf("%s is UNKNOWN, byte 16: %d \n", filename, buf[16]);
			break;
	}
}

int main(int argc, char** argv){
	if(argc < 2) fprintf(stderr, "Invalid usage \n");
	if(argc == 3) (bool)(do_rename = argv[2] - '0' > 0);

	DIR *dir;
	struct dirent *ent;
  
	if((dir = opendir(argv[1])) != NULL){
		path = argv[1];
		int i = 0;
		while((ent = readdir(dir)) != NULL){
			char buf[256];
			snprintf(buf, sizeof buf, "%s%s%s", argv[1], "/", ent->d_name);
			if(strstr(ent->d_name, ".fxp")){ 
				detect(ent->d_name, i);
				i++;
			}	
		}

		closedir(dir);
	}else{
		fprintf(stderr, "Error scanning directory");
		return 1;
	}

	return 0;	
}


