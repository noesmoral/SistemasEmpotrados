#include <public/vehicle_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

Vehicle::EDROOMTopContext::EDROOMTopContext (Vehicle &act
	, CDLocation & EDROOMpVarVTargetLocation
	, CEDROOMPOOLCDLocation & EDROOMpPoolCDLocation ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,PathPlannerCtrl(EDROOMcomponent.PathPlannerCtrl)
	,PathTrackerCtrl(EDROOMcomponent.PathTrackerCtrl)
	,AvoidObstaclesSysCtrl(EDROOMcomponent.AvoidObstaclesSysCtrl)
	,Timer(EDROOMcomponent.Timer)
	, VTargetLocation ( EDROOMpVarVTargetLocation )
	, EDROOMPoolCDLocation ( EDROOMpPoolCDLocation )
 {

}

Vehicle::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,PathPlannerCtrl(contex.PathPlannerCtrl)
	,PathTrackerCtrl(contex.PathTrackerCtrl)
	,AvoidObstaclesSysCtrl(contex.AvoidObstaclesSysCtrl)
	,Timer(contex.Timer)
	, VTargetLocation ( contex.VTargetLocation )
	, EDROOMPoolCDLocation ( contex.EDROOMPoolCDLocation )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool Vehicle::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

	TEDROOMBool edroomValidMsg=false; 

	 switch(Msg->signal){

		// Check trigger for signal EDROOMSignalTimeout

		 case (EDROOMSignalTimeout): 

				if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId= ReStart;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

			 break;

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User Defined Functions   ****************************

void	Vehicle::EDROOMTopContext::FAvObstaclesError()

{

{
 
 	print_string("error in Avoid Obstacles System");
	print_char('\n');
	print_char('\r');
  
 
}

}



void	Vehicle::EDROOMTopContext::FInvokeConfigAvObstacles()

{

   //Invoke synchronous communication 
   MsgBack=AvoidObstaclesSysCtrl.invoke(SConfigAO); 
}



void	Vehicle::EDROOMTopContext::FInvokeConfigPathPlanner()

{
   //Allocate data from pool
  CDLocation * pSConfigPathPlanner_Data = 
                                               EDROOMPoolCDLocation.AllocData();
	
		// Complete Data 
	
	*pSConfigPathPlanner_Data=VTargetLocation;
   //Invoke synchronous communication 
   MsgBack=PathPlannerCtrl.invoke(SConfigPathPlanner
                                                      , pSConfigPathPlanner_Data
                                                      , &EDROOMPoolCDLocation); 
}



void	Vehicle::EDROOMTopContext::FInvokeConfigPathTracker()

{

   //Invoke synchronous communication 
   MsgBack=PathTrackerCtrl.invoke(SConfigPathTracker); 
}



void	Vehicle::EDROOMTopContext::FMarkObstacle()

{
   //Allocate data from pool
  CDLocation * pSMarkObstacle_Data = 
                                               EDROOMPoolCDLocation.AllocData();
	
		// Complete Data 
	
	*pSMarkObstacle_Data=sensors_get_current_location();
   //Send message 
   PathPlannerCtrl.send(SMarkObstacle, pSMarkObstacle_Data
                                                      , &EDROOMPoolCDLocation); 
}



void	Vehicle::EDROOMTopContext::FPathPlannerError()

{

{
 
 print_string("Error in Planner Config");
 print_char('\n');
 print_char('\r');
 
 
}

}



void	Vehicle::EDROOMTopContext::FPathTrackerError()

{

{
 
 printf("Error in Path Tracker Config");
 print_char('\n');
 print_char('\r');
 
 
 
}

}



void	Vehicle::EDROOMTopContext::FProgRecovery()

{
   //Define absolute time
  Pr_Time time;
	
	time.GetTime();
 
	print_string("Power off all subsystems");
	print_char('\n');
	print_char('\r');
 
	print_string("Restart in 10 seconds");
	print_string("----------------------------------"); 
	print_char('\n');
	print_char('\r');
	// Timing Service 
	 
	time+=Pr_Time(10,0);  // seconds
	 
	
   //Program absolute timer 
   Timer.InformAt( time ); 
}



void	Vehicle::EDROOMTopContext::FProgTimerConfig()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
   interval = Pr_Time(1,0); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	Vehicle::EDROOMTopContext::FStartAvoidObs()

{

   //Send message 
   AvoidObstaclesSysCtrl.send(SStart); 
}



void	Vehicle::EDROOMTopContext::FStartPlanning()

{

   //Send message 
   PathPlannerCtrl.send(SStartPlanning); 
}



void	Vehicle::EDROOMTopContext::FStartTracking()

{

   //Send message 
   PathTrackerCtrl.send(SStartTracking); 
}



void	Vehicle::EDROOMTopContext::FStartUp()

{

{
 
	VTargetLocation=sensors_get_current_location();
 
	if(VTargetLocation.latitude>0) 
		VTargetLocation.latitude-=0.1;
	else
		VTargetLocation.latitude+=0.1;
 
	if(VTargetLocation.longitude>0) 
		VTargetLocation.longitude-=0.1;
	else
		VTargetLocation.longitude+=0.1;	
 
 	print_string("basic hw checking\n");
 
	print_string("power on sensors\n");
 
	print_string("power on actuators\n");
 
 	  
}

}



void	Vehicle::EDROOMTopContext::FStopTracking()

{

   //Send message 
   PathTrackerCtrl.send(SStopTracking); 
}



TEDROOMBool	Vehicle::EDROOMTopContext::GConfigError()

{

return(MsgBack->signal==SConfigError);

}



	//********************************** Pools *************************************

	//CEDROOMPOOLCDLocation

Vehicle::EDROOMTopContext::CEDROOMPOOLCDLocation::CEDROOMPOOLCDLocation(TEDROOMUInt32 elemCount, CDLocation* pMem, TEDROOMBool * pMemMarks):CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks, sizeof (CDLocation)){;}

CDLocation *	Vehicle::EDROOMTopContext::CEDROOMPOOLCDLocation::AllocData(){
	return(CDLocation*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

Vehicle::EDROOMTopState::EDROOMTopState (Vehicle &act, CEDROOMMemory *pEDROOMMemory  ):
	  EDROOMTopContext( act 
		, VTargetLocation
		, EDROOMPoolCDLocation )
	, EDROOMPoolCDLocation ( 10, pEDROOMMemory->poolCDLocation, pEDROOMMemory->poolMarkCDLocation)
{

}

	//***************************** EDROOMBehaviour ********************************

void Vehicle::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIllegada();

	do{

		//Take next transition

		switch(edroomCurrentTrans.localId){

			//Next Transition is Init
			case(Init):
				//Next State is StartUp
				edroomNextState = StartUp;
				break;
			//To Choice Point BranchConfigAvObstacles
			case(ConfigAvObstacles):
				//Invoke Synchronous Message 
				FInvokeConfigAvObstacles();
				//Evaluate Branch Error
				if( GConfigError() ){
					//Execute Action 
					FAvObstaclesError();

				//Next Transition is ConfigAvObstacles
					edroomCurrentTrans.localId = ConfigAvObstacles_Error;

				//Next State is SysRecovery
					edroomNextState = SysRecovery;
				 } 
				//Evaluate Branch OK
				else{

				//Next Transition is ConfigAvObstacles
					edroomCurrentTrans.localId = ConfigAvObstacles_OK;

				//Next State is AvObstaclesConfigured
					edroomNextState = AvObstaclesConfigured;
				 } 
				break;
			//Next Transition is ReStart
			case(ReStart):
				//Next State is StartUp
				edroomNextState = StartUp;
				break;
			//To Choice Point BranchConfigPathTracker
			case(ConfigPathTracker):
				//Invoke Synchronous Message 
				FInvokeConfigPathTracker();
				//Evaluate Branch Error
				if( GConfigError() ){
					//Execute Action 
					FPathTrackerError();

				//Next Transition is ConfigPathTracker
					edroomCurrentTrans.localId = ConfigPathTracker_Error;

				//Next State is SysRecovery
					edroomNextState = SysRecovery;
				 } 
				//Evaluate Branch OK
				else{

				//Next Transition is ConfigPathTracker
					edroomCurrentTrans.localId = ConfigPathTracker_OK;

				//Next State is PathTrackerConfigured
					edroomNextState = PathTrackerConfigured;
				 } 
				break;
			//To Choice Point BranchConfigPathPlanner
			case(ConfigPathPlanner):
				//Invoke Synchronous Message 
				FInvokeConfigPathPlanner();
				//Evaluate Branch Error
				if( GConfigError() ){
					//Execute Action 
					FPathPlannerError();

				//Next Transition is ConfigPathPlanner
					edroomCurrentTrans.localId = ConfigPathPlanner_Error;

				//Next State is SysRecovery
					edroomNextState = SysRecovery;
				 } 
				//Evaluate Branch OK
				else{
					//Send Asynchronous Messages 
					FStartPlanning();
					FStartTracking();
					FStartAvoidObs();

				//Next Transition is ConfigPathPlanner
					edroomCurrentTrans.localId = ConfigPathPlanner_OK;

				//Next State is VehicleReady
					edroomNextState = VehicleReady;
				 } 
				break;
			//Next Transition is ObstacleDetected
			case(ObstacleDetected):
				//Send Asynchronous Messages 
				FStopTracking();
				FMarkObstacle();
				//Next State is VehicleReady
				edroomNextState = VehicleReady;
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState){

				//Go to the state I
			case(I):
				//Entry into the State I
				edroomCurrentTrans=EDROOMIllegada();
				break;

				//Go to the state StartUp
			case(StartUp):
				//Execute Entry Actions 
				FStartUp();
				FProgTimerConfig();
				//Entry into the State StartUp
				edroomCurrentTrans=EDROOMStartUpllegada();
				break;

				//Go to the state VehicleReady
			case(VehicleReady):
				//Entry into the State VehicleReady
				edroomCurrentTrans=EDROOMVehicleReadyllegada();
				break;

				//Go to the state SysRecovery
			case(SysRecovery):
				//Execute Entry Action 
				FProgRecovery();
				//Entry into the State SysRecovery
				edroomCurrentTrans=EDROOMSysRecoveryllegada();
				break;

				//Go to the state AvObstaclesConfigured
			case(AvObstaclesConfigured):
				//Execute Entry Action 
				FProgTimerConfig();
				//Entry into the State AvObstaclesConfigured
				edroomCurrentTrans=EDROOMAvObstaclesConfiguredllegada();
				break;

				//Go to the state PathTrackerConfigured
			case(PathTrackerConfigured):
				//Execute Entry Action 
				FProgTimerConfig();
				//Entry into the State PathTrackerConfigured
				edroomCurrentTrans=EDROOMPathTrackerConfiguredllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void Vehicle::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId Vehicle::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  StartUp

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOMTopState::EDROOMStartUpllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  ConfigAvObstacles
					edroomCurrentTrans.localId = ConfigAvObstacles;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  VehicleReady

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOMTopState::EDROOMVehicleReadyllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (SObstacleDetected): 

				 if ( *Msg->GetPInterface() == AvoidObstaclesSysCtrl) {

					edroomCurrentTrans.localId= ObstacleDetected;
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

	// Leaf SubState  SysRecovery

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOMTopState::EDROOMSysRecoveryllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  AvObstaclesConfigured

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOMTopState::EDROOMAvObstaclesConfiguredllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  ConfigPathTracker
					edroomCurrentTrans.localId = ConfigPathTracker;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  PathTrackerConfigured

	// ***********************************************************************



TEDROOMTransId Vehicle::EDROOMTopState::EDROOMPathTrackerConfiguredllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  ConfigPathPlanner
					edroomCurrentTrans.localId = ConfigPathPlanner;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



