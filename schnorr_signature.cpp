#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cstring>

typedef long long int llu ;

#define ALL_ONE_30BIT 0x3FFFFFFF
#define ALL_ONE_32BIT 0xFFFFFFFF

#define GET_THE_BIT(a,m)  ((a[m/30] >> (m%30)) & 1)

using namespace std;

//function to change the base from 2^8 to 2^30
//
void print_256_number(llu x[10])
{

    for(unsigned i=0 ; i<9 ; i++)
    {
        cout<<","<<std::dec<<x[i] ;
    }
}
void print_Big_number(llu *x,int size)
{

    for(unsigned i=0 ; i<size ; i++)
    {
        cout<<","<<x[i] ;
    }
}

/*int get_bit1(long long int a[] ,  long long int m)
{
 int z,i;
 z = (a[m/30] >> (m%30)) & 1;
 return z;
}*/

int get_bit_length(llu *a)
{
 int z=0,i,m=255;
 while(z != 1)
 {
 	z = (a[m/30] >> (m%30)) & 1;
 	m--;
 }
 return (m+1);
}


void change_base_to_2_power_30(unsigned char a[32] , llu base_2_power_30_rep[9]) //a is a 256 bit integer in 256 base representation
{

    base_2_power_30_rep[0] = a[0] |(llu)(a[1])<<8 |(llu)(a[2])<<16 |(llu)(a[3]&0x3f)<<24 ;
    base_2_power_30_rep[1] = (a[3]>>6) |(llu)(a[4])<<2 |(llu)(a[5])<<10 |(llu)(a[6])<<18 | (llu)(a[7]&0xf)<<26 ;
    base_2_power_30_rep[2] = (a[7]>>4) |(llu)(a[8])<<4 |(llu)(a[9])<<12 |(llu)(a[10])<<20 | (llu)(a[11]&0x3)<<28 ;
    base_2_power_30_rep[3] = (a[11]>>2) |(llu)(a[12])<<6 |(llu)(a[13])<<14 |(llu)(a[14])<<22 ;
    base_2_power_30_rep[4] = a[15] |(llu)(a[16])<<8 |(llu)(a[17])<<16 |(llu)(a[18]&0x3f)<<24 ;
    base_2_power_30_rep[5] = (a[18]>>6) |(llu)(a[19])<<2 |(llu)(a[20])<<10 |(llu)(a[21])<<18 | ((llu)(a[22])&0xf)<<26 ;
    base_2_power_30_rep[6] = (a[22]>>4) |(llu)(a[23])<<4 |(llu)(a[24])<<12 |(llu)(a[25])<<20 | ((llu)(a[26])&0x3)<<28 ;
    base_2_power_30_rep[7] = (a[26]>>2) |(llu)(a[27])<<6 |(llu)(a[28])<<14 |(llu)(a[29])<<22 ;
    base_2_power_30_rep[8] = a[30] |(llu)(a[31])<<8 ;

   // cout<<"base 2^30 base representation is"<<endl ;
   // for(unsigned i = 0 ; i< 9 ; i++)
   // {
   //     cout<<"  ," << base_2_power_30_rep[i] ;
   // }
   // cout<<endl ;

}

int compareTwoBigNumbers(llu a[10] , llu b[10], int size = 9)
{
 int i = size;
 while(a[i]==b[i] && i>=0)
 {
 	i--;
 }
 if(i != -1)
 {
 	if(a[i] > b[i])
    {
 		return 1;
    }
 	else
    {
 		return 0;
    }
 }
 else
 {
 	return -1;
 }
}


void Tobinary(llu x , int b[64], int size)
{
    int i = 0 ;
    while(x > 0)
    {
        if(x % 2 == 0)
        {
            b[i] = 0 ;
        }
        else
        {
            b[i] = 1 ;
        }
        x = x/2 ;
        i++ ;
    }
    size = i-- ;
    for(unsigned j=0 ; j<size ; j++)
    {
        cout<<""<<b[j] ;
    }
    cout<<"," ;
}


