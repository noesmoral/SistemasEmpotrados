#include <public/capathplanner_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAPathPlanner::EDROOMTopContext::EDROOMTopContext (CAPathPlanner &act
	, CDPath & EDROOMpVarVNextPath
	, CDLocation & EDROOMpVarVNextStepStartPoing
	, TEDROOMUInt8 & EDROOMpVarVSimError
	, CDLocation & EDROOMpVarVTargetLocation
	, TEDROOMBool & EDROOMpVarVVehicleHalted
	, CEDROOMPOOLCDPath & EDROOMpPoolCDPath ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,TrackPath(EDROOMcomponent.TrackPath)
	,PathPlannerCtrl(EDROOMcomponent.PathPlannerCtrl)
	,Timer(EDROOMcomponent.Timer)
	, VMaxPathSteps ( 8 )
	, VMinPathSteps ( 3 )
	, VNextPath ( EDROOMpVarVNextPath )
	, VNextStepStartPoing ( EDROOMpVarVNextStepStartPoing )
	, VSimError ( EDROOMpVarVSimError )
	, VTargetLocation ( EDROOMpVarVTargetLocation )
	, VVehicleHalted ( EDROOMpVarVVehicleHalted )
	, EDROOMPoolCDPath ( EDROOMpPoolCDPath )
 {

}

