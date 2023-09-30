#ifndef SCHNORR_H

#define SCHNORR_H

using namespace std ;

class Schnorr's_Digital_Signature
{
    public :
        explicit Schnorr's_Digital_Signature(int group_order ,int group_element , int message) ;
        //~Schnorr's_Digital_Signature() ;
        void generate_signature() ;
        bool verify_signature() ;
    private :
        int _message ;
        int _group_order ;
        int _group_element ;
        int _group_element_order ;
        int _first_coord_signature ;
        int _second_coord_signature ;
    private :
        void key_generation() ;

} ;

#endif 
