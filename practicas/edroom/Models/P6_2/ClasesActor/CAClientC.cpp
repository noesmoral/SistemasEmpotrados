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
  TEDROOMUInt8 * pSFreeRes_Data = EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 
	
	*pSFreeRes_Data=VresId;
   pServReq.send(SFreeRes, pSFreeRes_Data, &EDROOMPoolTEDROOMUInt8); 
}



void	CAClient::EDROOMTopContext::FProgRequest()

{
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
	interval =Pr_Time(3,0);
	printf("%s is sleeping\n", EDROOMcomponent.EDROOMName);
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FProgWait()

{
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
	interval=Pr_Time(1,0);
	printf("%s is waiting\n", EDROOMcomponent.EDROOMName);
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FProgWorking()

{
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
	interval =Pr_Time(2,0);
	printf("%s is working\n", EDROOMcomponent.EDROOMName);
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FResRequest()

{

   MsgBack=pServReq.invoke(SResReq); 
}



TEDROOMBool	CAClient::EDROOMTopContext::GIsAck()

{

	return (MsgBack->signal==SResAck);

}



void	CAClient::EDROOMTopContext::FGetResId()

{
  TEDROOMUInt8 & varSResAck = *(TEDROOMUInt8 *)MsgBack->data;
	
		// Data access
	
	VresId=varSResAck;

	printf("%s get ResId %i\n", EDROOMcomponent.EDROOMName, VresId);
 
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
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	interval = Pr_Time(0,100000); // interval of X sec + Y microsec 100ms
   ResConfigTimer.InformIn( interval ); 
}



void	CAClient::EDROOM_CTX_Working_2::FTryResConfig()

{

VresAttempts++;

}



void	CAClient::EDROOM_CTX_Working_2::FResConfigFail()

{

printf("%s Res %i Config Fail\n",EDROOMcomponent.EDROOMName,(int)VresId);

}



TEDROOMBool	CAClient::EDROOM_CTX_Working_2::GResConfigOK()

{

	return(VresAttempts>2);

}



void	CAClient::EDROOM_CTX_Working_2::FResConfigOK()

{

	printf("%s Res %i Config OK\n", EDROOMcomponent.EDROOMName, (int)VresId);
	VresAttempts=0;

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

	edroomCurrentTrans = EDROOMIllegada();

	do{

		switch(edroomCurrentTrans.localId){

			case(ReqRes):
				FResRequest();
				if( GIsAck() ){
					FGetResId();
					edroomCurrentTrans.localId = ReqRes_Ack;
					edroomNextState = Working;
				 } 
				else{
					edroomCurrentTrans.localId = ReqRes_Nack;
					edroomNextState = WaitingRes;
				 } 
				break;
			case(TryAgain):
				FResRequest();
				if( GIsAck() ){
					FGetResId();
					edroomCurrentTrans.localId = TryAgain_Ack;
					edroomNextState = Working;
				 } 
				else{
					edroomCurrentTrans.localId = TryAgain_Nack;
					edroomNextState = WaitingRes;
				 } 
				break;
			case(FreeRes):
				FFreeRes();
				edroomNextState = Idle;
				break;
			case(Init):
				edroomNextState = Idle;
				break;
		}

		switch(edroomNextState){

			case(I):
				edroomCurrentTrans=EDROOMIllegada();
				break;

			case(Idle):
				FProgRequest();
				edroomCurrentTrans=EDROOMIdlellegada();
				break;

			case(Working):
				FProgWorking();
				edroomCurrentTrans=EDROOMWorking.llegada((IdTrans)edroomCurrentTrans.localId);
				break;

			case(WaitingRes):
				FProgWait();
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

	switch (transLlegada){

		case(EDROOMTopContext::ReqRes_Ack):
			edroomCurrentTrans.localId= ToResConfig2;
			edroomNextState = ResConfig;
			break;
		case(EDROOMTopContext::TryAgain_Ack):
			edroomCurrentTrans.localId= ToResConfig;
			edroomNextState = ResConfig;
			break;
		case(EDROOMTopContext::EDROOMMEMORIA):
			edroomCurrentTrans.localId = EDROOMMEMORIA ;
			edroomNextState = edroomCurrentState;
			break;
		default:
			edroomCurrentTrans.localId = EDROOMMEMORIA ;
			edroomNextState = edroomCurrentState;
			break;
	}

	do{

		switch(edroomNextState){

			case(ResConfig):
				FProgResConfig();
				edroomCurrentTrans=EDROOMResConfigllegada();
				break;

			case(DoWork):
				edroomCurrentTrans=EDROOMDoWorkllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

		if (edroomCurrentTrans.distanceToContext == 0){

			switch (edroomCurrentTrans.localId){

				case(TryResConfig):
					FTryResConfig();
					if( GResConfigOK() ){
						FResConfigOK();
						edroomCurrentTrans.localId = TryResConfig_ResConfigOK;
						edroomNextState = DoWork;
						salirContexto=0;
					 } 
					else{
						FResConfigFail();
						edroomCurrentTrans.localId = TryResConfig_ResConfigError;
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



