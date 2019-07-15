//library
#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;
//polytropic equation of state
double eos(double k,double p,double r)
{
	//declare density
	double d;
	//write the relation
	d = k*pow(p,r);
	//return density
	return d;
}
//function to find change in mass
double cmass(double d, double r)
{
	double x;
	//returns the change in mass
	x =0.0125*d*(pow((r+0.001),3)-pow(r,3));
	return x;
}
//function to find change in p
double cpressure(double p, double m, double d, double r)
{
	double a = 3.74*pow(10,-1)*log((r*(r+0.001-2.96*m))/((r+0.001)*(r-2.96*m)));
	double b = 2.325*pow(10,-13)*p*(pow((r+0.001-2.96*m),2)-pow((r-2.96*m),2));
	double c = 8.274*pow(10,-10)*p*m;
	double e = 3.679*pow(10,-1)*p*m*m*log((r+0.001-2.96*m)/(r-2.96*m));
	double x;
	x = 1.334*(d+p)*(a+b+c+e);
	return x;
}
double TOV(double p, double m, double d, double r)
{
	//base condition
	if(p <= 0)
	{
		cout<<"pressure is "<<p<<" mass is "<<m<<" density is "<<d<<" radius is "<<r<<endl;
		//returns mass when p is 0
		return m;
	}
	else
	{
		//change in p
		p = p - cpressure(p,m,d,r);
		//change in m
		m = m + cmass(d,r);
		//new density
		d = 2.4216*pow(p,0.6)+2.866*p;
		//cout<<p<<" ";
		//cout<<m<<" ";
		//cout<<d<<" ";
		//cout<<r<<endl;
		//use recursion
		return TOV(p,m,d,r+0.001);
	}
}
int main()
{
	//TOV(0.01,0,0.1814,pow(10,-10));
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

