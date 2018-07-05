#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

	int checkFloat(char* checking ){
		for(int i = 0; i < strlen(checking); i ++ ){
			if( (*(checking +i ) ) == '.' || isdigit(*(checking +i )) ) {
				continue; 
			}
			else{
				return -1;
				} 
			}
		return 1; 
		}


int aTag;
int bTag; 
float firstF;
float SecondF;
int flagA=-1;
int flagB=-1;
int main(int argc, char* argv[] ){
	/*make sure its 3 arg*/

	if (argc !=  4){
		printf(" input should be 3 arguments");
		return -1;	
	}

		if( checkFloat(argv[2] ) == -1 || checkFloat(argv[3] ) == -1){
	/*false, exit*/
			printf("Error:bad float arg");
			return -1;
			 }
		else{
			firstF = atof(argv[2]);;
			SecondF = atof(argv[3]);
		}

/*part1*/
	FILE*f = fopen(argv[1],"r" );
	FILE*f2 = fopen(argv[1],"r" );

	if(f == NULL){
			printf("Error:bad file");
			return -1; 
		}

    do{
        char buffer1=fgetc(f);
        	if(buffer1=='#'){
           		 char buffer2=fgetc(f);
            if(buffer2=='A'){
               			 char buffer3=fgetc(f);
                    	if(buffer3=='#'){
                 	   flagA=0;
              	   }
     }
			else if(buffer2=='B'){
               		 char abuffer3=fgetc(f);
               	 if(abuffer3=='#'){
                     flagB=0;
                 }
      }
        } 
    }
	while(!feof(f));
    if(flagA==-1||flagB==-1){
        printf(" Error: Bad file");
        exit(-1);
    }
    else{    
        do{
            	char rbuffer1=fgetc(f2);
            if(rbuffer1=='#'){
               		 char rbuffer2=fgetc(f2);
            if(rbuffer2=='A'){
                   	 char rbuffer3=fgetc(f2);
             if(rbuffer3=='#'){
                        printf("%.6f",firstF);
              }
                }
			else if(rbuffer2=='B'){
                    char rbbuffer3=fgetc(f2);
                if(rbbuffer3=='#'){
                        printf("%.6f",SecondF);
                    }
         }
            }
			else{
                printf("%c",rbuffer1);
     }    
     }
	while(!feof(f2));                                     
    }

fclose(f);
fclose(f2);
}