CAPathPlanner::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,TrackPath(contex.TrackPath)
	,PathPlannerCtrl(contex.PathPlannerCtrl)
	,Timer(contex.Timer)
	, VMaxPathSteps ( 8 )
	, VMinPathSteps ( 3 )
	, VNextPath ( contex.VNextPath )
	, VNextStepStartPoing ( contex.VNextStepStartPoing )
	, VSimError ( contex.VSimError )
	, VTargetLocation ( contex.VTargetLocation )
	, VVehicleHalted ( contex.VVehicleHalted )
	, EDROOMPoolCDPath ( contex.EDROOMPoolCDPath )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CAPathPlanner::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

	TEDROOMBool edroomValidMsg=false; 

	 switch(Msg->signal){

		// Check trigger for signal SNewTargetLocation

		 case (SNewTargetLocation): 

				if ( *Msg->GetPInterface() == PathPlannerCtrl) {

					edroomCurrentTrans.localId= NewTar;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

			 break;

		// Check trigger for signal SPathRequest

		 case (SPathRequest): 

				if ( *Msg->GetPInterface() == TrackPath) {

					edroomCurrentTrans.localId= PatRequest;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

			 break;

		// Check trigger for signal SMarkObstacle

		 case (SMarkObstacle): 

				if ( *Msg->GetPInterface() == PathPlannerCtrl) {

					edroomCurrentTrans.localId= ObsTDetected;
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

void	CAPathPlanner::EDROOMTopContext::FCalPathStep()

{

{
		print_char('s');
 
 		VNextPath.pathLocations[VNextPath.pathSteps]
					=calNextPathStep(VNextStepStartPoing, VTargetLocation);
 
		VNextPath.pathSteps++;
 
}

}



void	CAPathPlanner::EDROOMTopContext::FConfigPlanner()

{

{
 
	VTargetLocation = *(CDLocation *)Msg->data;
 
	
 
}

}



void	CAPathPlanner::EDROOMTopContext::FMarkObstacle()

{
   //Handle Msg->data
  CDLocation & varSMarkObstacle = 
                                                       *(CDLocation *)Msg->data;
	
		// Data access
 
  markObstacle(varSMarkObstacle);

}



void	CAPathPlanner::EDROOMTopContext::FMaxSteps()

{

{
 
 print_char('\n');
 print_char('\r');
 print_string("\tMAX");
 
 
}

}



void	CAPathPlanner::EDROOMTopContext::FNewTarget()

{
   //Handle Msg->data
  CDLocation & varSNewTargetLocation = 
                                                       *(CDLocation *)Msg->data;
	
		// Data acces
 
	VTargetLocation = varSNewTargetLocation;
 
	VVehicleHalted=true;	
	actuators_halt();
 
	VNextStepStartPoing=sensors_get_current_location();
 
	VNextPath.pathSteps=0;

}



void	CAPathPlanner::EDROOMTopContext::FProgNextStep()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
   interval = Pr_Time(0,100000); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAPathPlanner::EDROOMTopContext::FReplanning()

{

{
 
   VVehicleHalted=true;
 
   VNextStepStartPoing=sensors_get_current_location();
   VNextPath.pathSteps=0;
 
}

}



void	CAPathPlanner::EDROOMTopContext::FReplyConfigOK()

{

  VNextStepStartPoing=sensors_get_current_location();
 
  VVehicleHalted=true;	
		
  VNextPath.pathSteps=0;
   //Reply synchronous communication
   Msg->reply(SConfigOK); 
}



void	CAPathPlanner::EDROOMTopContext::FReplySimError()

{

 
 
 VSimError--;
   //Reply synchronous communication
   Msg->reply(SConfigError); 
}



void	CAPathPlanner::EDROOMTopContext::FSendNextPath()

{
   //Allocate data from pool
  CDPath * pSTrackPath_Data = 
                                                   EDROOMPoolCDPath.AllocData();
	
		// Complete Data 
	
	*pSTrackPath_Data=VNextPath;
 
	VVehicleHalted=false;	
 
	VNextPath.pathSteps=0;
 
 	printf("\n\rx");
 
   //Send message 
   TrackPath.send(STrackPath, pSTrackPath_Data, &EDROOMPoolCDPath); 
}



TEDROOMBool	CAPathPlanner::EDROOMTopContext::GMaxSteps()

{

{
 
 
 return (VNextPath.pathSteps==VMaxPathSteps);
 
 
}

}



TEDROOMBool	CAPathPlanner::EDROOMTopContext::GSendMinPath()

{

{
 
 
 	return ((VVehicleHalted)&&(VNextPath.pathSteps>=VMinPathSteps));
 
 
}

}



	//********************************** Pools *************************************

	//CEDROOMPOOLCDPath

CAPathPlanner::EDROOMTopContext::CEDROOMPOOLCDPath::CEDROOMPOOLCDPath(TEDROOMUInt32 elemCount, CDPath* pMem, TEDROOMBool * pMemMarks):CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks, sizeof (CDPath)){;}

CDPath *	CAPathPlanner::EDROOMTopContext::CEDROOMPOOLCDPath::AllocData(){
	return(CDPath*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAPathPlanner::EDROOMTopState::EDROOMTopState (CAPathPlanner &act, CEDROOMMemory *pEDROOMMemory  ):
	  EDROOMTopContext( act 
		, VNextPath
		, VNextStepStartPoing
		, VSimError
		, VTargetLocation
		, VVehicleHalted
		, EDROOMPoolCDPath )
	, VSimError ( 1 )
	, VVehicleHalted ( true )
	, EDROOMPoolCDPath ( 3, pEDROOMMemory->poolCDPath, pEDROOMMemory->poolMarkCDPath)
{

}

	//***************************** EDROOMBehaviour ********************************

void CAPathPlanner::EDROOMTopState::EDROOMBehaviour(){

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
			//To Choice Point BranchConfig
			case(Config):
				//Execute Action 
				FConfigPlanner();
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
					FReplyConfigOK();

				//Next Transition is Config
					edroomCurrentTrans.localId = Config_OK;

				//Next State is Idle
					edroomNextState = Idle;
				 } 
				break;
			//To Choice Point BranchCalStep
			case(CalStep):
				//Execute Action 
				FCalPathStep();
				//Evaluate Branch SendMinPath
				if( GSendMinPath() ){
					//Execute Action 
					FProgNextStep();
					//Send Asynchronous Message 
					FSendNextPath();

				//Next Transition is CalStep
					edroomCurrentTrans.localId = CalStep_SendMinPath;

				//Next State is CalculatePath
					edroomNextState = CalculatePath;
				 } 
				//Evaluate Branch MaxStep
				else if( GMaxSteps() ){
					//Execute Action 
					FMaxSteps();

				//Next Transition is CalStep
					edroomCurrentTrans.localId = CalStep_MaxStep;

				//Next State is CalNextPath
					edroomNextState = CalNextPath;
				 } 
				//Evaluate Branch NextStep
				else{
					//Execute Action 
					FProgNextStep();

				//Next Transition is CalStep
					edroomCurrentTrans.localId = CalStep_NextStep;

				//Next State is CalculatePath
					edroomNextState = CalculatePath;
				 } 
				break;
			//Next Transition is Start
			case(Start):
				//Execute Action 
				FProgNextStep();
				//Next State is CalculatePath
				edroomNextState = CalculatePath;
				break;
			//Next Transition is NewTar
			case(NewTar):
				//Msg->Data Handling 
				FNewTarget();
				//Next State is CalculatePath
				edroomNextState = CalculatePath;
				break;
			//Next Transition is PatRequest
			case(PatRequest):
				//Send Asynchronous Message 
				FSendNextPath();
				//Next State is CalculatePath
				edroomNextState = CalculatePath;
				break;
			//Next Transition is ObsTDetected
			case(ObsTDetected):
				//Msg->Data Handling 
				FMarkObstacle();
				//Execute Action 
				FReplanning();
				//Next State is CalculatePath
				edroomNextState = CalculatePath;
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

				//Go to the state CalculatePath
			case(CalculatePath):
				//Entry into the State CalculatePath
				edroomCurrentTrans=EDROOMCalculatePathllegada();
				break;

				//Go to the state CalNextPath
			case(CalNextPath):
				//Entry into the State CalNextPath
				edroomCurrentTrans=EDROOMCalNextPathllegada();
				//Execute Exit Action 
				FProgNextStep();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CAPathPlanner::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CAPathPlanner::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CAPathPlanner::EDROOMTopState::EDROOMIdlellegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (SConfigPathPlanner): 

				 if ( *Msg->GetPInterface() == PathPlannerCtrl) {

					//Next transition is  Config
					edroomCurrentTrans.localId = Config;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

			case (SStartPlanning): 

				 if ( *Msg->GetPInterface() == PathPlannerCtrl) {

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

	// Leaf SubState  CalculatePath

	// ***********************************************************************



TEDROOMTransId CAPathPlanner::EDROOMTopState::EDROOMCalculatePathllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  CalStep
					edroomCurrentTrans.localId = CalStep;
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

	// Leaf SubState  CalNextPath

	// ***********************************************************************



TEDROOMTransId CAPathPlanner::EDROOMTopState::EDROOMCalNextPathllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



