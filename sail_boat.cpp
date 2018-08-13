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
		double bodyV[3][2]={{-10,10},{0,-10},{10,10}};
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
				slider= new Rectangle(0,180,15,40,this);
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
     Polygon *decoy,*p1;
     Circle *c1;

	public :
		arena(double x,double y,Composite* owner=NULL): Composite(x,y,owner){
            cout<<"MAP ORIGIN "<<x<<","<<y<<endl;
            body = new Rectangle(0,0,5120,2880,this);
            body->setColor(COLOR(0,0,255));
            body->setFill();
			int space=-1440 ,vspace=-2560;
			for(int i=0;i<17;i++){
			vector<Text*>temp;
			for(int j=0;j<10;j++)
			{
				temp.push_back(new Text(vspace,space,"+",this));
				space+=320;
			}
			vspace+=320;
			space=-1440;
			t1.push_back(temp);
			}
            double island[24][2]={{676,-181},{606,-350},{495,-495},{350,-606},{181,-676},{0,-700},{-181,-676},{-350,-606},{-495,-495},{-606,-350},{-676,-181},{-700,0},{-676,181},{-606,350},
{-495,495},{-350,606},{-181,676},{0,700},{181,676},{350,606},{495,495},{606,350},{676,181},{700,0}};
            p1 = new Polygon(0,0,island,24,this);
            p1->setColor(COLOR(0,128,0));
            p1->setFill();
            cout<<"Island Origin "<<p1->getX()<<","<<p1->getY();
            c1= new Circle(1455,600,50,this);
            c1->setColor(COLOR("red"));
            c1->setFill();

        }
        inline void decoyForward(double speed){
            decoy->forward(speed);
        }
        void createDecoy(int x,int y){
            x=x-2560;
            y=y-720;
            double bodyV[6][2]={{-56,0},{-50,-14.50},{30,-20},{75.0,0},{30,20},{-50,14.50}};
            decoy = new Polygon(x,y,bodyV,6,this);
            decoy->setColor(COLOR(34,139,34));
            decoy->setFill();
        }
        inline void moveDecoyright(double angle){
            decoy->right(angle);
        }
        inline void moveDecoyleft(double angle){
            decoy->left(angle);
        }
        inline bool boundary(void){
                if(decoy->getX()<-2520||decoy->getX()>2520||decoy->getY()<-1400||decoy->getY()>1400)
                        return 1;
                return 0;
        }
        inline bool proximity(void){
            int prox=720,distance=0;
            distance=sqrt((decoy->getX()-0)*(decoy->getX()-0)+(decoy->getY()-0)*(decoy->getY())-0);
            cout<<"distance = "<<distance<<endl;
            if(prox>=distance){
                 return 1;
            }
           else{
            return 0;
           }
        }
        inline int goalstate(void){
            int prox=10,distance=0;
            distance=sqrt((decoy->getX()-c1->getX())*(decoy->getX()-c1->getX())+(decoy->getY()-c1->getY())*(decoy->getY())-c1->getY());
            if(prox>=distance)
                    return 1;
            else
                    return 0;
        }
};

class Sail : public Composite{
	Line *mast;
	double a,b;
	public:	Sail(double x,double y,Composite* owner=NULL): Composite(x,y,owner){
	mast= new Line(0,0,-60,0,this);
	mast->setColor(COLOR(255,255,0));
	mast->setFill();
	}
};
class Rudder : public Composite {
        Line *flap;
        double max_left,max_right;
        bool brake=0;
 	public:
        Rudder(double x,double y,Composite* owner=NULL): Composite(x,y,owner){
        flap = new Line(0,0,-25,0,this);
        max_left=0;
        max_right=0;
	}
	void move_left(double angle){
		if(max_left<4){
		flap->left(angle);
		max_left++;
		max_right--;
		}
	}
	void move_right(double angle){
		if(max_right<4){
		flap->right(angle);
		max_right++;
		max_left--;
		}

	}
	inline int stabalizeRudder(double angle){
        if(max_right==max_left)
                return 0;
        if(max_right<max_left){
            int n=max_left;
            for(int i=0;i<n;i++){
                flap->right(angle);
                max_right++;
                max_left--;
                wait(0.1);
            }
        }
        if(max_right>max_left){
            int n=max_right;
            for(int i=0;i<n;i++){
                flap->left(angle);
                max_right--;
                max_left++;
                wait(0.1);
            }
        }
        return 0;
    }
	void halt(bool test){
        if(brake==0){
		flap->left(90);
		brake=test;
		}
	}
	void normalizeRudder(){
            if(brake==1){
            flap->right(90);
            brake=0;
            }

	}
};

