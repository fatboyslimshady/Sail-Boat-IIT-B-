// let's build a sail boat //
// using use inputs to control the boat
// only one affecting factor added - the wind
#include<simplecpp>
#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
#include<map>
#include<stdlib.h>
vector<vector<Text*> >t1;
double va,acc,T,dcc;
int alpha;
class HUD : public Composite{
	Rectangle *body;
	Line *l1,*l2,*l3;
	Text *t1,*t2,*t3,*t5,*t6;
	public:	HUD(double x,double y,Composite* owner=NULL):Composite(x,y,owner){
			body = new Rectangle(0,0,200,100,this);
			body->setColor(COLOR("green"));
            body->setFill();
			t1 = new Text (-20,-30,"Boat Speed", this);
			t2 = new Text (-20,0,"Wind Angle", this);
			t3 = new Text (-20,30,"Wind Speed", this);
		}
		void display(int windspeed,int windangle)
		{

			t5 = new Text (30,0,windangle,this);
			t6 = new Text (30,30,windspeed,this);
		}
};
class triangle : public Composite {
	Polygon *body;
	public:	triangle(double x, double y,Color c,Composite* owner=NULL):Composite(x,y,owner){
		double bodyV[3][2]{{-10,10},{0,-10},{10,10}};
		body = new Polygon(0,0,bodyV,3,this);
		body->setColor(c);
		body->setFill();
	}
	void invert(void){
		body->right(180);
	}
};

class scrollBar : public Composite {
	public :triangle *t1,*t2;
		Rectangle *bar,*slider;

		scrollBar(double x, double y, Composite* owner=NULL):Composite(x,y,owner){
				bar = new Rectangle(0,0,10,400,this);
				slider= new Rectangle(0,175,15,50,this);
				slider->setColor(COLOR("black"));
				slider->setFill();
				t1= new triangle(0,-207,COLOR("black"),this);
				t2= new triangle(0,207,COLOR("black"),this);
				t2->invert();
			}
		int posX(){
			int x=slider->getX();

			return x;
		}
		int posY(){
			int y=slider->getY();
			return y;
		}
};
class arena : public Composite {
    Rectangle *body;
    Circle *c1;
	public :
		arena(double x,double y,Composite* owner=NULL): Composite(x,y,owner){
            body = new Rectangle(0,0,2560,1440,this);
            body->setColor(COLOR(0,0,255));
            body->setFill();
			int space=-720 ,vspace=-1280;
			for(int i=0;i<33;i++){
			vector<Text*>temp;
			for(int j=0;j<19;j++)
			{
				temp.push_back(new Text(vspace,space,"+",this));
				space+=80;
			}
			vspace+=80;
			space=-720;
			t1.push_back(temp);
			}
            c1 = new Circle(0,0,100,this);
            c1->setColor(COLOR(0,128,0));
            c1->setFill();
		}

};