void add256bit_num(llu *a , llu *b , llu *add,int len = 11 ,bool verbose = 0)
{

   for(unsigned k= 0 ; k < len ; k++)
   {
       llu temp = (a[k]&ALL_ONE_30BIT)+(b[k]&ALL_ONE_30BIT) ;
       if(verbose)
       {
           cout << "carry = " << add[k] << endl ;
           cout << "a[" << k << "] = " << std::hex << (a[k]&ALL_ONE_32BIT) << endl ;
           cout << "b[" << k << "] = " << std::hex << (b[k]&ALL_ONE_32BIT) << endl ;
       }
       add[k] = add[k] + temp ;
       // if ((add[k] >> 28) > 0x3) add[k+1] = 1 ;
       add[k+1] = ((add[k] >> 30) & 0x1) ;
       add[k] &= ALL_ONE_30BIT ;
       if (verbose) cout << "add[" << k << "] = " << std::hex << (add[k]&ALL_ONE_32BIT) << endl ;
   }
   // cout << "add[11] = " << std::hex << (add[11]&ALL_ONE_30BIT) << endl ;


}
 void sub256bit_num(llu *a, llu *b, llu *c, int len) 	// here a is bigger than b.
{
 llu *d = new llu[len+1] ;
 for(unsigned j=0;j<len+1;j++)
 {
 	d[j]=a[j];
 }
 for(unsigned i = 0; i < len; i++)
 {
        c[i]=d[i]-b[i];
        if((c[i] >> 63)&1)
        {
            c[i] += (1 << 30);
            d[i+1]-=1;
        }
 }
}



void multiply256bit_num(llu a[10], llu b[10] , llu mult[20],bool verbose= 0)
{
    if(verbose)
    {
        print_256_number(a) ;
        cout<<endl ;
        print_256_number(b) ;
        cout<<endl ;
    }

    for(unsigned i=0 ; i<10 ; i++)
    {
        for(unsigned j=0 ; j<10 ; j++)
        {
            mult[j+i] += ((a[j]&ALL_ONE_30BIT)*(b[i]&ALL_ONE_30BIT)) ;
            if (verbose) {
                cout << "a[" << j << "] = " << (a[j]&ALL_ONE_30BIT) << endl ;
                cout << "b[" << j << "] = " << (b[j]&ALL_ONE_30BIT) << endl ;
                cout<<"mult["<<j<<"+"<<i<<"]="<<mult[j+i]<<endl ;
            }
        }
    }
    for(unsigned i=0 ; i<20 ; i++)
    {
        llu tmp = 0 ;
        tmp = mult[i]>>30 ;
        mult[i] = mult[i] & ALL_ONE_30BIT ;
        mult[i+1] += tmp ;
    }
}


void barrett_reduction(llu *x , llu *remainder)
{
 llu mu[10]={805306368,0,0,1073741820,1073741807,1073741759,1073741567,1073741823,4095,16384};
 llu p[10]={1073741823, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535,0};
 llu basePowerTen[11] = {0} ;
 basePowerTen[10] = 1;

 llu q_1[10] = {0}, q1[20] = {0},q2[10]={0},base[11]={0},x1[10]={0},qp[10]={0},dummy[20]={0},r[10]={0},r1[11]={0},r2[10]={0};
 for(unsigned i=0;i<10;i++)
 {
 	q_1[i] = x[i+8];
 }

 llu q_2[20] = {0} ;
 multiply256bit_num(q_1 , mu , q_2);

 llu q_3[10] = {0} ;
 for(unsigned i=0;i<10;i++)
 {
 	q_3[i] = q_2[i+10];
 }

 llu Mult_p_q3[20] = {0} ;
 multiply256bit_num(q_3 , p , Mult_p_q3);

 if(compareTwoBigNumbers(x , Mult_p_q3) == 1 || compareTwoBigNumbers(x , Mult_p_q3) == -1)
 {
 	sub256bit_num(x , Mult_p_q3 , r,10);
 }
 else
 {
    llu r_temp[11] = {0} ;
 	sub256bit_num(Mult_p_q3 , x, r_temp,10);
 	sub256bit_num(basePowerTen ,r_temp, r,10);

 }
 if(compareTwoBigNumbers(r , p) == -1)
 {
 	for(unsigned i=0;i<10;i++)
    {
 		remainder[i]=0;
    }
 }
 if(compareTwoBigNumbers(r , p) == 0)
 {
 	for(unsigned i=0;i<10;i++)
    {
 		remainder[i]=r[i];
    }
 }

 while(compareTwoBigNumbers(r , p) == 1)
 	{
        llu r_2[10] = {0} ;
 		sub256bit_num(r , p , r_2,10);
 		for(unsigned i=0;i<10;i++)
 		{
 			r[i]=r_2[i];
 		}
 	}
 if(compareTwoBigNumbers(r , p) == -1)
 {
 	for(unsigned i=0;i<9;i++)
    {
 		remainder[i]=0;
    }
 }
 else
 {
 	for(unsigned i=0;i<9;i++)
    {
 		remainder[i]=r[i];
    }
 }
 }



