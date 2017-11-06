#include <stdlib.h>
#include <stdio.h>

const int STRING_SIZE = 255;

int* open_file_read_numbers(char* _name)
{
      FILE *_h;
      _h = fopen(_name, "rw+");
      if(!_h)
      {
            printf("Couldn't open %s!", _name);
            return NULL;
      }
      
      int counter = 0;
      char* _buf = (char*)malloc(sizeof(char));
      while(fgets(_buf, STRING_SIZE, _h)) counter++; //считаем кол-во чисел в файле
      
      
      int* _returnVector = (int*)malloc(sizeof(int) * counter + 1);
      
      realloc(_buf, sizeof(int));
      rewind(_h);
      
      for(int i = 1; i < counter+1; i++)
      {
            fgets(_buf, 255, _h);
            *(_returnVector + i) = atoi(_buf);
      }
      *_returnVector = counter;
      
      free(_buf);
      fclose(_h);
      
      return _returnVector;
}

void sort_numbers(int numberOfNumbers, int* _massiv)
{
     _massiv++;
             for(int i = 0; i < numberOfNumbers; i++)
             {
                     for(int j = i; j < numberOfNumbers; j++)
                     {
                                              if(*(_massiv + j) == 0)
                                              {
                                                           int buf = *(_massiv + i);
                                                           *(_massiv + i) = *(_massiv + j);
                                                           *(_massiv + j) = buf;  
                                              }
                             
                     }
             }  
             for(int i = 0; i < numberOfNumbers; i++)
             {
                     if(*(_massiv + i) == 0) continue;
                     for(int j = i; j < numberOfNumbers; j++)
                     {
                                              if(*(_massiv + j) < 0)
                                              {
                                                           int buf = *(_massiv + i);
                                                           *(_massiv + i) = *(_massiv + j);
                                                           *(_massiv + j) = buf;  
                                              }
                             
                     }
             }  
}

int main(int argc, char *argv[])
{
      if(argv[1] == NULL) 
      {
            printf("Please provide a file");
            return 0; 
      }
      
      int* _numbers = open_file_read_numbers(argv[1]); //первое число в полученном массиве - количество чисел в массиве
      if(_numbers == NULL)
      {
            printf("Please provide a text file filled with a number on each line.");                      
      }
      sort_numbers(*_numbers, _numbers);

      
      FILE *_h;
      _h = fopen(argv[1], "w+");
      
      for(int i = 1; i < *_numbers + 1; i++)
      {
           // printf("%d \n", *(_numbers + i));
           fprintf(_h, "%d \n", *(_numbers + i));
      }
      
      fclose(_h);
}


