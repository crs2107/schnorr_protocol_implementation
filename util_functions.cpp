#include<iostream>
#include<stdlib.h>

#include "util_functions.h"

using namespace std ;

int modulo_arithmetic::Euclid(int a , int b) //To find gcd of two numbers
{
   if (a == 0)
   {
       return b ;
   }
   else
   {
       return modulo_arithmetic::Euclid(b%a , a) ;
   }

}

int modulo_arithmetic::Extended_euclid(int g , int p) //to find g^(-1) modulo p
{
    int m0 = p;
    int y = 0, x = 1;
 
    if (p == 1)
        return 0;
 
    while (g > 1) {
        // q is quotient
        int q = g / p;
        int t = p;
 
        // m is remainder now, process same as
        // Euclid's algo
        p = g % p, g = t;
        t = y;
 
        // Update y and x
        y = x - q * y;
        x = t;
    }
 
    // Make x positive
    if (x < 0)
        x += m0;
 
    return x;

}


int modulo_arithmetic::square_multiply(int a, int x , int p) //to find a^x modulo p
{
    int temp = 1 ;
    int l = 0;
    int bin[64] ;

    while(x > 0) //To find the binary representation of x also the no of bits present in it
    {
        if(x%2 == 0)
        {
            bin[l] = 0 ;
        }
        else
        {
            bin[l] = 1 ;
        }
        x = x/2 ;
        l++ ;
    }
    
    l-- ;

    while(l >= 0)
    {
        temp = (temp*temp) % p ;
        if(bin[l] == 1)
        {
            temp = (temp * a) % p ;
        }
        l-- ;
    }

    return temp ;

    
    
}
