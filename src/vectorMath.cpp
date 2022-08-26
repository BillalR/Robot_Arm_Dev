/*
Vector math functions

Author: Billal Rahimi
Email: billalrahimi@hotmail.com

Date: 2022-07-29
*/

// Includes
#include "vectorMath.hpp"

/**
 * Matrix multiplication
 * 
 * @param VecA Vector 1 
 * @param VecB Vector 2
 * @param result Reference pass of Vector 2 for use in storing the multiplication result
 * @return Void
 */
void VecMult(std::vector<std::vector<float> > VecA, std::vector<std::vector<float> > VecB, std::vector<std::vector<float> > &result)
{
    unsigned short int M = VecA.size();
    unsigned short int N = VecB.size();

    if(M != N)
    {
        Serial.println("Matrix size mismatch");
        Serial.println(M);
        Serial.println(N);
        return;
    }

    for(unsigned short int i = 0; i < M; i++)
    {
        for(unsigned short int j = 0; j < N; j++)
        {
            result[i][j] = 0;
            for(unsigned short int k = 0; k < N; k++)
            {
                result[i][j] += VecA[i][k] * VecB[k][j];
            }
        }
        
    }

}