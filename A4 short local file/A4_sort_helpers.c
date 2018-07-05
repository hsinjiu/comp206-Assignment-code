#include "A4_sort_helpers.h"

// Function: read_all() 
// Provided to read an entire file, line by line.
// No need to change this one.
void read_all( char *filename ){
    
    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
	
    while( curr_line < MAX_NUMBER_LINES && 
           fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) )
    {
        curr_line++;
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// Function: read_all() 
// Provided to read only the lines of a file staring with first_letter.
// No need to change this one.
void read_by_letter( char *filename, char first_letter ){

    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
    text_array[curr_line][0] = '\0';
	
    while( fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) ){
        if( text_array[curr_line][0] == first_letter ){
            curr_line++;
        }

        if( curr_line == MAX_NUMBER_LINES ){
            sprintf( buf, "ERROR: Attempted to read too many lines from file.\n" );
            write( 1, buf, strlen(buf) );
            break;
        }
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q1.
void sort_words( ){
    int x, y; 
    char temp[MAX_LINE_LENGTH];
    x=0;
    while(text_array[x][0] != '\0'){
        y = x+1;
        while(text_array[y][0] != '\0'){
            if(strcmp(text_array[x],text_array[y])>0){
                strcpy(temp, text_array[x]);
                strcpy(text_array[x], text_array[y]);
                strcpy(text_array[y], temp);
            }
            y++;
        }
        x++;
    } 
}
//global array of semaphore 
sem_t *sem_array[27];
// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2.
int initialize( ){
    // Remove the current place-holder code, and write your own.

    //set all sem
    for(int i = 0; i <= 27; i++){

            sprintf(buf, "sem_%c", (char)(i + 97)); 

            if(i == 1){ //1~27 a~z
            sem_unlink(buf);
            sem_array[i] = sem_open(buf,O_CREAT, 0666,1);
            }
            else{
            sem_unlink(buf); 
            sem_array[i] = sem_open(buf,O_CREAT, 0666,0);
            }
    }
   /*
    sprintf(buf, "Initializing.\n"  );
    write(1, buf, strlen(buf)); */
       
    return 0;
}

// YOU MUST COMPLETE THIS FUNCTION FOR Q2 and Q3.   
int process_by_letter( char* input_filename, char first_letter ){
    // For Q2, keep the following 2 lines in your solution (maybe not at the start).
    // Add lines above or below to ensure the "This process will sort..." lines
    // are printed in the right order (alphabetical).
            int j = (first_letter -'a') +1; 
   
            sem_wait( sem_array[j]);
            //two lines given 
            //sprintf( buf, "This process will sort the letter %c.\n",  first_letter );
            //write(1,buf,strlen(buf));
            FILE *buf = fopen("buff.txt", "a");
            if(buf == NULL ){
               printf("Error opening file");
                return -1;
            }
            read_by_letter( input_filename, first_letter );
            sort_words( );
            for( int counter = 0 ; text_array[counter][0] !='\0'; counter ++ ){
                fprintf(buf,"%s", text_array[counter]); 
            }
            fclose(buf);
            //two lines end 
            if(j ==26){ //1~26 a~z
                sem_post(sem_array[0]);
            }
            else{
                sem_post( sem_array[j+1]);
             }
            //CODE END Q2  

    // For Q3, uncomment the following 2 lines and integrate them with your overall solution.


    return 0;
    

}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2 and Q3.
int finalize( ){
    // For Q2, keep the following 2 lines in your solution (maybe not at the start).
    // Add lines above or below to ensure the "Sorting complete!" line
    // is printed at the very end, after all letter lines.

    sem_wait( sem_array[0] ); //the last element    

    FILE *bufR = fopen("buff.txt", "r");
    if(bufR == NULL){
        printf("Error opening a file");
        return -1; 
    }
    char buffer[MAX_LINE_LENGTH]; 
    while(!feof(bufR)){
        strcpy(buffer, "\0");
        fgets(buffer, MAX_LINE_LENGTH, bufR);
        sprintf(buf,"%s", buffer);
        write( 1, buf, strlen(buf) );
    }

    fclose(bufR);
        //given code
    sprintf( buf, "Sorting complete!\n" );
    write( 1, buf, strlen(buf) );
    //code end Q2
    //delete file
    int status;
    status = remove("buff.txt");
    return 0;
}