class Sail : public Composite{
	Line *mast;
	double a,b;
	public:	Sail(double x,double y,Composite* owner=NULL): Composite(x,y,owner){
	mast= new Line(0,0,-30,0,this);
	mast->setColor(COLOR(255,255,0));
	mast->setFill();
	}
};
class Rudder : public Composite {
        Line *flap;
        double max_left,max_right;
 	public:
        Rudder(double x,double y,Composite* owner=NULL): Composite(x,y,owner){
        flap = new Line(-25,0,-35,0,this);
        max_left=0;
        max_right=0;
	}
	void move_left(double angle){
		if(max_left<5){
		flap->left(angle);
		max_left++;
		max_right--;
		}
	}
	void move_right(double angle){
		if(max_right<5){
		flap->right(angle);
		max_right++;
		max_left--;
		}

	}
	void halt(double angle){
		flap->left(angle);
	}
};
class boat : public Composite {					// Class Boat
	Polygon *body;
	Rudder *flap;
	public:	Sail *mast;
		boat(double x, double y,Composite* owner=NULL):Composite(x,y,owner){
		double bodyV[6][2]{{-28,0},{-25,-7.25},{15,-10},{37.5,0},{15,10},{-25,7.25}};

		body = new Polygon(0,0,bodyV,6,this);
		body->setColor(COLOR(165,42,42));
		body->setFill();
		flap = new Rudder(0,0,this);
		mast = new Sail(20,0,this);
	}
	void move_forward(double speed){
		Composite::forward(speed);
	}
	void move_left(double angle){
		Composite::left(angle);
		flap->move_right(angle);
	}
	void move_right(double angle){
		Composite::right(angle);
		flap->move_left(angle);

	}
	std::vector<double>sail;
	void halt(vector<double> &sail){
    		sail[0]=sail[0]-(.081*sail[0]*sail[0]);
	//	flap->halt(90);
	}
	void destroy(){
		cout<<"boat is succesfully destroyed"<<endl;
		delete body;
	}
};
double getCl(int aot){
	map<int,float>cl;
	cl.insert(pair<int,float>(0,0));
	cl.insert(pair<int,float>(5,0));
	cl.insert(pair<int,float>(10,0.15));
	cl.insert(pair<int,float>(15,0.90));
	cl.insert(pair<int,float>(20,1.43));
	cl.insert(pair<int,float>(25,1.57));
	cl.insert(pair<int,float>(30,1.43));
	cl.insert(pair<int,float>(35,1.39));
	cl.insert(pair<int,float>(40,1.30));
	cl.insert(pair<int,float>(45,1.15));
	cl.insert(pair<int,float>(50,0.95));
	cl.insert(pair<int,float>(55,0.82));
	cl.insert(pair<int,float>(60,0.72));
	cl.insert(pair<int,float>(65,0.58));
	cl.insert(pair<int,float>(70,0.45));
	cl.insert(pair<int,float>(75,0.35));
	cl.insert(pair<int,float>(80,0.29));
	cl.insert(pair<int,float>(85,0));
	cl.insert(pair<int,float>(90,0));
	return cl[aot];

}
double getCd(int aot){
	map<int,float>cd;
	cd.insert(pair<int,float>(0,0));
	cd.insert(pair<int,float>(5,0));
	cd.insert(pair<int,float>(10,0.15));
	cd.insert(pair<int,float>(15,0.16));
	cd.insert(pair<int,float>(20,0.18));
	cd.insert(pair<int,float>(25,0.20));
	cd.insert(pair<int,float>(30,0.22));
	cd.insert(pair<int,float>(35,0.35));
	cd.insert(pair<int,float>(40,0.45));
	cd.insert(pair<int,float>(45,0.50));
	cd.insert(pair<int,float>(50,0.56));
	cd.insert(pair<int,float>(55,0.66));
	cd.insert(pair<int,float>(60,0.78));
	cd.insert(pair<int,float>(65,0.85));
	cd.insert(pair<int,float>(70,1.00));
	cd.insert(pair<int,float>(75,1.15));
	cd.insert(pair<int,float>(80,1.31));
	cd.insert(pair<int,float>(85,1.33));
	cd.insert(pair<int,float>(90,1.33));
	return cd[aot];
}
inline void calculate(vector<double> &sail,double &va,double aot,double T,double Cl,double Cd){

	acc=0.003748*va*va*(Cl*sin(aot*0.0174533)-Cd*cos(aot*0.0174533));
	sail[0]+=acc*T;
	cout<<"accelerating at "<<acc<<endl;
}

