#include <stdio.h>
#include <stdlib.h>

typedef struct
{
       int numberOfRows, numberOfColumns;
       double** _Data;       
}Matrix;

double get_elem(void* _matr, int row, int col)
{
       Matrix* _mat = _matr;
       //проверки на ошибку индексации
       if( row > _mat->numberOfRows || col > _mat-> numberOfRows || row < 1 || col < 1 )
       {
              printf("\nUnable to access [%i+1,%i+1]", row, col);
              return 0;
       }
       else
       {
              return _mat->_Data[row-1][col-1]; //в математике нумерация индексов начинается с еденицы;
       }
}

void set_elem(void* _matr, int row, int col, double elem)
{
       Matrix* _mat = _matr;
       //проверки на ошибку индексации
       if( row > _mat->numberOfRows || col > _mat-> numberOfRows || row < 1 || col < 1 )
       {
              printf("\nUnable to access [%i,%i]", row, col);
              return;
       }
       else
       {
              _mat->_Data[row-1][col-1] = elem;
       }   
}

void nullify_matrix(void* _matr)
{
     if(_matr == NULL) return;
     Matrix* _tempMatrix = _matr;
        for(int i = 1; i < _tempMatrix->numberOfRows+1; i++)
        {
                for(int j = 1; j < _tempMatrix->numberOfColumns+1; j++)
                {
                        set_elem(_tempMatrix, i, j, 0);
                }
        }     
}

Matrix* _readMatrixFromFile(const char* _name)
{
        Matrix* _returnMat = malloc(sizeof(Matrix));
        FILE *_h;
        _h = fopen(_name, "r");
        if(_h == NULL) 
        {
              printf("Could not open %s!\n", _name);  
              return NULL;    
        }
        
        int numberOfNonzeroElements;
        
        fscanf(_h, "%i %i %i", &_returnMat->numberOfRows, &_returnMat->numberOfColumns, &numberOfNonzeroElements);
        _returnMat->_Data = (double**)malloc(_returnMat->numberOfRows * sizeof(double*));
        

        for(int i = 0; i < _returnMat->numberOfRows; i++)
        {
                _returnMat->_Data[i] = (double*)malloc(_returnMat->numberOfColumns * sizeof(double));
        }
        
        nullify_matrix(_returnMat);

        for(int i = 0; i < numberOfNonzeroElements; i++)
        {
                int row, col;
                double value;
                fscanf(_h, "%i %i %lf", &row, &col, &value);
                set_elem(_returnMat, row, col, value);
        }
        
        return _returnMat;
}

double Max(double* _numbers, int howMany)
{
       double max = 0;
       
       for(int i = 0; i < howMany; i++)
       {
               if(_numbers[i] > max) max = _numbers[i];
       }
       
       return max;
}

double AbsSum(double* _numbers, int howMany)
{
       double Sum = 0;
       
       for(int i = 0; i < howMany; i++)
       {
               if(_numbers[i] < 0) Sum -= _numbers[i];
               else Sum += _numbers[i];
       }       
       
       return Sum;
}

double FindLNorma(void* _matr)
{
       if(_matr == NULL) return -1;
       Matrix* _tempMatrix = _matr;
       int numberOfRows = _tempMatrix->numberOfRows;
       double* _sums = malloc(numberOfRows * sizeof(double));
       for(int i = 0; i < numberOfRows; i++)
       {
               _sums[i] = AbsSum(_tempMatrix->_Data[i], _tempMatrix->numberOfColumns);
       }
       return Max(_sums, numberOfRows);
       
}

int main(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++)
    {
            Matrix* tempMatr = _readMatrixFromFile(argv[i]);
            double tempNorm = FindLNorma(tempMatr);
            if(tempNorm != -1) printf("LNorm of matrix %s: %f\n", argv[i], tempNorm);
            
            free(tempMatr);
            tempMatr = NULL;
    }
}
