#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
 #include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


 struct func_desc{
    char *name;
    void (*fun)();
};

int debug_mode = 0;
int size = 1;
char* data_pointer = NULL;
char filename[100];

void quit(){
	exit(0);
}

void toggleDebugMode(){
	if(debug_mode == 1){
		debug_mode = 0;
		printf("Debug flag now off.\n");
	}
	else{
		debug_mode = 1;
		printf("Debug flag now on.\n");
	}
}

void setFileName(){
	printf("Enter file name: \n");
	fgets(filename,100,stdin);
	strtok(filename,"\n");
	if(debug_mode)
		printf("Debug: file name set to: %s \n",filename);
}

void setUnitSize(){
	printf("Enter a number: \n");
	int c = fgetc(stdin);
	fgetc(stdin);
	if(c == '1' || c == '2' || c == '4'){
		size = c - '0';
		if(debug_mode)
			printf("Debug: size set to : %d \n",size);
	}
	else{
		printf("Number entered isn't valid!\n");
	}
}

void fileDisplay(){
	if(strcmp(filename,"") == 0){
		printf("filename is empty \n");
		return;
	}
	FILE* fd = fopen(filename,"r+b");
	if(!fd ){
		printf("failed to open file \n");
		return;
	}
	
	char str[100];
	int location, length;
	char* location_str;
	printf("Please enter <location> <length>:\n");
	fgets(str,100,stdin);
	sscanf(str,"%s %d",location_str,&length);
	location = strtol(location_str,NULL,16);
	fseek(fd,location,SEEK_CUR);
	if(debug_mode)
		printf("location in decimal: %d length: %d\n",location,length);
	size_t size_fixed = length*size;
	void* buf = malloc(size_fixed);
	fread(buf,(size_t)size,(size_t)length,fd);
	
	int i;
	printf("HexaDecimal Representation:\n");
	for(i=0;i<length;i++){
		if(size == 1)
			printf("%04hx ",*((char*)buf + i));
		else if(size == 2)
			printf("%04hx ",*((short*)buf + i));
		else
			printf("%04hx ",*((int*)buf + i));
	}
	printf("\n");

	printf("Decimal Representation:\n");
	for(i=0;i<length;i++){
		if(size == 1)
			printf("%hu ",*((char*)buf + i));
		else if(size == 2)
			printf("%hu ",*((short*)buf + i));
		else
			printf("%hu ",*((int*)buf + i));
	}
	printf("\n");
	free(buf);
	fclose(fd);	
}


int main(int argc, char** argv){
    char c;
    char empty;
    struct func_desc menu[] = {{"0-Toggle Debug Mode", toggleDebugMode},{"1-Set File Name", setFileName},{"2-Set Unit Size", setUnitSize},{"3-File Display",fileDisplay},{"4-Quit", quit},{NULL,NULL}};
    while(1){
    	if(debug_mode){
    		printf("Unit size: %d \nFilename: %s \nData address: %s \n",size,filename,data_pointer);
    	}

        printf("Please choose a function: \n");
        for(int i = 0; i < 5; i++){
            printf("%s \n",menu[i].name);
        }
    	
        c = fgetc(stdin);
        empty = fgetc(stdin);
        while (empty != EOF && empty != '\n'){empty = fgetc(stdin);}
        if( c >= '0' && c <= '4'){
            menu[c - '0'].fun();
        }
        else{
            printf("Not within bounds \n");
        }
        
    }
    
}