void squareAndMultiply(llu x[10] , llu xPower[11]) // to calculate x^(p-2)mod p
{
    llu p_minus_two[10] = {1073741821, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535 ,0} ;
    const char* bin_p_minus_two = "1111111111111111111111111111111100000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111101" ;
    for(int i= 0 ; i< strlen(bin_p_minus_two) ; i++)
    {
        llu mult[20] = {0} ;
        multiply256bit_num(xPower,xPower,mult) ;
        barrett_reduction(mult,xPower) ;

        if( bin_p_minus_two[i] == '1')
        {
            llu mult_1[20] = {0} ;
            multiply256bit_num(xPower,x,mult_1) ;

            barrett_reduction(mult_1,xPower) ;
        }


    }




}
void ECC_Group_Point_Addition(llu *P_1_x , llu *P_1_y , llu *P_2_x , llu *P_2_y , llu *P_3_x , llu* P_3_y)  //to compute P_1 + P_2 where P_1 != P_2
{
    llu p[10] = {1073741823, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535,0} ; //for curve p-256
    llu lambda[10] = {0} ;
    //To compute x_2 - x_1
    llu sub_x[10] = {0} ;
    if(compareTwoBigNumbers(P_2_x , P_1_x) == 1 || compareTwoBigNumbers(P_2_x , P_1_x) == -1)
    {
        sub256bit_num(P_2_x , P_1_x , sub_x , 9);
    }
    else
    {
        llu tmp[10] = {0} ;
        sub256bit_num(P_1_x , P_2_x, tmp ,9);
        sub256bit_num(p , tmp, sub_x ,9);
    }
    // cout<<"\nx_2 - x_1 is"<<endl ;
    // print_256_number(sub_x) ;

    //To compute y_2 - y_1
    llu sub_y[10] = {0} ;
    if(compareTwoBigNumbers(P_2_y , P_1_y) == 1 || compareTwoBigNumbers(P_2_y , P_1_y) == -1)
    {
        sub256bit_num(P_2_y , P_1_y , sub_y , 9);
    }
    else
    {
        llu tmp[10] = {0} ;
        sub256bit_num(P_1_y , P_2_y, tmp ,9);
        sub256bit_num(p , tmp, sub_y ,9);
    }

    //To compute sub_x^(-1) mod(p)
    llu x_coordinate_inverse[10] = {0} ;
    squareAndMultiply(sub_x , x_coordinate_inverse) ;
    // cout<<"\nx inv is"<<endl ;
    // print_256_number(x_coordinate_inverse) ;

    //lambda = (sub_y * x_coordinate_inverse)mod p
    llu lambda_tmp[20] = {0} ;
    multiply256bit_num(sub_y , x_coordinate_inverse , lambda_tmp) ;
    barrett_reduction(lambda_tmp , lambda) ;
    // cout<<"\nlambda is"<<endl ;
    // print_256_number(lambda) ;

    //compute lambda^2 mod(p)
    llu square_lambda[10] = {0} ;
    llu tmp_square_lambda[20] = {0} ;
    multiply256bit_num(lambda,lambda,tmp_square_lambda) ;
    barrett_reduction(tmp_square_lambda , square_lambda) ;

    //To compute P_1_x + P_2_x
    llu sum_x_coordinates[10] = {0} ;
    llu tmp_sum_x_coordinates[10] = {0} ;
    add256bit_num(P_1_x, P_2_x , tmp_sum_x_coordinates,9) ;
    barrett_reduction(tmp_sum_x_coordinates , sum_x_coordinates) ;

    //To compute lambda^2 - sum_x_coordinates


    if(compareTwoBigNumbers(square_lambda , sum_x_coordinates) == 1 || compareTwoBigNumbers(square_lambda , sum_x_coordinates) == -1)
    {
        sub256bit_num(square_lambda , sum_x_coordinates , P_3_x , 9);
    }
    else
    {
        llu tmp[10] = {0} ;
        sub256bit_num(sum_x_coordinates , square_lambda, tmp ,9);
        sub256bit_num(p , tmp, P_3_x ,9);
    }

    //To compute x_1 - x_3

    llu sub_1_3[10] = {0} ;


    if(compareTwoBigNumbers(P_1_x , P_3_x) == 1 || compareTwoBigNumbers(P_1_x , P_3_x) == -1)			//y3=lambda*(x1-x3)-y1
    {
        sub256bit_num(P_1_x , P_3_x , sub_1_3,9);
    }
    else
    {
        llu tmp[10] = {0} ;
        sub256bit_num(P_3_x , P_1_x, tmp,9);
        sub256bit_num(p , tmp, sub_1_3,9);

    }
    //to compute lambda*sub_1_3
    llu tmp_mult_lambda_sub_1_3[20] = {0} ;
    llu mult_lambda_sub_1_3[10] = {0} ;
    multiply256bit_num(lambda,sub_1_3,tmp_mult_lambda_sub_1_3) ;
    barrett_reduction(tmp_mult_lambda_sub_1_3, mult_lambda_sub_1_3) ;

    //to compute mult_lambda_sub_1_3 - y_1
    if(compareTwoBigNumbers(mult_lambda_sub_1_3 , P_1_y) == 1 || compareTwoBigNumbers(mult_lambda_sub_1_3 , P_1_y) == -1)			//y3=lambda*(x1-x3)-y1
    {
        sub256bit_num(mult_lambda_sub_1_3 , P_1_y , P_3_y,9);
    }
    else
    {
        llu tmp[9] = {0} ;
        sub256bit_num(P_1_y , mult_lambda_sub_1_3, tmp,9);
        sub256bit_num(p , tmp, P_3_y,9);

    }


}


