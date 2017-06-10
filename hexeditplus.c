#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
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
			printf("Debug: size set to : %d",size);
	}
	else{
		printf("Number entered isn't valid!\n");
	}
}

int main(int argc, char** argv){
    char c;
    
    struct func_desc menu[] = {{"0-Toggle Debug Mode", toggleDebugMode},{"1-Set File Name", setFileName},{"2-Set Unit Size", setUnitSize},{"3-Quit", quit},{NULL,NULL}};
    while(1){
    	if(debug_mode){
    		printf("Unit size: %d \nFilename: %s \nData address: %s \n",size,filename,data_pointer);
    	}

        printf("Please choose a function: \n");
        for(int i = 0; i < 4 ; i++){
            printf("%s \n",menu[i].name);
        }
        printf("Option: ");
    
        c = fgetc(stdin);
        fgetc(stdin);
        if( c >= '0' && c <= '3'){
            menu[c - '0'].fun();
        }
        else{
            printf("Not within bounds \n");
        }
        
    }
    
}