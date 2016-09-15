#include <public/capathtracker_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAPathTracker::EDROOMTopContext::EDROOMTopContext (CAPathTracker &act
	, CDPath & EDROOMpVarVCurrentPath
	, TEDROOMUInt8 & EDROOMpVarVCurrentPathStep
	, TEDROOMUInt8 & EDROOMpVarVSimError ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,TrackPath(EDROOMcomponent.TrackPath)
	,PathTrackerCtrl(EDROOMcomponent.PathTrackerCtrl)
	,Timer(EDROOMcomponent.Timer)
	, VCurrentPath ( EDROOMpVarVCurrentPath )
	, VCurrentPathStep ( EDROOMpVarVCurrentPathStep )
	, VSimError ( EDROOMpVarVSimError )
 {

}

CAPathTracker::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,TrackPath(contex.TrackPath)
	,PathTrackerCtrl(contex.PathTrackerCtrl)
	,Timer(contex.Timer)
	, VCurrentPath ( contex.VCurrentPath )
	, VCurrentPathStep ( contex.VCurrentPathStep )
	, VSimError ( contex.VSimError )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CAPathTracker::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

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

void	CAPathTracker::EDROOMTopContext::FGetNewPatch()

{
   //Handle Msg->data
  CDPath & varSTrackPath = *(CDPath *)Msg->data;
	
		// Data access
 
	VCurrentPath = varSTrackPath;
 
 	VCurrentPathStep=0;

}



void	CAPathTracker::EDROOMTopContext::FGoToPathStep()

{

{
 print_char('\n');
 print_char('\r');
 print_char('+');
 print_uint8(VCurrentPathStep);
 
 actuators_go_to_location(VCurrentPath.pathLocations[VCurrentPathStep]);
 
 VCurrentPathStep++;
 
}

}



void	CAPathTracker::EDROOMTopContext::FProgFirstTrackStep()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
 interval = Pr_Time(0,10000); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAPathTracker::EDROOMTopContext::FProgNextTrackStep()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
  interval = Pr_Time(0,400000); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAPathTracker::EDROOMTopContext::FReplyOK()

{

   //Reply synchronous communication
   Msg->reply(SConfigOK); 
}



void	CAPathTracker::EDROOMTopContext::FReplySimError()

{

 
 
  VSimError--;
   //Reply synchronous communication
   Msg->reply(SConfigError); 
}



void	CAPathTracker::EDROOMTopContext::FSendPathRequest()

{

   //Send message 
   TrackPath.send(SPathRequest); 
}



TEDROOMBool	CAPathTracker::EDROOMTopContext::GLastStep()

{

{
 
	return (VCurrentPathStep>=VCurrentPath.pathSteps);
 
 
 
 
}

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAPathTracker::EDROOMTopState::EDROOMTopState (CAPathTracker &act ):
	  EDROOMTopContext( act 
		, VCurrentPath
		, VCurrentPathStep
		, VSimError )
	, VCurrentPathStep ( 0 )
	, VSimError ( 2 )
{

}

	//***************************** EDROOMBehaviour ********************************

void CAPathTracker::EDROOMTopState::EDROOMBehaviour(){

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
			//Next Transition is NewPath
			case(NewPath):
				//Msg->Data Handling 
				FGetNewPatch();
				//Execute Action 
				FProgFirstTrackStep();
				//Next State is TrackingPath
				edroomNextState = TrackingPath;
				break;
			//To Choice Point BranchPathStep
			case(PathStep):
				//Execute Action 
				FGoToPathStep();
				//Evaluate Branch LastStep
				if( GLastStep() ){
					//Send Asynchronous Message 
					FSendPathRequest();

				//Next Transition is PathStep
					edroomCurrentTrans.localId = PathStep_LastStep;

				//Next State is StandBy
					edroomNextState = StandBy;
				 } 
				//Evaluate Branch toNextStep
				else{
					//Execute Action 
					FProgNextTrackStep();

				//Next Transition is PathStep
					edroomCurrentTrans.localId = PathStep_toNextStep;

				//Next State is TrackingPath
					edroomNextState = TrackingPath;
				 } 
				break;
			//To Choice Point BranchConfig
			case(Config):
				//Evaluate Branch Error
				if( VSimError ){
					//Invoke Synchronous Message 
					FReplySimError();

				//Next Transition is Config
					edroomCurrentTrans.localId = Config_Error;

				//Next State is Idle
					edroomNextState = Idle;
				 } 
				//Evaluate Branch OK
				else{
					//Invoke Synchronous Message 
					FReplyOK();

				//Next Transition is Config
					edroomCurrentTrans.localId = Config_OK;

				//Next State is Idle
					edroomNextState = Idle;
				 } 
				break;
			//Next Transition is Start
			case(Start):
				//Next State is StandBy
				edroomNextState = StandBy;
				break;
			//Next Transition is StopTrack
			case(StopTrack):
				//Next State is Pause
				edroomNextState = Pause;
				break;
			//Next Transition is ResumePath
			case(ResumePath):
				//Msg->Data Handling 
				FGetNewPatch();
				//Next State is TrackingPath
				edroomNextState = TrackingPath;
				break;
			//Next Transition is ToStandBy
			case(ToStandBy):
				//Next State is StandBy
				edroomNextState = StandBy;
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

				//Go to the state StandBy
			case(StandBy):
				//Entry into the State StandBy
				edroomCurrentTrans=EDROOMStandByllegada();
				break;

				//Go to the state TrackingPath
			case(TrackingPath):
				//Entry into the State TrackingPath
				edroomCurrentTrans=EDROOMTrackingPathllegada();
				break;

				//Go to the state Pause
			case(Pause):
				//Entry into the State Pause
				edroomCurrentTrans=EDROOMPausellegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CAPathTracker::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CAPathTracker::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CAPathTracker::EDROOMTopState::EDROOMIdlellegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (SConfigPathTracker): 

				 if ( *Msg->GetPInterface() == PathTrackerCtrl) {

					//Next transition is  Config
					edroomCurrentTrans.localId = Config;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

			case (SStartTracking): 

				 if ( *Msg->GetPInterface() == PathTrackerCtrl) {

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

	// Leaf SubState  StandBy

	// ***********************************************************************



TEDROOMTransId CAPathTracker::EDROOMTopState::EDROOMStandByllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (STrackPath): 

				 if ( *Msg->GetPInterface() == TrackPath) {

					edroomCurrentTrans.localId= NewPath;
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

	// Leaf SubState  TrackingPath

	// ***********************************************************************



TEDROOMTransId CAPathTracker::EDROOMTopState::EDROOMTrackingPathllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  PathStep
					edroomCurrentTrans.localId = PathStep;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

			case (SStopTracking): 

				 if ( *Msg->GetPInterface() == PathTrackerCtrl) {

					edroomCurrentTrans.localId= StopTrack;
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

	// Leaf SubState  Pause

	// ***********************************************************************



TEDROOMTransId CAPathTracker::EDROOMTopState::EDROOMPausellegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (STrackPath): 

				 if ( *Msg->GetPInterface() == TrackPath) {

					edroomCurrentTrans.localId= ResumePath;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId= ToStandBy;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



