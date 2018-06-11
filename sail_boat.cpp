// let's build a sail boat //
// using use inputs to control the boat 
// only one affecting factor added - the wind
#include<simplecpp>
#include<iostream>
#include<vector>



class boat : public Composite {					// Class Boat
	
	Polygon *body;
	double a,b;

	public:	boat(double x, double y,Color c,Composite* owner=NULL):Composite(x,y,owner){
		double bodyV[5][2]{{a-25,b-6.250},{a+25,b-6.25},{a+37.5,b},{a+25,b+6.25},{a-25,b+6.25}
		};

		body = new Polygon(a,b,bodyV,5,this);
		body->setColor(c);
		body->setFill();
	}
	void move_forward(int speed){
		Composite::forward(speed);
	}
	
	std::vector<double>sail;

	void destroy(){
		cout<<"boat is succesfully destroyed"<<endl;
		delete body;
	}
};


void calculate(vector<double> &wind,vector<double> &sail){
	sail[0]=sqrt(pow(wind[0],2)+pow(sail[0],2)+(2*wind[0]*sail[0]));
	sail[1]=tan(sail[0]/wind[0]);	
}

/*class rudder : public Composite {
	Line *flap;

	public: 
	rudder(
*/



int main(){
	vector<double>wind(2);

	initCanvas("sail_boat",1280,720);

	const double bWidth=150,bHeight=50,bRRx=900,bRRy=100;
	Rectangle screen(640,360,1280,720),buttonResult(bRRx,bRRy,bWidth,bHeight);
	screen.setColor(COLOR("black"));
	screen.setFill(true);
  	buttonResult.setColor(COLOR("yellow"));
	buttonResult.setFill(true);	

	boat b(200,250,COLOR("green"));

 	Text t1(280,500,"Distance="),t2(100,10,"start"),t3(900,400,"Stop");

	b.sail.push_back(0);
	b.sail.push_back(57.2985*b.getOrientation());
	
        double x=b.getX(),y=b.getY(),distance=0;
        while(1){
		beginFrame();
                if(x<5 || y< 5 || x>1260 || y>650){			//Checking for Collision At edges of screen
                        cout<<"collision detected"<<endl<<"entering destroy fun"<<endl;
                        b.destroy();
                        exit(1);
                }
		wind[0]=rand()%2;
		calculate(wind,b.sail);
		b.move_forward((b.sail[0])/500);

				
                distance=sqrt(pow(827-x,2)-pow(400-y,2));
                Text t5(340,500,distance);

                XEvent event;
                if(checkEvent(event) && keyPressEvent(event)){
                 char c = charFromEvent(event);
                 if(c=='a') b.left(1);
                 if(c=='d') b.right(1);
                }

                x=b.getX();
                y=b.getY();

  		 if(x<920&&x>820&&y>350&&y<450){
                        wait(2);
			int cm=0;
			Text r(bRRx,bRRy,"YOU WON");
			while(cm<5){
				r.hide();
				wait(2);
				r.show();
				wait(2);
				cm++;
			}
                        wait(2);
			cout<<"entering destroy fun"<<endl;
			b.destroy();
                        exit(1);
		 }
		 endFrame();
		 
	}
	cout<<"entering destroy fun"<<endl;
        b.destroy();
	return 0;
}