int game_area(void){
	beginFrame();
	arena m(1280,720);
	scrollBar s(100,360);
	HUD h(1180,50);
	Text t1(60,185,"90 D"),t2(60,360,"45 D"),t3(60,535,"0 D");
	Line l1(100,40,150,40);
	boat b(640,320);
	b.setScale(2.0);
	endFrame();
	vector<double>wind(2);
		wind[0]=20; // wind speed
		wind[1]=40; // wind angle
	b.sail.push_back(0);
	b.sail.push_back(57.2985*b.getOrientation());
	int sailAngle=0;
	l1.right(wind[1]);
	int angleTomove=0;
	clock_t start,end;
	double x;
	double cpu_time_used;

        while(1){
		start=clock();
		beginFrame();
		int theta=0; //angle between boat and true wind ;
		int omega=0;//new
		int aot=0; //angle of attack ;
		double cl,cd;
		sailAngle=57.2985*b.mast->getOrientation();
		cout<<"sail orientation"<<sailAngle<<endl;
		b.sail[1]=b.getOrientation();//new
		cout<<"bsail "<<b.sail[0]<<" wind "<<wind[0];//new
        theta=(57.2958*b.sail[1])-wind[1];//new
        theta=180-theta;//new
        cout<<"theta"<<theta;//new
        theta=0.0174*theta;//new
        x=pow(b.sail[0],2)+pow(wind[0],2)+(2*b.sail[0]*wind[0]*cos(theta));//new
        va=pow(x,0.5);//new
		alpha=atan2((wind[0]*sin(theta)),(b.sail[0]+wind[0]*cos(theta)));//angle of apparent wind ;
		alpha*=57.2985;
        theta=57.2985*theta;//new
        omega=theta-alpha;//new
        aot=omega+sailAngle;
        aot=abs(aot);//new
		int rem=aot%5;
		if(rem<3)
			aot-=rem;
		else
			aot+=(5-rem);
		cl=getCl(aot);
		cd=getCd(aot);
		calculate(b.sail,va,aot,T,cl,cd);
		cout<<"boat speed :"<<b.sail[0]<<endl;
		cout<<"apparent wind speed "<<va<<endl;
		cout<<"angle of attack "<<aot<<endl;
		cout<<"Ttime "<<T<<endl;
		cout<<"cl "<<cl<<endl;
		cout<<"cd "<<cd<<endl;
		cout<<"angle of apparent wind "<<alpha<<endl;
		cout<<"theta"<<theta<<endl;

		h.display(wind[0],wind[1]);
		XEvent event;
                if(checkEvent(event)){

					if(keyPressEvent(event)){
                				 char c = charFromEvent(event);

						 if(c=='a'){
								b.move_left(5);
						 }
                				 if(c=='d'){
								b.move_right(5);
						 }
                				 if(c==' '){
								b.halt(b.sail);
								m.move(0,0);
						 }
						if(c==27)
								exit(0);
						if(c=='w'){
							if(s.slider->getY()>-175)
								s.slider->move(0,-25);
							if(angleTomove<90){
								angleTomove+=5;
								if((theta>=180&&theta<=330)||(theta<0&&theta>-35)){
									b.mast->right(5);

								}
								if(theta>=0&&theta<180)
								{
									b.mast->left(5);
								}
							}
						}
						if(c=='s'){
							if(s.slider->getY()<175)
								s.slider->move(0,25);
							if(angleTomove>0){
								angleTomove-=5;
								if((theta>=180&&theta<=330)||(theta<0&&theta>-35)){
										b.mast->left(5);
								}
								if(theta>=0&&theta<180){

										b.mast->right(5);
																	}
								}
							}
			        	        }
		}
		if(theta>=0&&theta<180){
			if(sailAngle>=0){
				b.mast->left(sailAngle);
				b.mast->left(sailAngle);
			}

		}
		if((theta>=180&&theta<=330)||(theta<0&&theta>-35)){
			if(sailAngle<0){
				b.mast->right(sailAngle);
				b.mast->right(sailAngle);
			}

		}


		b.sail[1]=57.2985*b.getOrientation();
        cout<<"boat angle"<<b.sail[1]<<endl;
		cout<<"--------------------------------------------------------\n";
		if((int)b.sail[1]>=0&&(int)b.sail[1]<=90){
			double dx,dy;
			dx=b.sail[0]*cos(b.getOrientation());
			dy=b.sail[0]*sin(b.getOrientation());
			m.move(-dx,-dy);
		}
		else if((int)b.sail[1]>90&&(int)b.sail[1]<=180){
			double dx,dy;
			double newangle;
			newangle=180-b.sail[1];
			newangle*=0.0174533;
			dx=b.sail[0]*cos(newangle);
			dy=b.sail[0]*sin(newangle);
			m.move(dx,-dy);
		}
		else if((int)b.sail[1]<=-90&&(int)b.sail[1]>-185){
			double dx,dy,newangle;
			newangle=180+b.sail[1];
			newangle*=0.0174533;
			dx=b.sail[0]*cos(newangle);
			dy=b.sail[0]*sin(newangle);
			m.move(dx,dy);

		}
		else if((int)b.sail[1]<0&&(int)b.sail[1]>-90){
			double dx,dy;
			dx=b.sail[0]*cos(-b.getOrientation());
			dy=b.sail[0]*sin(-b.getOrientation());
			m.move(-dx,dy);
		}
		endFrame();
		end=clock();
		cpu_time_used=(end-start)/(double)CLOCKS_PER_SEC * 1000;
		T=cpu_time_used*0.001;
	//	cout<<T<<endl;
			wait(0.015897667);
	}
	cout<<"entering destroy fun"<<endl;
        b.destroy();
	return 0;
}
int customise_boat(void){
	int x,y,pos;
	Rectangle r1(640,175,300,120),r2(640,300,300,120),r3(640,425,300,120),r4(640,550,300,114);
	Text T1(640,175,"SMALL"),T2(640,300,"MEDIUM"),T3(640,425,"LARGE"),T4(640,550,"BACK");
	while(1){
	pos=getClick();
        x=pos/65536;
        y=pos%65536;
        if(x>=540&&x<=740&&y>=115&&y<=235)
                return 2;
        else if(x>=540&&x<=740&&y>=240&&y<=360)
                return 3;
	else if(x>=540&&x<=740&&y>=365&&y<=485)
		return 4;
	else if(x>=540&&x<=740&&y>=490&&y<=600)
		return 1;
	}
}
int boat_style(void){
        int x,y,pos;
	Rectangle r1(640,195,300,150),r2(640,355,300,150),r3(640,515,300,150);
	Text T1(640,195,"GENERIC BOAT"),T2(640,355,"CUSTOMISED BOAT"),T3(640,515,"BACK");
	while(1){
	pos=getClick();
        x=pos/65536;
        y=pos%65536;
        if(x>=540&&x<=740&&y>=120&&y<=270)
                return 1;
        else if(x>=540&&x<=740&&y>=280&&y<=430)
                return 2;
	else if(x>=540&&x<=740&&y>=440&&y<=590)
		return 3;
	}
}
int main_menu(void){
	int x,y,pos;
	Rectangle r1(640,250,200,100),r2(640,500,200,100);
	Text T1(640,250,"ENTER THE GAME"),T2(640,500,"QUIT THE GAME");
	while(1){
	pos=getClick();
	x=pos/65536;
	y=pos%65536;
	if(x>=540&&x<=740&&y>=200&&y<=300)
		return 1;
	else if(x>=540&&x<=740&&y>=400&&y<=600)
		exit(0);
	}
	return 0;
}

int main(){
	int choice;
	initCanvas("Menu_Screen",1280,720);
	Rectangle r1(640,360,400,500);
	choice=main_menu();
	while(1){
		if(choice==1){
			choice=boat_style();
			if(choice==1){
				r1.hide();
				game_area();
			}
			if(choice==2){
				choice=customise_boat();
				if(choice==1)
					continue;
				r1.hide();
				game_area();
			}
			if(choice==3)
				choice=main_menu();
		}
	}
	return 0;
}