class boat : public Composite {					// Class Boat
	Polygon *body;
	Rudder *flap;
	public:	Sail *mast;
		boat(double x, double y,Composite* owner=NULL):Composite(x,y,owner){
            double bodyV[6][2]={{-56,0},{-50,-14.50},{30,-20},{75.0,0},{30,20},{-50,14.50}};
            body = new Polygon(0,0,bodyV,6,this);
            body->setColor(COLOR(165,42,42));
            body->setFill();
            flap = new Rudder(-45,0,this);
            mast = new Sail(35,0,this);
        }
        void move_forward(double speed){
            Composite::forward(speed);
        }
        void move_left(double angle){
            Composite::left(angle);
            flap->move_right(angle*2);
        }
        void move_right(double angle){
            Composite::right(angle);
            flap->move_left(angle*2);
        }
        std::vector<double>sail;
        void halt(vector<double> &sail){
        if(sail[0]>0)
    		sail[0]=sail[0]-(.051*sail[0]*sail[0]);
        	flap->halt(1);
        }
        inline void stabalize(int a){
            flap->stabalizeRudder(a*2);
        }
        inline void normalizeRudder(){
            flap->normalizeRudder();
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
inline void calculate(vector<double> &sail,double &va,double omega,double T,double Cl,double Cd,double &wind){

	acc=0.003748*va*va*(Cl*sin(omega*0.0174533)-Cd*cos(omega*0.0174533));
	acc=acc-(1.8*sail[0]*pow(10,-5));
	acc=abs(acc);
	sail[0]+=acc*T;
	if(sail[0]>=wind+5)
	sail[0]=wind+5;
	cout<<"accelerating at "<<acc<<endl;
}
inline int pause_menu(void){

                        beginFrame();
                        Rectangle r1(640,360,400,500);
                        r1.setFill();
                        int x,y,pos;
                        Rectangle r4(640,195,300,150),r2(640,355,300,150),r3(640,515,300,150);
                        Text T1(640,195,"RESUME GAME"),T3(640,515,"QuiT GAME"),T2(640,355,"RESTART");
                        endFrame();
                        while(1){
                            pos=getClick();
                            x=pos/65536;
                            y=pos%65536;
                            if(x>=540&&x<=740&&y>=120&&y<=270)
                                return 0;
                            else if(x>=540&&x<=740&&y>=280&&y<=430)
                                return 4;
                            else if(x>=540&&x<=740&&y>=440&&y<=590)
                                    exit(0);
                        }

}
class arrow :public Composite{

    Line *l1,*l2,*l3;

    public : arrow(double x,double y,Composite* owner=NULL):Composite(x,y,owner){
                l1 = new Line(35,0,-35,0,this);
                l2 = new Line(35,0,0,-20,this);
                l3 = new Line(35,0,0,20,this);

            }
};
class miniMap : public Composite {
    Rectangle *R1;
    Polygon *decoy,*island;
    Circle *c1;
    public : miniMap(double x,double y,Composite* owner=NULL): Composite(x,y,owner){
                R1= new Rectangle(0,0,256,144,this);
                R1->setColor(COLOR(0,0,102));
                R1->setFill();
                double points[24][2]={{676/20,-181/20},{606/20,-350/20},{495/20,-495/20},{350/20,-606/20},{181/20,-676/20},{0,-700/20},{-181/20,-676/20},{-350/20,-606/20},{-495/20,-495/20},{-606/20,-350/20},{-676/20,-181/20},{-700/20,0},{-676/20,181/20},{-606/20,350/20},
{-495/20,495/20},{-350/20,606/20},{-181/20,676/20},{0,700/20},{181/20,676/20},{350/20,606/20},{495/20,495/20},{606/20,350/20},{676/20,181/20},{700/20,0}};
                island = new Polygon(0,0,points,24,this);
                island->setColor(COLOR(0,128,0));
                island->setFill();
                c1= new Circle(1455/20,600/20,50/20,this);
                c1->setColor(COLOR("black"));
                c1->setFill();


            }
            inline void decoyForward(double speed){
            decoy->forward(speed/20);
            }
            void createDecoy(int x,int y){
                x=x-2560;
                y=y-720;
                double bodyV[3][2]={{-1.44,-1.44},{1,0},{-1.44,1.44}};
                decoy = new Polygon(x/20,y/20,bodyV,3,this);
                decoy->setColor(COLOR(153,0,0));
                decoy->setFill();

            }
            inline void moveDecoyright(double angle){
                decoy->right(angle);
            }
            inline void moveDecoyleft(double angle){
                decoy->left(angle);
            }
};
inline int restart(void){
                            beginFrame();
                            Rectangle r1(450,50,400,50);
                            r1.setFill();
                            Text t1(450,50,"BOAT HAS COLLIDED , RESTARTING GAME IN 5 SECONDS");
                            endFrame();
                            cout<<"GAME RESTARTING"<<endl;
                            wait(5);
                            return 4;
}
int game_area(void){
	beginFrame();
	arena m(2560,720);
	scrollBar s(100,360);
	HUD h(1180,50);
	Text t1(60,185,"90 D"),t2(60,360,"45 D"),t3(60,535,"0 D");
	boat b(640,320);
    miniMap mi(128,648);
    mi.createDecoy(640,320);
    arrow a(200,100);
    vector<double>wind(2);
		wind[0]=20; // wind speed
		wind[1]=90; // wind angle

    h.display(wind[0],wind[1]);
	endFrame();

		b.sail.push_back(0);
	b.sail.push_back(57.2985*b.getOrientation());
	int sailAngle=0;
	a.right(wind[1]);
	int angleTomove=0;
	clock_t start,end;
	double x;
	double cpu_time_used;
    int theta=0,gamma=0,beta=0; //180-angle between boat and true wind ;
	int omega=0;//new
	int aot=0; //angle of attack ;
	double cl,cd,thetar;
    int posX,posY;
    posX=b.getX();
    posY=b.getY();
    m.createDecoy(posX,posY);
    bool toggle=0;
    double dx=0,dy=0;
    time_t now,later; //taking system time
    time(&now);
    while(1){           //main game loop

		start=clock();
		beginFrame();
		toggle=m.goalstate();
		if(toggle==1){
            beginFrame();
            Text t1(500,50,"YOU WON THE GAME in");
            time(&later);
            double seconds = difftime(later,now);
            Text t2(600,50,seconds);
            Text t3(650,50,"seconds");
            endFrame();
            wait(5);
            cout<<"game was played for "<<seconds<<"seconds"<<endl;
            exit(0);

		}
        toggle=m.proximity();
        cout<<"toggle "<<toggle<<endl;
        if(toggle==1){
                int level=restart();
                if(level==4){
                    time(&later);
                     double seconds = difftime(later,now);
                        cout<<"game was played for"<<seconds<<endl;
                    return level;
                }
        }
        toggle=m.boundary();
        if(toggle==1)
                exit(0);
        sailAngle=57.2985*b.mast->getOrientation();
        cout<<"sail angle"<<sailAngle<<endl;
		b.sail[1]=57.2958*b.getOrientation();//new
		if(b.sail[1]<0){gamma=b.sail[1]-(2*b.sail[1]);}//new
		gamma=b.sail[1];
		beta=b.sail[1];
		if(b.sail[1]<0){beta=361+b.sail[1];}
		cout<<beta<<"bsail "<<gamma;//new
        if((beta>wind[1])&&(beta<(180+wind[1])))
            {theta=(beta-wind[1]);}
        else
            {theta=wind[1]-gamma;
                theta=-1*theta;}
        int AngleBetweenBoat=theta;
        theta=abs(theta);//new
        theta=180-theta;//new
        cout<<AngleBetweenBoat<<"theta"<<theta;//new
        thetar=0.0174*theta;//new
        x=pow(b.sail[0],2)+pow(wind[0],2)+(2*b.sail[0]*wind[0]*cos(thetar));//new
        va=pow(x,0.5);//new
		omega=atan2((wind[0]*sin(thetar)),(b.sail[0]+wind[0]*cos(thetar)));//angle of apparent wind ;
		omega*=57.2985;
        alpha=theta-omega;//new
        cout<<"alpha"<<alpha;
        cout<<"omega"<<omega;
        if(sailAngle==0)
            {aot=0;}
        else
            {aot=alpha-sailAngle;}
        if(aot<0)
            aot=abs(aot);
		int rem=aot%5;
		if(rem<3)
			aot-=rem;
		else
			aot+=(5-rem);

        if(AngleBetweenBoat>150)
                {cl=0; cd=0;}
        else
                {cl=getCl(aot); cd=getCd(aot);}

		calculate(b.sail,va,omega,T,cl,cd,wind[0]);
        Text sp(1230,20,b.sail[0]);
/*		cout<<"boat speed :"<<b.sail[0]<<endl;
		cout<<"apparent wind speed "<<va<<endl;
		cout<<"angle of attack "<<aot<<endl;
		cout<<"Ttime "<<T<<endl;
		cout<<"cl "<<cl<<endl;
		cout<<"cd "<<cd<<endl;
		cout<<"angle of apparent wind "<<omega<<endl;
		cout<<"theta"<<theta<<endl;
*/

		XEvent event;
        if(checkEvent(event)){

					if(keyPressEvent(event)){
                				 char c = charFromEvent(event);

                            if(c=='a'){
								b.move_left(5);
								m.moveDecoyleft(5);
								mi.moveDecoyleft(5);
                            }
                			if(c=='d'){
								b.move_right(5);
								m.moveDecoyright(5);
								mi.moveDecoyright(5);
                            }
                			if(c==' '){
								b.halt(b.sail);
								m.move(0,0);
								mi.move(0,0);
                            }
                            if(c==27){
                                                int level;
                                                level=pause_menu();
                                                if(level==4)
                                                        return level;
                                                start=clock();
                            }
                            if(c=='w'){
                                if(s.slider->getY()>-180)
                                    s.slider->move(0,-20);
                                if(angleTomove<90){
                                    angleTomove+=5;
                                    if(AngleBetweenBoat>=0){
                                        b.mast->right(5);
                                    }
                                    if(AngleBetweenBoat<0)
                                    {
                                        b.mast->left(5);
                                    }
                                }
                            }
                            if(c=='s'){
                                if(s.slider->getY()<180)
                                    s.slider->move(0,20);
                                if(angleTomove>0){
                                    angleTomove-=5;
								if(AngleBetweenBoat>=0){
										b.mast->left(5);
								}
								if(AngleBetweenBoat<0){
										b.mast->right(5);
								}
                                }
                            }
       	        }
 		}
        if(!checkEvent(event)){
                b.stabalize(5);
                b.normalizeRudder();
        }
		if(AngleBetweenBoat<0){
			if(sailAngle>0){
                b.mast->left(sailAngle);
				b.mast->left(sailAngle);
			}

		}
		if(AngleBetweenBoat>=0){
			if(sailAngle<=0){

				b.mast->left(sailAngle);
				b.mast->left(sailAngle);
			}

		}


		b.sail[1]=57.2985*b.getOrientation();
        cout<<"boat angle"<<b.sail[1]<<endl;
		cout<<"--------------------------------------------------------\n";
		if((int)b.sail[1]>=0&&(int)b.sail[1]<=90){

			dx=b.sail[0]*cos(b.getOrientation());
			dy=b.sail[0]*sin(b.getOrientation());
			m.move(-dx,-dy);
			m.decoyForward(b.sail[0]);
			mi.decoyForward(b.sail[0]);
		}
		else if((int)b.sail[1]>90&&(int)b.sail[1]<=180){

			double newangle;
			newangle=180-b.sail[1];
			newangle*=0.0174533;
			dx=b.sail[0]*cos(newangle);
			dy=b.sail[0]*sin(newangle);
			m.move(dx,-dy);
			m.decoyForward(b.sail[0]);
			mi.decoyForward(b.sail[0]);
		}
		else if((int)b.sail[1]<=-90&&(int)b.sail[1]>-185){
			double newangle;
			newangle=180+b.sail[1];
			newangle*=0.0174533;
			dx=b.sail[0]*cos(newangle);
			dy=b.sail[0]*sin(newangle);
			m.move(dx,dy);
            m.decoyForward(b.sail[0]);
            mi.decoyForward(b.sail[0]);
		}
		else if((int)b.sail[1]<0&&(int)b.sail[1]>-90){

			dx=b.sail[0]*cos(-b.getOrientation());
			dy=b.sail[0]*sin(-b.getOrientation());
			m.move(-dx,dy);
			m.decoyForward(b.sail[0]);
			mi.decoyForward(b.sail[0]);
		}
		endFrame();
		end=clock();
		cpu_time_used=(end-start)/(double)CLOCKS_PER_SEC * 1000;
		T=cpu_time_used*0.001;
		cout<<"CPU TIME "<<T<<endl;
			wait(0.015897667);
	}
	cout<<"entering destroy fun"<<endl;
        b.destroy();
	return 0;
}
void main_menu(int level){
	int x,y,pos;
	while(1){
	if(level==0){
            beginFrame();
            Rectangle R2(640,360,400,500);
            Rectangle r1(640,250,200,100),r2(640,500,200,100);
	        Text T1(640,250,"ENTER THE GAME"),T2(640,500,"QUIT THE GAME");
	        endFrame();
	        cout<<level<<endl;
            pos=getClick();
            x=pos/65536;
            y=pos%65536;
            if(x>=540&&x<=740&&y>=200&&y<=300)
                level++;
            else if(x>=540&&x<=740&&y>=400&&y<=600)
                exit(0);
            }
    else if(level==1){
                beginFrame();
                Rectangle R2(640,360,400,500);
                Text T1(640,150,"BOAT MANUAL");
                boat b(540,320);
                b.left(90);
                b.mast->left(45);
                Line l1(600,320,650,320);
                Line l2(550,380,600,380);
                Text t1(720,320,"SAIL :- \"W\" & \"S\""),
                     t2(720,340,"To open/close the sail"),
                t3(720,380,"Rudder :- \"A\" &\"D\""),
                t4(720,400,"To navigate the boat right and left");
                Rectangle r1(550,500,100,40),r2(750,500,100,40);
                Text t5(550,500,"BACK"),t6(750,500,"NEXT");
                endFrame();
                cout<<level<<endl;
                pos=getClick();
                int x=pos/65536;
                int y=pos%65536;
                if(x>=500&&x<=600&&y>=480&&y<=520)
                    level--;
                else if(x>=700&&x<=800&&y>=480&&y<=520)
                    level++;
                else
                    level=level;
            }
    else if(level==2){
             beginFrame();
                Rectangle R2(640,360,400,500);
                Text T1(640,150,"WEATHER FORECAST");
                Text T2(550,220,"WIND SPEED :- 20-60 KMPH");
                Text T3(580,250,"WIND Direction :- 40degree-80degree");
                Text T4(550,280,"South-east to South west");
                Text T5(610,310,"occosionally retreat wind towards North west");
                Rectangle r1(550,500,100,40),r2(750,500,100,40);
                Text t2(550,500,"BACK"),t3(750,500,"NEXT");
                endFrame();
                cout<<level<<endl;
                pos=getClick();
                int x=pos/65536;
                int y=pos%65536;
                if(x>=500&&x<=600&&y>=480&&y<=520)
                    level--;
                else if(x>=700&&x<=800&&y>=480&&y<=520)
                    level++;
            }
        else if(level==3){
                  Rectangle R2(640,360,400,500);
                Text T1(640,150,"HOW TO PLAY ?");
                Text T2(600,220,"Use The Controls to Navigate The sail boat");
                Text T3(600,250,"Use the HUD to see the Boat speed ");
                Text T7(610,280,"wind speed and wind angle");
                Text T4(610,310,"Check with the arrow showing the direction of wind ");
                Text T5(610,340,"Use the mini-map to find your destination and");
                Text T6(620,370,"by using your skills sail to the destination");
                Rectangle r1(550,500,100,40),r2(750,500,100,40);
                Text t2(550,500,"BACK"),t3(750,500,"PLAY GAME");
                endFrame();
                cout<<level<<endl;
                pos=getClick();
                int x=pos/65536;
                int y=pos%65536;
                if(x>=500&&x<=600&&y>=480&&y<=520)
                    level--;
                else if(x>=700&&x<=800&&y>=480&&y<=520)
                    level++;
            }

        else if(level==4){
            cout<<"GAME STARTS"<<endl;
                level=game_area();
            }
    }//end while

}
int main(){
	initCanvas("Menu_Screen",1280,720);
	main_menu(0);
	return 0;
}

