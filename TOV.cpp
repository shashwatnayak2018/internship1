//library 
#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;
//define the equation of state
double fdensity(double p,double k,float r)
{
	//declare density
	double d;
	//the polytropic eos
	d = k*pow(p,r);
	//return density
	return d;
}
//define change in pressure funtion
double cpressure(double m, double d, double r)
{
	double x;
	double y = 1/(r+0.001);
	double z = 1/r;
	//returns the change in p
	x =1.48*m*d*(z-y);
	return x;
}
//define change in mass function
double cmass(double d, double r)
{
	double x;
	//returns the change in mass
	x =0.0125*d*(pow((r+0.001),3)-pow(r,3));
	return x;
}
//write the TOV solver functiondouble TOV(double p, double m, double d, double r)
double TOV(double p, double m, double d, double r)
{
	//base condition
	if(p<=0)
	{
		//displays the p,m,d,r
		cout<<"mass is "<<m<<" density is "<<d;
		cout<<" radi is "<<r<<" press is "<<p<<endl;
		//returns mass when p is 0
		return m;
	}
	else
	{
		//change in pressure 
		p = p - cpressure(m,d,r);
		//change in mass
		m = m + cmass(d,r);
		//the new density
		d = 2.4216*pow(p,0.6)+2.866*p;
		//cout<<p<<" ";
		//cout<<m<<" ";
		//cout<<d<<" ";
		//cout<<r<<endl;
		return TOV(p,m,d,r+0.001);
	}
}
//write the main function
int main()
{
	TOV(0.01,0,0.18136,pow(10,-10));
	ofstream outfile;
	//create dat files to storevalue
	outfile.open("data2.dat");
	//values for d_c vs M graph
	for(int i = 0;i<100;i++)
	{
		outfile<<2.4216*pow(0.01+0.03*i,0.6)+2.866*(0.01+0.03*i);
		outfile<<" ";
		outfile<<TOV(0.01+0.03*i,0,2.4216*pow(0.01+0.03*i,0.6)+ 2.866*(0.01+0.03*i),pow(10,-10))<<endl;
	}
	outfile.close();
	ofstream infile;
	//creating a dat file to store values
	infile.open("data4.dat");
	//loop to find values for p vs d graph
	for(int i = 1;i<100;i++)
	{
		infile<<i<<" "<<2.4216*pow(i,0.6)+2.866*i<<endl;
	}
	infile.close();
	return 0;
}