void ECC_Group_Point_Doubling(llu *P_x , llu *P_y , llu *x3 , llu *x5)
{
    long long int y[10]={0},x[10]={0},redu_px1[10]={0},r[10]={0},x4[10]={0},new_x3[10]={0},new_px[10]={0};
    long long int p[10]={1073741823, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535};
    long long int p2[10]={1073741820, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535};
    llu three[10]={3,0,0,0,0,0,0,0,0,0};
    llu two[10]={2,0,0,0,0,0,0,0,0,0};
    long long int mul_px[20]={0},redu_px[10]={0},add_p2[10]={0},inv_y1[10]={0},lambda[10]={0},lambda1[10]={0},x1[10]={0},new_x1[10]={0};
    int i;

    llu tmp_square_x[20] = {0} ;
    llu square_x[10] = {0} ;
    multiply256bit_num(P_x , P_x , tmp_square_x);
    barrett_reduction(tmp_square_x,square_x);

    llu tmp_three_x_square[20] = {0} ;
    llu three_x_square[10] = {0} ;
    multiply256bit_num(square_x , three , tmp_three_x_square);

    barrett_reduction(tmp_three_x_square,three_x_square);
    add256bit_num(three_x_square , three , add_p2 , 9);

    llu three_x_square_plus_a[10] ={0} ;
    barrett_reduction(add_p2 , three_x_square_plus_a);
    //(3*x1^2+A)
    for(i=0;i<10;i++)
    {
        redu_px[i]=0;
    }
    for(i=0;i<20;i++)
    {
        mul_px[i]=0;
    }

    llu tmp_two_P_y[20] = {0} ;
    llu two_P_y[10] = {0} ;
    multiply256bit_num(two , P_y , tmp_two_P_y);
    barrett_reduction(tmp_two_P_y,two_P_y);
    squareAndMultiply(two_P_y , inv_y1);

    llu tmp_lambda[20] = {0} ;
    multiply256bit_num(three_x_square_plus_a , inv_y1 , tmp_lambda);
    barrett_reduction(tmp_lambda,lambda);

    llu tmp_square_lambda[20]={0} ;
    llu square_lambda[10] = {0} ;
    multiply256bit_num(lambda , lambda , tmp_square_lambda);
    barrett_reduction(tmp_square_lambda , square_lambda);
    llu tmp_x1[11] = {0} ;
    add256bit_num(P_x , P_x , tmp_x1,9);

    barrett_reduction(tmp_x1 , x1);

    if(compareTwoBigNumbers(square_lambda , x1) == 1 || compareTwoBigNumbers(square_lambda , x1) == -1)			// x1 is addition of x1 and x2
    {
        sub256bit_num(square_lambda , x1 , x3,9);
    }
    else											// x3 is the x co-ordinate of new point
    {											// x3=lambda*lambda-x1-x2
        llu temp[10] = {0} ;
        sub256bit_num(x1 , square_lambda , temp,9);
        sub256bit_num(p , temp, x3,9);

    }


    // y co-ordinate..........................


    for(i=0;i<9;i++)
        new_x1[i]=P_x[i];
    for(i=0;i<9;i++)
        redu_px1[i]=x3[i];

    llu sub_x_1_x_3[10] = {0} ;


    if(compareTwoBigNumbers(P_x , x3) == 1 || compareTwoBigNumbers(P_x , x3) == -1)			//y3=lambda*(x1-x3)-y1
    {
        sub256bit_num(P_x , x3 , sub_x_1_x_3,9);
    }
    else
    {
        sub256bit_num(x3 , P_x, r,9);
        sub256bit_num(p , r, sub_x_1_x_3,9);
        for(i=0;i<10;i++)
        {
            r[i]=0;
        }

    }
    for(i=0;i<20;i++)
    {
        mul_px[i]=0;
    }
    for(i=0;i<10;i++)
    {
        redu_px[i]=0;
    }

    llu tmp_lambda_mult_x_1_sub_x_3[20] = {0} ;
    llu lambda_mult_x_1_sub_x_3[10] = {0} ;
    multiply256bit_num(lambda , sub_x_1_x_3 , tmp_lambda_mult_x_1_sub_x_3);
    barrett_reduction(tmp_lambda_mult_x_1_sub_x_3 , lambda_mult_x_1_sub_x_3);
    for(i=0;i<10;i++)
    {
        new_x1[i]=0;
        redu_px1[i]=0;
    }
    for(i=0;i<9;i++)
    {
        new_x1[i]=redu_px[i];
        redu_px1[i]=P_y[i];
    }
    if(compareTwoBigNumbers(lambda_mult_x_1_sub_x_3 , P_y) == 1 || compareTwoBigNumbers(lambda_mult_x_1_sub_x_3 , P_y) == -1)
    {
        sub256bit_num(lambda_mult_x_1_sub_x_3 , P_y , x5,9);
    }
    else									// x5 is the y co-ordinate of new point
    {
        sub256bit_num(P_y , lambda_mult_x_1_sub_x_3 , r,9);
        sub256bit_num(p , r, x5,9);
    }

}
void doubling_and_adding(llu *P_x , llu *P_y , llu *scalar , llu *scalar_mult_x , llu *scalar_mult_y)
{
 llu m ;
 llu z_x[10]={0},z_y[10]={0},outputx[10]={0},outputy[10]={0},qx[10]={0},qy[10]={0};
 int c,i,n;

 for(unsigned i=0;i<9;i++)
 {
 	qx[i]=P_x[i];
 	qy[i]=P_y[i];
 }

 for(unsigned i=0;i<9;i++)
 {
 	z_x[i]=P_x[i];
 	z_y[i]=P_y[i];
 }

 n = get_bit_length(scalar);
 for(m=n-2;m>=0;m--)
 {
 	c=GET_THE_BIT(scalar,m);
 	ECC_Group_Point_Doubling(z_x , z_y , outputx , outputy);
 	for(unsigned i=0;i<9;i++)
 	{
 		z_x[i] = outputx[i];
 		z_y[i] = outputy[i];
 	}
 	z_x[9]=0;
 	z_y[9]=0;
 	for(i=0;i<10;i++)
 	{
 		outputx[i]=0;
 		outputy[i]=0;
 	}
 	if(c==1)
 	{
        )	ECC_Group_Point_Addition(z_x , z_y , qx , qy ,outputx , outputy);
 		for(i=0;i<9;i++)
 		{
 			z_x[i] = outputx[i];
 			z_y[i] = outputy[i];
 		}
 		z_x[9]=0;
	 	z_y[9]=0;
 		for(i=0;i<10;i++)
 		{
 			outputx[i]=0;
 			outputy[i]=0;
 		}
 	}
 }
 for(i=0;i<9;i++)
 {
 	scalar_mult_x[i] = z_x[i];
 	scalar_mult_y[i] = z_y[i];
 }
}

