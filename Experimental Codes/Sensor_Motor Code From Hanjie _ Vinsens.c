#pragma config(Sensor, in2,    B,              sensorAnalog)
#pragma config(Sensor, in3,    C,              sensorAnalog)
#pragma config(Sensor, in4,    A,              sensorAnalog)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int ball_close=0;
int object_detection=0;
int robot_detection=0;
int test=0;
int batLevel;
float distance;
float a;

task rotate()
{
	while(true)
	{
		test=1;
		if(object_detection == 0)
		{
			test=2;
			int rotateStatus = 0;
			motor[port1] = 50;
			motor[port10] = 50;
			clearTimer(T1);
			while(object_detection == 0)
			{
				if(time1[T1] > 2500) break;
				if(object_detection == 1) break;
				if(time1[T1] > 800 && rotateStatus == 0)
				{
					motor[port1] = 0;
					motor[port10]=0;
					wait1Msec(500);
					motor[port1] = -30;
					motor[port10] = -30;
					rotateStatus = 1;
				}
			}
		}
	}
}
/*
task moveToBall()
{
while(true)
{
if(object_detection == 1)
{
if(distance < 14)
{
motor[port1] = 0;
motor[port10] = 0;
}
else if(distance < 20)
{
motor[port1] = 25;
motor[port10] = -30;
}
else
{
motor[port1] = 0;
motor[port10] = 0;
}
}
}
}
*/
task main()
{
	//wait1Msec(5000);
	startTask(rotate);
	//startTask(moveToBall);
	while(true){
		batLevel = nImmediateBatteryLevel;
		if(300<SensorValue[B]&& SensorValue[B]< 3000) //detect an object ball,small value means long distance
		{
			object_detection =1;

			if (SensorValue[C] >600) // if detect other robot
			{
				robot_detection = 1; //that is robot
			}
			else{
				robot_detection = 0;

				//Detect the ball if it is close to the grabber
				if(robot_detection ==0&&object_detection==1){
					a = SensorValue[B];
					distance = (1/a*10000+0.6763)/0.5554;
					if(SensorValue[A] > SensorValue[B]-230 && SensorValue[A] <SensorValue[B]+230) //robot is closed to the object
					{
						ball_close =1;	//close then rotate the body
					}
					else{
						ball_close = 0; //not close enough
					}
				}
			}
		}

		else{
			object_detection=0;
			robot_detection =0;
			ball_close=0;
		}
	}
}
