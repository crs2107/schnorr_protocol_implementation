#include<iostream>
#include<stdlib.h>

#include "util_functions.h"
#include "schnorr.h"

using namespace std ;

int SECRET_KEY = 0 ;
int PUBLIC_KEY = 0 ;

Schnorr's_Digital_Signature::Schnorr's_Digital_Signature(int group_order , int group_element ,int group_element_order, int message):
    _group_order(group_order),
    _message(message),
    _group_element(group_element),
    _group_element_order(group_element_order) ,
    _first_coord_signature(0),
    _second_coord_signature(0),
{
}

void Schnorr's_Digital_Signature::key_generation()
{
    SECRET_KEY = 5 ;
    int temp = modulo_arithmetic::square_multiply(_group_element , SECRET_KEY , _group_order) ;
    PUBLIC_KEY = modulo_arithmetic::Extended_euclid(temp , _group_order) ;
}

void Schnorr's_Digital_Signature::generate_signature()
{
    int r = 5 ;
    int x = modulo_arithmetic::square_multiply(_group_element, r , _group_order) ;
    _first_coord_signature = x ;
    _second_coord_signature = (r+ (SECRET_KEY * x)) % _group_element_order ;

}

bool Schnorr's_Digital_Signature::verify_signature()
{
    int temp = _group_element ^ _second_coord_signature ;
    int tmp = PUBLIC_KEY ^ _first_coord_signature ; 

    int x = (temp * tmp)% _group_order ;

    if( x == _first_coord_signature)
    {
        return true ;
    }
    else
    {
        return false ;
    }

}

int main()
{

}