void Key_Generation(llu* public_key_x , llu* public_key_y)
{
    llu px[9]={412664470,
        310699287,
        515062287,
        14639179,
        608236151,
        865834382,
        69500811,
        880588875,
        27415};
    llu py[9]={935285237,
        785973664,
        857074924,
        864867802,
        262018603,
        531442160,
        670677230,
        280543110,
        20451};
    unsigned char scalar[32] = {187,72,238,175,133,119,128,185,114,78,124,20,248,239,134,167,77,220,35,154,179,49,194,250,202,189,27,202,18,129,151,202} ; //in base 256
    llu scalar_base[9] = {0} ; //base in 2^30
    change_base_to_2_power_30(scalar,scalar_base) ;

    doubling_and_adding(px,py,c,public_key_x,public_key_y) ;

}

void schnorr_sign()






//void base_change_from_hex_to_256()



int main()
{
    // unsigned char a[32] = {'S','A','M','I',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
    //unsigned char a[32] = {173,21,0,242,97,255,16,180,156,122,23,150,163,97,3,176,35,34,174,93,222,64,65,65,234,207,1,143,191,22,120,186} ;
    unsigned char a[32] = {187,72,238,175,133,119,128,185,114,78,124,20,248,239,134,167,77,220,35,154,179,49,194,250,202,189,27,202,18,129,151,202} ;
    unsigned char b[32] = {3,6,98,85,80,184,3,89,77,139,123,151,187,152,114,52,193,243,82,214,155,195,96,140,36,63,76,46,252,32,142,251} ;
    //unsigned char b[32] = {173,21,0,242,97,255,16,180,156,122,23,150,163,97,3,176,35,34,174,93,222,64,65,65,234,207,1,143,191,22,120,186} ;
    llu tst_1[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1} ; // b^n+1 = (2^30)^10


    llu add[10]={0} ;
    // long long int sub[11]={0} ;
    // long long int sub_1[11]={0} ;
    //
    llu c[11] = {0} ; llu d[11] = {0} ;
    // long long int e[11] = {2,0,0,0,0,0,0,0,0,0,0} ;
    // long long int f[11] = {4,0,0,0,0,0,0,0,0,0,0} ;
    // llu p[10] = {1073741823, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535,0} ; //for curve p-256
    //llu test[10] = {0} ;
    //llu bPowerTen[20] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0} ; // b^n+1 = (2^30)^10
     llu bPowerTen[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,0,0,0,0,0,0,0,0,0} ;
    llu remainder[11] = {0} ;

    change_base_to_2_power_30(a,c) ;
    change_base_to_2_power_30(b,d) ;


    add256bit_num(d,c,add) ;

    // cout<<"the added value in 2^30 base is"<<endl ;
    //
    // for(unsigned i=0 ; i< 10 ; i++)
    // {
    //     cout<<" ,"<<add[i] ;
    // }
    // cout<<endl ;
   //  cout<<"f is"<<endl ;
   // for(unsigned i=0 ; i< 11 ; i++)
   // {
   //     cout<<" ,"<<std::hex<<(f[i]&ALL_ONE_30BIT)  ;
   // }
   // cout<<endl ;
   //
   //  cout<<"e is"<<endl ;
   // for(unsigned i=0 ; i< 11 ; i++)
   // {
   //     cout<<" ,"<<std::hex<<(e[i]&ALL_ONE_30BIT)  ;
   // }
   // cout<<endl ;
   //
   //  sub256bit_num(d,c,sub_1,11) ;
   //  cout<<"the subtracted_1 value in 2^30 base is"<<endl ;
   //
   // for(unsigned i=0 ; i< 11 ; i++)
   // {
   //     cout<<" ,"<<std::dec<<(sub_1[i]&ALL_ONE_30BIT)  ;
   // }
   // cout<<endl ;

   // for(unsigned i=0 ; i< 11 ; i++)
   // {
   //     cout<<" ,"<<std::hex<<(sub_1[i]&ALL_ONE_30BIT)  ;
   // }
   // cout<<endl ;
   //  subtract(e,f,sub) ;
   //  cout<<"the subtracted value in 2^30 base is"<<endl ;
   //
   // for(unsigned i=0 ; i< 11 ; i++)
   // {
   //     cout<<" ,"<<sub[i]  ;
   // }
   // cout<<endl ;
   //cout<<"check= "<<check<<endl ;

   /*add256bit_num(sub,p,test) ;
   cout<<"the subtracted test value in 2^30 base is"<<endl ;

   for(unsigned i=0 ; i< 9 ; i++)
   {
       cout<<"test["<<i<<"]"<<test[i]<<endl ;
   }*/
    // llu mult[20]={0} ;
    // multiply256bit_num(c,d,mult) ;
    // cout<<"the 2^30 base representation of the multiplication is "<<endl ;
    // for(unsigned i=0 ; i<20 ; i++)
    // {
    //     cout<<" "<<std::dec<<mult[i] ;
    // }
    // cout<<endl ;
    //
    // barrett_reduction(bPowerTen,remainder) ;
    //
    // cout<<"The modulo value in 2^30 base is"<<endl ;
    // for(int i=0 ; i<9 ; i++)
    // {
    //     cout<<"  "<<std::dec<<remainder[i] ;
    // }
    // cout<<endl ;
    //
    // llu aPower[11]={1,0,0,0,0,0,0,0,0,0,0} ;
    // squareAndMultiply(c,aPower) ;
    // cout<<"The a^(p-2)modp value in 2^30 base is"<<endl ;
    // for(int i=0 ; i<10 ; i++)
    // {
    //     cout<<"  "<<aPower[i] ;
    // }
    // cout<<endl ;
    // long long int alice[9] = {775950223, 1039104322, 927144646, 452245582, 1056047366, 844078672, 339464557, 3249} ;
    // long long int bob[9] = {393509683, 245659113, 1070193796, 731301130, 359258151, 692055663, 789261178, 3322} ;
    //
    llu tmp_x[9]={0} ;
    llu tmp_y[9] = {0} ;
    //
    // ECC_Group_Point_Addition(c,c,d,d,tmp_x,tmp_y) ;
    // printf("\ntemp x co-ordinate is:\n");
    // for(unsigned i=0;i<9;i++)
    //     printf("%lld ",tmp_x[i]);
    // printf("\n");
    // printf("\ntmp y co-ordinate is:\n");
    // for(unsigned i=0;i<9;i++)
    //     printf("%lld ",tmp_y[i]);
    // printf("\n");
    //
    // llu tmp_x1[9]={0} ;
    // llu tmp_y1[9] = {0} ;
    //
    // ECC_Group_Point_Doubling(c,c,tmp_x1,tmp_y1) ;
    // printf("\ntemp x co-ordinate is:\n");
    // for(unsigned i=0;i<9;i++)
    //     printf("%lld ",tmp_x1[i]);
    // printf("\n");
    // printf("\ntmp y co-ordinate is:\n");
    // for(unsigned i=0;i<9;i++)
    //     printf("%lld ",tmp_y1[i]);
    // printf("\n");

    llu px[9]={412664470,
        310699287,
        515062287,
        14639179,
        608236151,
        865834382,
        69500811,
        880588875,
        27415};
    llu py[9]={935285237,
        785973664,
        857074924,
        864867802,
        262018603,
        531442160,
        670677230,
        280543110,
        20451};
    llu p1x[9]={124164472,
        405611505,
        1059173210,
        576354461,
        890946496,
        148900882,
        888662181,
        516301632,
        31986};
    llu p1y[9]={578319313,
        940760692,
        244851353,
        527137167,
        875617210,
        912988797,
        755237523,
        356792035,
        1911};
    llu y[9]={0},x[9]={0} ;
    llu alice[9] = {775950223, 1039104322, 927144646, 452245582, 1056047366, 844078672, 339464557, 3249},alice_key[9]={0},alice_key1[9]={0};
    llu bob[9] = {393509683, 245659113, 1070193796, 731301130, 359258151, 692055663, 789261178, 3322},bob_key[9]={0},bob_key1[9]={0};
    llu p[10]={1073741823, 1073741823, 1073741823, 63, 0, 0, 4096, 1073725440, 65535,0},x1[10]={0},x3[9]={0},x4[9]={0},x5[9]={0};
    // llu tmp_x[9]={0} ;
    // long long int tmp_y[9]={0} ;

    /*long long int ali[9] = {804145339,637656598,130344747,565968389,601640359,147246696,1004318636,541373062,51863} ;
    long long int boo[9] = {358745603,604954945,934851797,480653029,317964596,51277657,66209990,138349459,64398} ;
    int i,s,j;
    different_point(ali , ali ,boo,boo, tmp_x , tmp_y) ;
    printf("\ntemp x co-ordinate is:\n");
    for(i=0;i<9;i++)
        printf("%lld ",tmp_x[i]);
    printf("\n");
    printf("\ntmp y co-ordinate is:\n");
    for(i=0;i<9;i++)
        printf("%lld ",tmp_y[i]);
    printf("\n");	*/
    doubling_and_adding(px , py , c , x3 , x5);
    doubling_and_adding(x3 , x5 , d , alice_key , alice_key1);

    cout<<"for d(cP) "<<endl ;
    printf("\nAlice x co-ordinate is:\n");
    print_256_number(alice_key) ;
    // for(unsigned i=0;i<9;i++)
    //     printf("%lld ",alice_key[i]);
    // printf("\n");
    printf("\nAlice y co-ordinate is:\n");
    print_256_number(alice_key1) ;
    // for(unsigned i=0;i<9;i++)
    //     printf("%lld ",alice_key1[i]);
    // printf("\n");
    for(unsigned i=0;i<9;i++)
    {
        x3[i]=0;
        x5[i]=0;
    }
    doubling_and_adding(px , py , d , x3 , x5);
    doubling_and_adding(x3 , x5 , c , bob_key , bob_key1);

    cout<<"\nfor c(dP) "<<endl ;
    printf("\nBob x co-ordinate is:\n");
    print_256_number(bob_key) ;
    // for(unsigned i=0;i<9;i++)
    //     printf("%lld ",bob_key[i]);
    // printf("\n");
    printf("\nBob y co-ordinate is:\n");
    print_256_number(bob_key1) ;
    // for(unsigned i=0;i<9;i++)
    //     printf("%lld ",bob_key1[i]);
    // printf("\n");
    cout<<endl ;


    return 0 ;


}
