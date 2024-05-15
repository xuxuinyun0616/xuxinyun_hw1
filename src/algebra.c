#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if(a.rows!=b.rows || a.cols!=b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        Matrix c;
        int i,j;
        c.rows=a.rows;
        c.cols=a.cols;
        for(i=0;i<c.rows;i++)
        {
            for(j=0;j<c.cols;j++)
            {
                c.data[i][j]=a.data[i][j]+b.data[i][j];
            }
        }
        return c;
    }
    
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if(a.rows!=b.rows || a.cols!=b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        Matrix c;
        int i,j;
        c.rows=a.rows;
        c.cols=a.cols;
        for(i=0;i<c.rows;i++)
        {
            for(j=0;j<c.cols;j++)
            {
                c.data[i][j]=a.data[i][j]-b.data[i][j];
            }
        }
        return c;
    }
    
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if(a.rows!=b.cols || a.cols!=b.rows)
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    else
    {
        Matrix c;
        int i,j,k,l;
        c.rows=a.rows;
        c.cols=a.cols;
        for(i=0;i<c.rows;i++)
        {
            for(j=0;j<c.cols;j++)
            {
                c.data[i][j]=0;
                for(k=0;k<c.rows;k++)
                {
                    c.data[i][j]+=a.data[i][k]*b.data[k][j];
                }
                
            }
        }
        return c;
    }
    
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix newa;
    newa.rows=a.rows;
    newa.cols=a.cols;
    int i,j;
    for(i=0;i<a.rows;i++)
    {
        for(j=0;j<a.cols;j++)
        {
            newa.data[i][j]=k*a.data[i][j];
        }
    }
    return newa;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix Ta;
    Ta.rows=a.cols;
    Ta.cols=a.rows;
    int i,j;
    for(i=0;i<a.rows;i++)
    {
        for(j=0;j<a.cols;j++)
        {
            Ta.data[i][j]=a.data[j][i];
        }
    }
    return Ta;
    
}

double det_matrix(Matrix a)
{
    if(a.rows>2)
    {
        if(a.rows!=a.cols)
        {
            printf("Error: The matrix must be a square matrix.\n");
            return 0;
        }
        else
        {
            int i,j,k;
            double re;
            Matrix c;
            c=create_matrix(a.rows-1, a.cols-1);
            
            for(k=0;k<a.rows;k++)
            {
                for(i=0;i<c.rows;i++)
                {
                    for(j=0;j<c.cols;j++)
                    {
                        if(i<k)
                        {
                            c.data[i][j]=a.data[i][j+1];
                        }
                        else if(i>k)
                        {
                            c.data[i][j]=a.data[i+1][j+1];
                        }
                    }
                re=a.data[k][0]*det_matrix(c);
                }
            }
        }
    }
    else if(a.rows==2)
    {
        return a.data[0][0]*a.data[1][1]-a.data[1][0]*a.data[0][1];
    }
    else if(a.rows==1)
    {
        return a.data[0][0];
    }
}

Matrix inv_matrix(Matrix a)
{
    if(a.rows!=a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    else if(det_matrix(a)==0)
    {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);       
    }
    else
    {
        int i,j,x,y,n,ex=1;
        Matrix c,inva;
        c=create_matrix(a.rows-1, a.cols-1);
        inva=create_matrix(a.rows, a.cols);
        for(i=0;i<a.rows;i++)
        {
            for(j=0;j<a.cols;j++)
            {

                ex=(i+j)%2?-1:1;

                for(x=0;x<c.rows;x++)
                {
                    if(x<i && y<j)
                    {
                        c.data[x][y]=a.data[i][j];
                    }
                    else if(x>i && y<j)
                    {
                        c.data[x][y]=a.data[i+1][j];
                    }
                    else if(x>i && y>j)
                    {
                        c.data[x][y]=a.data[i+1][j+1];
                    }
                    else
                    {
                        c.data[x][y]=a.data[i][j+1];
                    }
                }

                inva.data[i][j]=ex*det_matrix(c);
            }
        }
        return c;
    }
    
}

int rank_matrix(Matrix a)
{
    int rank=(a.rows>a.cols?a.cols:a.rows);
    int i,j,x,y,mid;
    int flag=1;
    double k;

    for(i=0;i<a.rows;i++)
    {
        if(a.data[i][i]==0)
        {
            for(j=i+1;j<a.cols;j++)
            {
                if(a.data[i][j]!=0)
                {
                    for(x=0;x<a.rows;x++)
                    {
                        mid=a.data[x][i];
                        a.data[x][i]=a.data[x][j];
                        a.data[x][j]=mid;
                    }
                    break;
                }
            }
        }
    }

    for(i=0;i<a.rows;i++)
    {
        if(a.data[i][i]!=0)
        {
            for(j=i+1;j<a.cols;j++)
            {
                k=a.data[i][j]/a.data[i][i];
                if(k==0)
                {
                    continue;
                }
                else
                {
                    for(x=0;x<a.rows;x++)
                    {
                        a.data[x][j]-=k*a.data[x][i];
                    }
                }
            }
        }
        else
        {
            for(j=i+1;j<a.cols;j++)
            {
                flag=1;
                if(a.data[i][j]!=0)
                {
                    for(x=0;x<a.rows;x++)
                    {
                        mid=a.data[x][i];
                        a.data[x][i]=a.data[x][j];
                        a.data[x][j]=mid;
                    }
                    flag=-1;
                    break;
                }
            }
            if(flag!=-1)
            {
                rank-=1;
                for(y=0;y<a.cols;y++)
                {
                    a.data[i][y]=a.data[a.cols-1][y];
                }
            }
            i-=1;           
        }
    return rank;
    }
}

double trace_matrix(Matrix a)
{
    if(a.rows!=a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else
    {
        int i;
        double sum=0;
        for(i=0;i<a.rows;i++)
        {
            sum+=a.data[i][i];
        }
        return sum;
    }
    
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}