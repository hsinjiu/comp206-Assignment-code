# Assignment3

This is the source code repository that will be used as a starting point for Assignment 3. You should edit this file (README.md) in order to write your responses for Question 2.
##Explain program function call
* taking several students' name as input. Create an array of class and create target_user
* make type PREFERRENCE_INFO array and and target_user(the fist instance). call function from preference to set target user adress.
* run the for loop all the other students,each student call load_one_preference
  * find the possible best matching with min-distance by calling two functions from disance.c. (use macro to check their preference )
* printing out favorite movie and end 
##LOAD_FIELD: 
The fomat "#define(parameters) replace_parameter" is a format of define that accept an list of parameters (must appear in order)that can be replace by the replace_parameter that contain the actual argument.So here it can be replace by input_fcn_array, which is an array of function pointers. It can handle various types of data, since each type of data is put into its corresponding function according to its field_number. 
##FIELD_OFFSETS: 
the function "offsetof" allow the calculation of size from the begning to end of an object (which includes an padding). In this function it calculate all the objects sizes giving a more accurate size. This correct way of storing position  of each field in the struct could help when implementing **PRINT_FIELD** and **LOAD_FIELD**If doesn't use offset, the padding will not be included (which can give a smaller size than our actual size )
