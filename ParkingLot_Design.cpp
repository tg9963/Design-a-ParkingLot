#include<iostream>
#include<ctime>
#include<unistd.h>
#include<string.h>

using namespace std;


//Abstract Vehicle class

class vehicle
{
	public:
		virtual int getscale()=0;
		virtual string getname()=0;
		
};


//Four_wheeler class

class four_wheeler: public vehicle
{
	//int vno;
	private:
	  string vno;	
	  int scale;
	public: 
	
	four_wheeler(string vno)
	{
		this->vno=vno;
		this->scale=10;
	}
	
	int getscale()
	{
		return this->scale;
	}
	string getname()
	{
		return this->vno;
	}
};


class three_wheeler: public vehicle
{
	//int vno;
	private:
	  string vno;	
	  int scale;
	public: 
	
	three_wheeler(string vno)
	{
		this->vno=vno;
		this->scale=5;
	}
	
	int getscale()
	{
		return this->scale;
	}
	
	string getname()
	{
		return this->vno;
	}
};

class two_wheeler: public vehicle
{
	//int vno;
	private:
	  string vno;	
	  int scale;
	public: 
	
	two_wheeler(string vno)
	{
		this->vno=vno;
		this->scale=3;
	}
	
	int getscale()
	{
		return this->scale;
	}
	
	string getname()
	{
		return this->vno;
	}
};


class ParkingLotBase
{
	private:
		double price_per_sec;
		int pnum;
	public:
		ParkingLotBase();
		double getPrice();
		int getPnum();
		void setPnum(int val);
		void set_price_per_sec(double val);
		void left();
		void remaining();
};


ParkingLotBase::ParkingLotBase()
{
	pnum = 100;
	price_per_sec = 0.01;
}

void ParkingLotBase::setPnum(int val)
{
	pnum = val;
}

void ParkingLotBase::set_price_per_sec(double val)
{
	price_per_sec = val;
}

void ParkingLotBase::left()
{
	this->pnum ++;
}


void ParkingLotBase::remaining()
{
	cout<<"The parking left is "<<this->pnum<<endl;
}


int ParkingLotBase::getPnum()
{
	//cout<<"Welcome to the Parking Lot!"<<endl;
	if(this->pnum <= 0)
	{
		cout<<"Sorry We are FULL!"<<endl;
		return 0;
	}
	this->pnum--;
	//cout<<"Please Notice the Parking Price is "<<this->price_per_sec<<" bucks per second "<<endl;
	return this->pnum;
}

double ParkingLotBase::getPrice()
{
	return this->price_per_sec;
}


class ParkingLotTicket: public ParkingLotBase
{
	private:
		int ticID;
		time_t arrive_time;
		time_t leave_time;
		double total_time;
		double charge;
	public:
		ParkingLotTicket(ParkingLotBase a,vehicle* vh);
		double getTotalTime();
		double getCharge(ParkingLotBase a,vehicle* vh);
};


ParkingLotTicket::ParkingLotTicket(ParkingLotBase a,vehicle* vh)
{
	ticID = a.getPnum();
	cout<<"vehicle "<<vh->getname()<<", your Ticket ID is "<<ticID<<endl;
	arrive_time = time(0);
}

double ParkingLotTicket::getTotalTime()
{
	this->leave_time = time(0);
	this->total_time = difftime(this->leave_time,this->arrive_time);

	return total_time;
}

double ParkingLotTicket::getCharge(ParkingLotBase a,vehicle* vh)
{
	this->total_time = this->getTotalTime();
	this->charge = this->total_time * a.getPrice() * vh->getscale();
	cout<<endl<<endl<<"****************"<<endl;
	cout<<"BILL: "<<endl;
	cout<<" Ticket ID "<<this->ticID<<endl;
	cout<<" Vehicle: "<<vh->getname()<<endl;
	cout<<"Please Pay "<<this->charge<<" for Parking "<<this->total_time<<" seconds of time "<<endl;
	cout<<"Thank you"<<endl;
	cout<<"****************"<<endl;
	this->left();
	return this->charge;
}


int main()
{
	
	cout<<"Welcome to the Parking Lot!"<<endl;
	
	
	//creating parkinglots for different sections
	
	ParkingLotBase four_wheeler_section,three_wheeler_section,two_wheeler_section;
	
	
	//Assigning number of spaces available in each section
	
	four_wheeler_section.setPnum(10);
	four_wheeler_section.set_price_per_sec(15);		// price per second in this section
	
	three_wheeler_section.setPnum(20);
	three_wheeler_section.set_price_per_sec(10);
	
	two_wheeler_section.setPnum(15);
	two_wheeler_section.set_price_per_sec(1);
	
	
	vehicle *vptr1,*vptr2,*vptr3;
	
	four_wheeler jeep("jeep_1502");				// creating objects for vehichles with name of vechicle
	three_wheeler car("car_1102");
	two_wheeler   bike("bike_182");
	
	vptr1=&jeep;
	
	ParkingLotTicket at1(four_wheeler_section,vptr1);		// Taking a ticket for a vehicle
	sleep(10);											//parking the vehicle

	vptr2=&car;
	
	ParkingLotTicket at2(three_wheeler_section,vptr2);
	sleep(5);
	
	vptr3=&bike;
	
	ParkingLotTicket at3(two_wheeler_section,vptr3);
	sleep(5);
	
	at2.getCharge(three_wheeler_section,vptr2);		//get the charge for parking vehicle for a specified amount of time
	at1.getCharge(four_wheeler_section,vptr1);
	at3.getCharge(two_wheeler_section,vptr3);
	
	return 0;
}
