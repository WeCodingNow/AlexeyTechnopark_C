#include <stdio.h>
#include <stdlib.h>

typedef struct
{
        int* _Data;
        int maxIndex;
}DynamicMassive;

DynamicMassive* _createDynamicMassive(int wantedSize)
{
     DynamicMassive* _returnMassive = malloc(sizeof(DynamicMassive));
     if(_returnMassive == NULL) 
     {
         printf("Could not allocate memory to a dynamic massive with size: %d\n", wantedSize);
         return NULL;
     }
     
     
     if(wantedSize == 0) 
     {
            _returnMassive->_Data = malloc(sizeof(int));     
            _returnMassive->maxIndex = -1;  
            return _returnMassive;
     }
     else
     {
            _returnMassive->_Data = malloc(sizeof(int) * wantedSize); 
            _returnMassive->maxIndex = wantedSize-1;
            return _returnMassive;
     }
}

void setElement(DynamicMassive* _dynMas, int number, int value)
{
     if(_dynMas == NULL) return;
     
     if(number > (_dynMas->maxIndex))
     {
               
               _dynMas->_Data = (int*)realloc(_dynMas->_Data, (number + 1) * sizeof(int));
               _dynMas->maxIndex = number;
     }
     
     _dynMas->_Data[number] = value;
}

int getElement(DynamicMassive* _dynMas, int number)
{
       if(number > (_dynMas->maxIndex) || _dynMas == NULL)
       {
             printf("Could not access A[%d]!\n", number);
             return 0;
       }
       printf("ok");
       return _dynMas->_Data[number];
}

void freeMassive(DynamicMassive* _dynMas)
{
     free(_dynMas->_Data);
     free(_dynMas);     
}

int main(int argc, char *argv[])
{
  FILE* _h1;
  if(argv[1] == NULL)
  {
         printf("Please supply a file!");
         return 0;
  }
  if(argv[2] == NULL)
  {
         printf("Please supply an output file name!");
         return 0;
  }
  
  _h1 = fopen(argv[1], "r");
  if(_h1 == NULL) 
  {
         printf("Could not open %s!", argv[1]);
         return 0;
  }
  
  int numbBuf, counter = 0;
  
  DynamicMassive* _dynMas = _createDynamicMassive(0);
  if(_dynMas == NULL) return 0;
  
  while(fscanf(_h1, "%d", &numbBuf) != EOF)
  {
         setElement(_dynMas, counter, numbBuf);
         counter++;
  }
  
  fclose(_h1);
  
  _h1 = fopen(argv[2], "w");
  if(_h1 == NULL)
  {
        printf("Could not open %s!", argv[2]);       
  }
  
  for(int i = _dynMas->maxIndex; i >= 0; i--)
  {
         fprintf(_h1, "%d ", getElement(_dynMas, i));
  }
  fclose(_h1);
  freeMassive(_dynMas);
  
  return 0;
}
