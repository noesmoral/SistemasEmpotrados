#include <public/caclient_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAClient::EDROOMTopContext::EDROOMTopContext (CAClient &act
	, TEDROOMUInt8 & EDROOMpVarVresId
	, CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pServReq(EDROOMcomponent.pServReq)
	,ResConfigTimer(EDROOMcomponent.ResConfigTimer)
	,Timer(EDROOMcomponent.Timer)
	, VresId ( EDROOMpVarVresId )
	, EDROOMPoolTEDROOMUInt8 ( EDROOMpPoolTEDROOMUInt8 )
 {

}

CAClient::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,pServReq(contex.pServReq)
	,ResConfigTimer(contex.ResConfigTimer)
	,Timer(contex.Timer)
	, VresId ( contex.VresId )
	, EDROOMPoolTEDROOMUInt8 ( contex.EDROOMPoolTEDROOMUInt8 )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CAClient::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

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

void	CAClient::EDROOMTopContext::FFreeRes()

{
   //Allocate data from pool
  TEDROOMUInt8 * pSFreeRes_Data = 
                                             EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 
	
	*pSFreeRes_Data=VresId;
   //Send message 
   pServReq.send(SFreeRes, pSFreeRes_Data, &EDROOMPoolTEDROOMUInt8); 
}



void	CAClient::EDROOMTopContext::FGetResId()

{
   //Handle MsgBack->data
  TEDROOMUInt8 & varSResAck = 
                                                 *(TEDROOMUInt8 *)MsgBack->data;
	
		// Data access
	
	VresId=varSResAck;
 
	printf("%s get ResId %i\n", EDROOMcomponent.EDROOMName, VresId);
 
}



void	CAClient::EDROOMTopContext::FProgRequest()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
	interval =Pr_Time(3,0);
	printf("%s is sleeping\n", EDROOMcomponent.EDROOMName);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FProgWait()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
	interval=Pr_Time(1,0);
	printf("%s is waiting\n", EDROOMcomponent.EDROOMName);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FProgWorking()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
	interval =Pr_Time(2,0);
	printf("%s is working\n", EDROOMcomponent.EDROOMName);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FResRequest()

{

   //Invoke synchronous communication 
   MsgBack=pServReq.invoke(SResReq); 
}



TEDROOMBool	CAClient::EDROOMTopContext::GIsAck()

{

	return (MsgBack->signal==SResAck);

}



// ***********************************************************************

// class EDROOM_CTX_Working_2

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAClient::EDROOM_CTX_Working_2::EDROOM_CTX_Working_2( EDROOMTopContext &contex, TEDROOMUInt8 & EDROOMpVarVresAttempts ):

	EDROOMTopContext(contex)
	, VresAttempts ( EDROOMpVarVresAttempts )
{

}

CAClient::EDROOM_CTX_Working_2::EDROOM_CTX_Working_2( EDROOM_CTX_Working_2 &contex ):

	EDROOMTopContext(contex)
	, VresAttempts ( contex.VresAttempts )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CAClient::EDROOM_CTX_Working_2::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

	TEDROOMBool edroomValidMsg=false; 

	 switch(Msg->signal){

		// Check trigger for signal EDROOMSignalTimeout

		 case (EDROOMSignalTimeout): 

				if ( *Msg->GetPInterface() == Timer) {

					 edroomValidMsg=true;
					edroomCurrentTrans.localId = EDROOMTopContext::FreeRes;
					edroomCurrentTrans.distanceToContext = 1 ;
				 }

			 break;

	}

	if (!edroomValidMsg) {

		 edroomValidMsg = EDROOMTopContext::EDROOMSearchContextTrans(edroomCurrentTrans);
		 if (edroomValidMsg) edroomCurrentTrans.distanceToContext++;
	}

	return(edroomValidMsg);

}

	// User Defined Functions   ****************************

