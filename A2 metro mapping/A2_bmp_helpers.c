/* FILE: A2_bmp_helpers.c is where you will code your answers for Assignment 2.
 * 
 * Each of the functions below can be considered a start for you. 
 *
 * You should leave all of the code as is, except for what's surrounded
 * in comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A2_bmp_headers.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int bmp_open( char* bmp_filename,        unsigned int *width, 
              unsigned int *height,      unsigned int *bits_per_pixel, 
              unsigned int *padding,     unsigned int *data_size, 
              unsigned int *data_offset, unsigned char** img_data ){

              
  // YOUR CODE FOR Q1 SHOULD REPLACE EVERYTHING FROM HERE
  FILE* bmpfile = fopen(bmp_filename, "rb");
    // Read the B and M characters into chars
  char* b=(char*)malloc(sizeof(char));
  char* m=(char*)malloc(sizeof(char));
  fread(b,1,1,bmpfile);
  fread(m,1,1,bmpfile);
        
    //Read the file size 
  unsigned int* overallFileSize=(unsigned int *)malloc(sizeof(unsigned int));
  fread(overallFileSize,1,sizeof(unsigned int),bmpfile);
    	
    // Close the file, re-open it to be at the beginning, and read the entire contents



  fclose(bmpfile);
	FILE*bmpfile2 = fopen(bmp_filename, "rb" );
      //store all the values in malloc 
    char* IMG_Data = (char*)malloc( *overallFileSize );
	  fread( IMG_Data, 1, *overallFileSize, bmpfile2 ); 
      if(*b != 'B' || *m != 'M' || overallFileSize <0 ){
        printf("the input file is not a valid BMP file");
        return -1; 
    }
    
       else{
    //datasize
    unsigned int* dataSize = (unsigned int*)malloc(sizeof(unsigned int));
    dataSize = (unsigned int*)(IMG_Data +2);
    
    //data_offset 
    unsigned int* dataOffset = (unsigned int*)malloc(sizeof(unsigned int));
    dataOffset = (unsigned int*)(IMG_Data +10);
    
    //width
    unsigned int* Wd = (unsigned int*)malloc(sizeof(unsigned int));
    Wd  = (unsigned int*)(IMG_Data +18);

    //height 
    unsigned int* Ht = (unsigned int*)malloc(sizeof(unsigned int));
    Ht = (unsigned int*)(IMG_Data +22);

    //bits_per_pixel 
    unsigned int* bbp  = (unsigned int*)malloc(sizeof(unsigned int));
    bbp   = (unsigned int*)(IMG_Data +28);
      
    //compute padding
   unsigned int* paddingp=(unsigned int*)malloc(sizeof(unsigned int*));
   *paddingp=(4-(((*Wd) * (*bbp))/8)%4)%4;

  *width=*Wd;
  *height=*Ht;
  *bits_per_pixel=*bbp;
  *padding=*paddingp;
  *data_size=*overallFileSize;
  *data_offset=*dataOffset;
  *img_data= IMG_Data;

    }

  // TO HERE
  
  return 0;  
}

// We've implemented bmp_close for you. No need to modify this function
void bmp_close( unsigned char **img_data ){

  if( *img_data != NULL ){
    free( *img_data );
    *img_data = NULL;
  }
}

int bmp_mask( char* input_bmp_filename, char* output_bmp_filename, 
              unsigned int x_min, unsigned int y_min, unsigned int x_max, unsigned int y_max,
              unsigned char red, unsigned char green, unsigned char blue )
{
  unsigned int img_width;
  unsigned int img_height;
  unsigned int bits_per_pixel;
  unsigned int data_size;
  unsigned int padding;
  unsigned int data_offset;
  unsigned char* img_data    = NULL;
  
  int open_return_code = bmp_open( input_bmp_filename, &img_width, &img_height, &bits_per_pixel, &padding, &data_size, &data_offset, &img_data ); 
  
  if( open_return_code ){ printf( "bmp_open failed. Returning from bmp_mask without attempting changes.\n" ); return -1; }
 
  // YOUR CODE FOR Q2 SHOULD REPLACE EVERYTHING FROM HERE
  //allocate memory 
  unsigned char *imageCopy = (char*)malloc(data_size*sizeof(char));
  //copy the content to new image 
  memcpy ( imageCopy, img_data, data_size);

  unsigned char* pixel_data = imageCopy +data_offset;
  unsigned int num_colors = bits_per_pixel/8; 
  for(int i = y_min; i<= y_min; i++){
    for(int j = x_min; j<= x_max;j++){
              pixel_data[ i*(img_width*num_colors +padding) + j*num_colors + 0] = red;
            pixel_data [i*(img_width*num_colors +padding) + j*num_colors + 1 ] = green;
            pixel_data[ i*(img_width*num_colors +padding)+ j*num_colors  + 2 ] = blue;
    }
  }
      //save it in new file 
   FILE* fp = fopen( output_bmp_filename , "w" );
   fwrite(imageCopy , data_size , 1 , fp );
   fclose(fp);
   free(imageCopy);
  // TO HERE!
  
  bmp_close( &img_data );
  
  return 0;
}         

int bmp_collage( char* bmp_input1, char* bmp_input2, char* bmp_result, int x_offset, int y_offset ){

  unsigned int img_width1;
  unsigned int img_height1;
  unsigned int bits_per_pixel1;
  unsigned int data_size1;
  unsigned int padding1;
  unsigned int data_offset1;
  unsigned char* img_data1    = NULL;
  
  int open_return_code = bmp_open( bmp_input1, &img_width1, &img_height1, &bits_per_pixel1, &padding1, &data_size1, &data_offset1, &img_data1 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input1 ); return -1; }
  
  unsigned int img_width2;
  unsigned int img_height2;
  unsigned int bits_per_pixel2;
  unsigned int data_size2;
  unsigned int padding2;
  unsigned int data_offset2;
  unsigned char* img_data2    = NULL;
  
  open_return_code = bmp_open( bmp_input2, &img_width2, &img_height2, &bits_per_pixel2, &padding2, &data_size2, &data_offset2, &img_data2 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input2 ); return -1; }
  
  // YOUR CODE FOR Q3 SHOULD REPLACE EVERYTHING FROM HERE
    //new boundaries 
  unsigned int new_img_width; //done 
  unsigned int new_img_height; //done   
  unsigned int new_padding; //done 

  //width 
   if(x_offset > 0 ){
    if(img_width2 + x_offset > img_width1){
      new_img_width = img_width2 +x_offset;
    }
    else{
      new_img_width = img_width1; 
    }
  }
  else if(x_offset < 0 ){
    if(img_width2 <img_width1 || img_width2 - img_width1 < -x_offset ||  img_width2 - img_width1 > x_offset){
      new_img_width = (img_width1 - x_offset) ;
    }
    else{
      new_img_width = img_width2;
    }
  }
   else {
       if(img_width1 >= img_width2){
         new_img_width = img_width1;
       }
       else{
         new_img_width = img_width2;
       }
   }
  //padding 
  new_padding=(4-(((new_img_width) * (bits_per_pixel1))/8)%4)%4;

  unsigned int canvas = ( new_img_width + new_padding )* new_img_height;

  //height 
  if(y_offset>0){
    if(img_height2 +y_offset >img_height1 ){
      new_img_height = img_height2 +y_offset;
    }
    else{
      new_img_height = img_height1;
    }
  }
  else if(y_offset<0){
    if(img_height2 <img_height1 || img_height2 - img_height1 < -y_offset || img_height2 - img_height1 > y_offset){
      new_img_height = (img_height1 - y_offset);
    }
    else{
      new_img_height = img_height2;
    }
  }

   else{
       if(img_height1 >= img_height2){
         new_img_height = img_height1;
       }
       else{
         new_img_height = img_height2;
       }
   }

  //boundary of image 
    unsigned int img_one_starting_col; 
    unsigned int img_two_starting_col;
    unsigned int img_one_starting_row; 
    unsigned int img_two_starting_row;


   if(x_offset > 0 ){
     img_one_starting_col = 0; 
     img_two_starting_col = x_offset; 
    
     if(y_offset > 0){
       img_one_starting_row = 0; 
       img_two_starting_row = y_offset; 
     }
     else if(y_offset < 0 ){
      img_one_starting_row = -y_offset;
       img_two_starting_row = 0; 
     }
     else{ //==0
       img_one_starting_row = 0; 
       img_two_starting_row =0; 
     }

   }
   else if(x_offset < 0 ){
     img_one_starting_col = -x_offset; 
     img_two_starting_col = 0; 
     if(y_offset>0){
       img_one_starting_row = 0; 
       img_two_starting_row = y_offset; 
     }
     else if(y_offset < 0 ){
       img_one_starting_row = -y_offset;
       img_two_starting_row = 0; 
     }
          else{ //==0
       img_one_starting_row = 0; 
       img_two_starting_row =0; 
     }
   }
      else{ //==0 
     img_one_starting_col = 0; 
     img_two_starting_col = 0; 
     if(y_offset>0){
       img_one_starting_row = 0; 
       img_two_starting_row = y_offset; 
     }
     else if(y_offset < 0 ){
       img_one_starting_row = -y_offset;
       img_two_starting_row = 0; 
     }
          else{ //==0
       img_one_starting_row = 0; 
       img_two_starting_row =0; 
     }
   }
 
   

    unsigned int img_one_ending_col = img_one_starting_col + img_width1; 
    unsigned int img_two_ending_col = img_two_starting_col + img_width2;
    unsigned int img_one_ending_row = img_one_starting_row + img_height1; 
    unsigned int img_two_enidng_row = img_two_starting_row + img_height2;
    
  
  //allocate new memory 
    unsigned int new_data_size;
    unsigned int new_data_offset;
    char *imageCopyC;

        new_data_offset = data_offset1; 
      new_data_size = (new_img_width * (bits_per_pixel1/8) + new_padding) * new_img_height + new_data_offset;
    imageCopyC = (char*)malloc(new_data_size*sizeof(char));
      //copy the whole content to new image 
   memcpy(imageCopyC, img_data1 , data_offset1);

   /* if( data_offset1 >= data_offset2){
    //new_data_size = data_size1 +data_size2 - data_offset2; //use the header size of data 1.
    new_data_offset = data_offset1; 
    new_data_size = new_data_offset + new_img_height * (new_img_width * bits_per_pixel1/8 +new_padding);
    imageCopyC = (char*)malloc(new_data_size*sizeof(char));
      //copy the whole content to new image 
   memcpy(imageCopyC, img_data1 , data_offset1);
  }
  else{
    //new_data_size = data_size1 +data_size2 - data_offset1; //use the header size of data 1.
    new_data_offset = data_offset2; 
     new_data_size = new_data_offset + new_img_height * (new_img_width * bits_per_pixel1/8 +new_padding);
     imageCopyC = (char*)malloc(new_data_size*sizeof(char ));
          //copy the whole content to new image 
   memcpy(imageCopyC, img_data2 , data_offset2);
  }*/

    //update some fields 
  memcpy(imageCopyC +2, &new_data_size,4);
  memcpy(imageCopyC+18, &new_img_width,4);
  memcpy(imageCopyC +22, &new_img_height,4);
  memcpy(imageCopyC +10, &new_data_offset,4);




  //loop it 
  unsigned char* pixel_data = imageCopyC +new_data_offset;
  unsigned int num_colors = bits_per_pixel1/8;

  /*for(int j = 0; j < new_img_height; j++){
    for(int i = 0; i < new_img_width; i++){
      if( j >= img_two_starting_row && j < img_two_enidng_row && i >= img_two_starting_col && i <img_two_ending_col){
        pixel_data[ j*( new_img_width *num_colors + new_padding ) + i*num_colors + 2 ] 
        = img_data2[data_offset2+ (j - img_two_starting_row )*(img_width2*num_colors+padding2)+(i - img_two_starting_col) *num_colors +2];
        
        pixel_data[ j*( new_img_width *num_colors + new_padding ) + i*num_colors + 1 ] 
        = img_data2[data_offset2+ (j - img_two_starting_row)*(img_width2*num_colors+padding2)+(i - img_two_starting_col) *num_colors + 1];
        
        pixel_data[ j*( new_img_width *num_colors + new_padding ) + i*num_colors + 0 ] 
        = img_data2[data_offset2+ (j - img_two_starting_row)*(img_width2*num_colors+padding2)+(i - img_two_starting_col) *num_colors +0];
      }
      else if(j >= img_one_starting_row && j < img_one_ending_row && i >= img_one_starting_col && i < img_one_ending_col) {
        pixel_data[ j*( new_img_width *num_colors + new_padding ) + i*num_colors + 2 ] 
        = img_data1[data_offset1 + (j - img_one_starting_row )*(img_width1 *num_colors+padding2)+(i - img_one_starting_col) *num_colors +2];

        pixel_data[ j*( new_img_width *num_colors + new_padding ) + i*num_colors + 1 ] 
        = img_data1[data_offset1 + (j - img_one_starting_row )*(img_width1 *num_colors+padding2)+(i - img_one_starting_col) *num_colors +1];       

        pixel_data[ j*( new_img_width *num_colors + new_padding ) + i*num_colors + 0 ] 
        = img_data1[data_offset1 + (j - img_one_starting_row )*(img_width1 *num_colors+padding2)+(i - img_one_starting_col) *num_colors +0];

      }
    }
  }*/
   //loop
  unsigned int new_1_offset = 0;
  unsigned int new_2_offset = 0;
  unsigned int currentpos=0;
  for (int row = 0; row < new_img_height;row++){
  	for (int column = 0; column < new_img_width;column++){
  		
      currentpos = (row)*(new_img_width*bits_per_pixel1/8 + new_padding) + (column)*(bits_per_pixel1/8);

  		if (row >= img_two_starting_row && row < img_two_enidng_row && column>= img_two_starting_col && column < img_two_ending_col){
  			new_2_offset = (row - img_two_starting_row)*(img_width2*num_colors + padding2) + (column - img_two_starting_col)*num_colors;
  			memcpy(pixel_data  +currentpos , img_data2 + new_2_offset + data_offset2, 3);
  		}
  		
      else if (row >= img_one_starting_row && row <  img_one_ending_row && column >= img_one_starting_col && column < img_one_ending_col){
  			new_1_offset = (row - img_one_starting_row )*(img_width1*num_colors + padding1) + (column- img_one_starting_col)*num_colors;
  			memcpy(pixel_data  + currentpos  , img_data1 + new_1_offset + data_offset1, 3);
  		}
  		
  	}
  }

   //save my shit 
   FILE* fp2 = fopen( bmp_result , "w" );
   fwrite(imageCopyC , new_data_size , 1 , fp2 );
   fclose(fp2);
   free(imageCopyC);
  
  // TO HERE!
  
  
  
  
  // TO HERE!
      
  bmp_close( &img_data1 );
  bmp_close( &img_data2 );
  
  return 0;
}                  
