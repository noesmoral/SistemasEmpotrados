#include <public/caavoidobstacles_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAAvoidObstacles::EDROOMTopContext::EDROOMTopContext (CAAvoidObstacles &act
	, TEDROOMBool & EDROOMpVarVObsDetected ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,AvoidObstaclesSysCtrl(EDROOMcomponent.AvoidObstaclesSysCtrl)
	,Timer(EDROOMcomponent.Timer)
	, VObsDetected ( EDROOMpVarVObsDetected )
 {

}

CAAvoidObstacles::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,AvoidObstaclesSysCtrl(contex.AvoidObstaclesSysCtrl)
	,Timer(contex.Timer)
	, VObsDetected ( contex.VObsDetected )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CAAvoidObstacles::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

	TEDROOMBool edroomValidMsg=false; 

	 switch(Msg->signal){

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User Defined Functions   ****************************

void	CAAvoidObstacles::EDROOMTopContext::FCheckObstacles()

{

print_char('.');
VObsDetected=sensors_check_obstacles();

}



void	CAAvoidObstacles::EDROOMTopContext::FConfigOK()

{

   //Reply synchronous communication
   Msg->reply(SConfigOK); 
}



void	CAAvoidObstacles::EDROOMTopContext::FHandleObstacle()

{

print_char('\n');
print_char('\r');
print_string("\tOBST");
actuators_halt();
   //Send message 
   AvoidObstaclesSysCtrl.send(SObstacleDetected); 
}



void	CAAvoidObstacles::EDROOMTopContext::FProgNextDetection()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	interval=Pr_Time(0,50000); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



TEDROOMBool	CAAvoidObstacles::EDROOMTopContext::GObstacleDetected()

{

return(VObsDetected);

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAAvoidObstacles::EDROOMTopState::EDROOMTopState (CAAvoidObstacles &act ):
	  EDROOMTopContext( act 
		, VObsDetected )
{

}

	//***************************** EDROOMBehaviour ********************************

void CAAvoidObstacles::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIllegada();

	do{

		//Take next transition

		switch(edroomCurrentTrans.localId){

			//Next Transition is Init
			case(Init):
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//Next Transition is Config
			case(Config):
				//Invoke Synchronous Message 
				FConfigOK();
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//Next Transition is Start
			case(Start):
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//To Choice Point BranchCheackObstacles
			case(CheackObstacles):
				//Execute Action 
				FCheckObstacles();
				//Evaluate Branch ObsDetected
				if( GObstacleDetected() ){
					//Send Asynchronous Message 
					FHandleObstacle();

				//Next Transition is CheackObstacles
					edroomCurrentTrans.localId = CheackObstacles_ObsDetected;

				//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Evaluate Branch NoObstacle
				else{

				//Next Transition is CheackObstacles
					edroomCurrentTrans.localId = CheackObstacles_NoObstacle;

				//Next State is Ready
					edroomNextState = Ready;
				 } 
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState){

				//Go to the state I
			case(I):
				//Entry into the State I
				edroomCurrentTrans=EDROOMIllegada();
				break;

				//Go to the state Idle
			case(Idle):
				//Entry into the State Idle
				edroomCurrentTrans=EDROOMIdlellegada();
				break;

				//Go to the state Ready
			case(Ready):
				//Execute Entry Action 
				FProgNextDetection();
				//Entry into the State Ready
				edroomCurrentTrans=EDROOMReadyllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CAAvoidObstacles::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CAAvoidObstacles::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CAAvoidObstacles::EDROOMTopState::EDROOMIdlellegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (SConfigAO): 

				 if ( *Msg->GetPInterface() == AvoidObstaclesSysCtrl) {

					edroomCurrentTrans.localId= Config;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (SStart): 

				 if ( *Msg->GetPInterface() == AvoidObstaclesSysCtrl) {

					edroomCurrentTrans.localId= Start;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CAAvoidObstacles::EDROOMTopState::EDROOMReadyllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  CheackObstacles
					edroomCurrentTrans.localId = CheackObstacles;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