void	CAClient::EDROOM_CTX_Working_2::FProgResConfig()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	interval = Pr_Time(0,100000); // interval of X sec + Y microsec 100ms
   //Program relative timer 
   ResConfigTimer.InformIn( interval ); 
}



void	CAClient::EDROOM_CTX_Working_2::FResConfigFail()

{

printf("%s Res %i Config Fail\n",EDROOMcomponent.EDROOMName,(int)VresId);

}



void	CAClient::EDROOM_CTX_Working_2::FResConfigOK()

{

	printf("%s Res %i Config OK\n", EDROOMcomponent.EDROOMName, (int)VresId);
	VresAttempts=0;

}



void	CAClient::EDROOM_CTX_Working_2::FTryResConfig()

{

VresAttempts++;

}



TEDROOMBool	CAClient::EDROOM_CTX_Working_2::GResConfigOK()

{

	return(VresAttempts>2);

}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMUInt8

CAClient::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(TEDROOMUInt32 elemCount, TEDROOMUInt8* pMem, TEDROOMBool * pMemMarks):CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks, sizeof (TEDROOMUInt8)){;}

TEDROOMUInt8 *	CAClient::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::AllocData(){
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAClient::EDROOMTopState::EDROOMTopState (CAClient &act, CEDROOMMemory *pEDROOMMemory  ):
	  EDROOMTopContext( act 
		, VresId
		, EDROOMPoolTEDROOMUInt8 )
	, EDROOMWorking( Working , *this )
	, EDROOMPoolTEDROOMUInt8 ( 10, pEDROOMMemory->poolTEDROOMUInt8, pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CAClient::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIllegada();

	do{

		//Take next transition

		switch(edroomCurrentTrans.localId){

			//To Choice Point BranchReqRes
			case(ReqRes):
				//Invoke Synchronous Message 
				FResRequest();
				//Evaluate Branch Ack
				if( GIsAck() ){
					//Msg->Data Handling 
					FGetResId();

				//Next Transition is ReqRes
					edroomCurrentTrans.localId = ReqRes_Ack;

				//Next State is Working
					edroomNextState = Working;
				 } 
				//Evaluate Branch Nack
				else{

				//Next Transition is ReqRes
					edroomCurrentTrans.localId = ReqRes_Nack;

				//Next State is WaitingRes
					edroomNextState = WaitingRes;
				 } 
				break;
			//To Choice Point BranchTryAgain
			case(TryAgain):
				//Invoke Synchronous Message 
				FResRequest();
				//Evaluate Branch Ack
				if( GIsAck() ){
					//Msg->Data Handling 
					FGetResId();

				//Next Transition is TryAgain
					edroomCurrentTrans.localId = TryAgain_Ack;

				//Next State is Working
					edroomNextState = Working;
				 } 
				//Evaluate Branch Nack
				else{

				//Next Transition is TryAgain
					edroomCurrentTrans.localId = TryAgain_Nack;

				//Next State is WaitingRes
					edroomNextState = WaitingRes;
				 } 
				break;
			//Next Transition is FreeRes
			case(FreeRes):
				//Send Asynchronous Message 
				FFreeRes();
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//Next Transition is Init
			case(Init):
				//Next State is Idle
				edroomNextState = Idle;
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
				//Execute Entry Action 
				FProgRequest();
				//Entry into the State Idle
				edroomCurrentTrans=EDROOMIdlellegada();
				break;

				//Go to the state Working
			case(Working):
				//Execute Entry Action 
				FProgWorking();
				//Entry into the State Working
				edroomCurrentTrans=EDROOMWorking.llegada((IdTrans)edroomCurrentTrans.localId);
				break;

				//Go to the state WaitingRes
			case(WaitingRes):
				//Execute Entry Action 
				FProgWait();
				//Entry into the State WaitingRes
				edroomCurrentTrans=EDROOMWaitingResllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CAClient::EDROOMTopState::EDROOMInit(){

EDROOMWorking.EDROOMInit();
edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CAClient::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CAClient::EDROOMTopState::EDROOMIdlellegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  ReqRes
					edroomCurrentTrans.localId = ReqRes;
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

	// Leaf SubState  WaitingRes

	// ***********************************************************************



TEDROOMTransId CAClient::EDROOMTopState::EDROOMWaitingResllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  TryAgain
					edroomCurrentTrans.localId = TryAgain;
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

// class EDROOM_SUB_Working_2

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAClient::EDROOM_SUB_Working_2::EDROOM_SUB_Working_2(EDROOMTopContext::edroomStateId idEst, EDROOMTopContext &contex ):
	  EDROOM_CTX_Working_2( contex , VresAttempts )
	, VresAttempts ( 0 )
{ idEstado =idEst; }

	// llegada**********************************************

TEDROOMTransId CAClient::EDROOM_SUB_Working_2::llegada(EDROOMTopContext::IdTrans transLlegada){

	TEDROOMTransId edroomCurrentTrans;

	int salirContexto=0;

	//Transition at Context Entry
	switch (transLlegada){

		//From entry point ReqRes_Ack
		case(EDROOMTopContext::ReqRes_Ack):
			edroomCurrentTrans.localId= ToResConfig2;
			edroomNextState = ResConfig;
			break;
		//From entry point TryAgain_Ack
		case(EDROOMTopContext::TryAgain_Ack):
			edroomCurrentTrans.localId= ToResConfig;
			edroomNextState = ResConfig;
			break;
		case(EDROOMTopContext::EDROOMMEMORIA):
			//Memory Entry added
			edroomCurrentTrans.localId = EDROOMMEMORIA ;
			edroomNextState = edroomCurrentState;
			break;
		default:
			//Default is memory entry
			edroomCurrentTrans.localId = EDROOMMEMORIA ;
			edroomNextState = edroomCurrentState;
			break;
	}

	do{

		//Entry into the Next State 
		switch(edroomNextState){

				//Go to the state ResConfig
			case(ResConfig):
				//Execute Entry Action 
				FProgResConfig();
				//Entry into the State ResConfig
				edroomCurrentTrans=EDROOMResConfigllegada();
				break;

				//Go to the state DoWork
			case(DoWork):
				//Entry into the State DoWork
				edroomCurrentTrans=EDROOMDoWorkllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

		if (edroomCurrentTrans.distanceToContext == 0){

			switch (edroomCurrentTrans.localId){

				//To Choice Point BranchTryResConfig
				case(TryResConfig):
					//Execute Action 
					FTryResConfig();
					//Evaluate Branch ResConfigOK
					if( GResConfigOK() ){
						//Execute Action 
						FResConfigOK();

					//Next Transition is TryResConfig
						edroomCurrentTrans.localId = TryResConfig_ResConfigOK;

					//Next State is DoWork
						edroomNextState = DoWork;
						salirContexto=0;
					 } 
					//Evaluate Branch ResConfigError
					else{
						//Execute Action 
						FResConfigFail();

					//Next Transition is TryResConfig
						edroomCurrentTrans.localId = TryResConfig_ResConfigError;

					//Next State is ResConfig
						edroomNextState = ResConfig;
						salirContexto=0;
					 } 
					break;
			}

		}else salirContexto=1;

	}while(!salirContexto);

	edroomCurrentTrans.distanceToContext--;

	return(edroomCurrentTrans);

}



	// Inicio**********************************************

void CAClient::EDROOM_SUB_Working_2::EDROOMInit(){

}



	// ***********************************************************************

	// Leaf SubState  ResConfig

	// ***********************************************************************



TEDROOMTransId CAClient::EDROOM_SUB_Working_2::EDROOMResConfigllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == ResConfigTimer) {

					//Next transition is  TryResConfig
					edroomCurrentTrans.localId = TryResConfig;
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

	// Leaf SubState  DoWork

	// ***********************************************************************



TEDROOMTransId CAClient::EDROOM_SUB_Working_2::EDROOMDoWorkllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



