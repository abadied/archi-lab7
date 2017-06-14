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
	fseek(fd,location,SEEK_SET);
	if(debug_mode)
		printf("location in decimal: %d length: %d\n",location,length);
	size_t size_fixed = length*size;
	void* buf = malloc(size_fixed);
	fread(buf,(size_t)size,(size_t)length,fd);
	
	int i;
	printf("HexaDecimal Representation:\n");
	for(i=0;i<length;i++){
		if(size == 1)
			printf("%02hhx\t",*((char*)buf + i));
		else if(size == 2)
			printf("%02hx\t",*((short*)buf + i));
		else
			printf("%02x\t",*((int*)buf + i));
	}
	printf("\n");

	printf("Decimal Representation:\n");
	for(i=0;i<length;i++){
		if(size == 1)
			printf("%hhu\t",*((char*)buf + i));
		else if(size == 2)
			printf("%hu\t",*((short*)buf + i));
		else
			printf("%u\t",*((int*)buf + i));
	}
	printf("\n");
	free(buf);
	fclose(fd);	
}

void loadIntoMemory(){
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
	char* sup;
	sscanf(str,"%s %d",location_str,&length);
	location = strtol(location_str,NULL,16);
	if(data_pointer)
		free(data_pointer);
	fseek(fd,location,SEEK_SET);
	data_pointer = (char*)malloc((size_t)length);
	if(debug_mode)
		printf("Filename: %s location in decimal: %d length: %d\n",filename,location,length);
	fread(data_pointer,1,(size_t)length,fd);
	printf("Loaded %d bytes into %p \n",length,data_pointer);
	fclose(fd);
}

void saveIntoFile(){
	if(strcmp(filename,"") == 0){
		printf("filename is empty \n");
		return;
	}
	FILE* fd = fopen(filename,"r+");
	if(!fd ){
		printf("failed to open file \n");
		return;
	}
	char str[100];
	int location, length;
	char location_str[8];
	char source_address[8];
	printf("Please enter <source-address> <target-location> <length>:\n");
	fgets(str,100,stdin);
	sscanf(str,"%s %s %d",source_address,location_str,&length);
	location = strtol(location_str,NULL,16);
	int sourcelocation = strtol(source_address, NULL, 16);
	if(data_pointer) /*check if location is bigger the filename size*/
		printf("change me \n");
	
	fseek(fd,location,SEEK_SET);
	if(strcmp(source_address,"0") == 0){
		printf("%s\n",source_address);
		fwrite(data_pointer,1,(size_t)length,fd);
	}else{
		fwrite(sourcelocation,1,(size_t)length,fd);
	}
	fclose(fd);
}

void fileModify(){
	if(strcmp(filename,"") == 0){
		printf("filename is empty \n");
		return;
	}
	FILE* fd = fopen(filename,"r+");
	if(!fd ){
		printf("failed to open file \n");
		return;
	}
	char str[100];
	int location; 
	char val_str[16];
	char location_str[8];
	printf("Please enter <location> <val>:\n");
	fgets(str,100,stdin);
	sscanf(str,"%s %s",location_str,val_str);
	location = strtol(location_str,NULL,16);
	printf("%d", location);
	char val[4];
	int i;
	for (i=0; i<size; i++){
		sscanf(&val_str[i*2], "%02x", &val[i]);
	}
	if(debug_mode) 
		printf("Location: %s Val: %s \n",location_str,val_str);
	fseek(fd,location,SEEK_SET);
	printf("%d", location);
	fwrite(val,1,(size_t)size,fd);
	fclose(fd);
}

int main(int argc, char** argv){
    char c;
    char empty;
    struct func_desc menu[] = {{"0-Toggle Debug Mode", toggleDebugMode},{"1-Set File Name", setFileName},{"2-Set Unit Size", setUnitSize},{"3-File Display",fileDisplay},{"4-Load Into Memory",loadIntoMemory},{"5-Save Into File",saveIntoFile},{"6- File Modify",fileModify},{"7-Quit", quit},{NULL,NULL}};
    while(1){
    	if(debug_mode){
    		printf("Unit size: %d \nFilename: %s \nData address: %p \n",size,filename,data_pointer);
    	}

        printf("Please choose a function: \n");
        for(int i = 0; i < 8; i++){
            printf("%s \n",menu[i].name);
        }
    	
        c = fgetc(stdin);
        empty = fgetc(stdin);
        while (empty != EOF && empty != '\n'){empty = fgetc(stdin);}
        if( c >= '0' && c <= '7'){
            menu[c - '0'].fun();
        }
        else{
            printf("Not within bounds \n");
        }
        
    }
    
}