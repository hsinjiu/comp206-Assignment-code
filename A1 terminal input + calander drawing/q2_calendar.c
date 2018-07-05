#include <stdio.h>
#include <stdlib.h>
#include <string.h>


        int daysize;
        int firstday;
        int row;

 /*set the seperator  */
	void rowsep (int size ){
		printf("|");
		for(int i = 0; i <size ; i++ ){
			printf("-");
		}
		printf("|");
	}	

/*set the month*/
	void month(int size, char* m ){
		int mlength = strlen(m);
		int left = size - mlength ; 
		printf("|");
	/*if 2X */
		if( left%2 == 0  ){
			for(int i = 0 ; i < left/2 ; i++){
				printf(" ");
			}
			printf("%s",m);
 			for(int i = 0 ; i < left/2 ; i++){
               			 printf(" ");
       			 }
		}
	/*IF NOT 2X*/
		else{
                        for(int i = 0 ; i < left/2 ; i++){
                                printf(" ");
                        }
                        printf("%s",m);
                        for(int i = 0 ; i < left/2 +1 ; i++){
                                 printf(" ");
                         }

		}
		printf("|");


	}
/*day labels */

	        void dayLabel(int rowS, char* m ){
                int mlength = strlen(m);
		int daySize = (rowS - 1 )/7 - 3; 
		
		if ( daySize > mlength){
			printf("|");
                        printf(" ");
		        printf("%s", m);
                        for(int i = 0 ; i < (daySize - mlength) ;i ++){
                                        printf(" ");
                                }
			printf(" ");
		
                }
                else{
			printf("|");
			printf(" ");
		        for(int j = 0; j < daySize ; j ++){
                                        printf("%c",*(m + j ) );
                                }
			printf(" ");
		}
		
        }


/*day label organizes*/
	void organizedDay(int daysize){
	dayLabel(daysize, "Sunday");
	dayLabel(daysize,"Monday");
	dayLabel(daysize,"Tuesday");
	dayLabel(daysize,"Wednesday");
	dayLabel(daysize, "Thursday");
	dayLabel(daysize,"Friday");
	dayLabel(daysize,"Saturday");
	printf("|");
	}
	
	void beginSpace(int firstday, int daySize){
/* fill up the space for no dates*/ 
		if( firstday - 1 > 0){
		for(int j = 0 ; j< firstday - 1; j ++ ){
			printf("|"); 
			printf(" ");/* the first space*/ 
			printf(" ");/*the empty space represent nothing*/ 
			for(int m = 0; m < daySize; m ++){
			printf(" "); /* the final to fill up the line*/  }
			}
		}
	}
	void leftSpaces(int leftNumbers, int daySize){
			if( leftNumbers > 0 ){
				for(int j = 0; j < 7 - leftNumbers; j ++){
			printf("|"); 
			printf(" ");/* the first space*/ 
			printf(" ");/*the empty space represent nothing*/ 
			for(int m = 0; m < daySize; m ++){
			printf(" "); /* the final to fill up the line*/  }
		
				}

			}

	}
/*days*/
	int daymethod(int firstday, int daySize){
		
		int totalspace = firstday + 30 -1; 
		int rowNeed = totalspace/7 +1; 
		int leftNumbers = totalspace % 7; 
		int initialSat = 8 - firstday; /* this is the first date of saturday*/ 
	

		/*fill in the begining spaces*/
		beginSpace(firstday, daySize);
		/*actual numbers*/
		for(int i = 1 ; i < 31 ; i ++ ){
			printf("|");
			printf(" ");/* the first space*/ 
			printf("%i",i);
		/*when i only takes 1 space*/
			if(i<10){
			for(int m = 0; m < daySize; m ++){ printf(" "); /* the final to fill up the line*/  }
			}
		/*when i takes 2 space*/
			else{
			for(int m = 0; m < daySize - 1; m ++){ printf(" "); /* the final to fill up the line*/}
			}
			/*done to saturday can jump line*/
			if(  (i - initialSat) % 7  == 0 ){
				printf("|");
				printf("\n");
			}
		}
		/*fill in the left spaces*/
		leftSpaces(leftNumbers,daySize );

	printf("|"); /* close it*/
	return leftNumbers + 1; /*indicate the next row start*/
	}
/*final structure */ 	
	int organizedOutput(int row, int firstday, int daysize, char* monthS){
		rowsep(row -2 );
		printf("\n");
        	month(row -2 ,monthS );
		printf("\n");
        	rowsep(row -2 );
		printf("\n");
		organizedDay(row );
		printf("\n");
		rowsep(row -2 );
		printf("\n");
		int nextDate = daymethod(firstday,daysize);
		printf("\n");
		return nextDate;
	}




void main(int argc, char* argv[] ){
        if(argc !=  3){
                printf("Shold give 2 command line argument");
                exit(-1);
        }
        /*checking daysize, firstday*/
        if ( atoi( argv[1])  <  2 ){
                printf("days must be 2 or greater");
                exit(-1);
        }
        if( atoi( argv[2])  < 1 || (*argv[2] - '0') > 7 ){
                printf("The first day of week has to be inbetween 1 to 7");
                exit(-1);
        }
	

        int daysize = atoi( argv[1]);
        int row  = (daysize + 3)*7 +1;      
        int firstday = atoi( argv[2]); 
       
/*forget to calculate the begin and end of each row "|", -2 for the input size*/
	int nextDate = organizedOutput(row,firstday,daysize,"January");
	nextDate = organizedOutput(row,nextDate,daysize,"February");
	nextDate = organizedOutput(row,nextDate,daysize,"March");
	nextDate = organizedOutput(row,nextDate,daysize,"April");
	nextDate = organizedOutput(row,nextDate,daysize,"May");
	nextDate = organizedOutput(row,nextDate,daysize,"June");
	nextDate = organizedOutput(row,nextDate,daysize,"July");
	nextDate = organizedOutput(row,nextDate,daysize,"August");
	nextDate = organizedOutput(row,nextDate,daysize,"September");
	nextDate = organizedOutput(row,nextDate,daysize,"October");
	nextDate = organizedOutput(row,nextDate,daysize,"November");
	nextDate = organizedOutput(row,nextDate,daysize,"December");
	rowsep(row -2 );
}
