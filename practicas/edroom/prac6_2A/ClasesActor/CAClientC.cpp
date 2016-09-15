#include <public/caclient_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAClient::EDROOMTopContext::EDROOMTopContext (CAClient &act ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pServReq(EDROOMcomponent.pServReq)
	,Timer(EDROOMcomponent.Timer)
 {

}

CAClient::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,pServReq(contex.pServReq)
	,Timer(contex.Timer)
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

   pServReq.send(SFreeRes); 
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



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAClient::EDROOMTopState::EDROOMTopState (CAClient &act ):
	  EDROOMTopContext( act  )
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
					edroomCurrentTrans.localId = ReqRes_Ack;
					edroomNextState = Working;
				 } 
				else{
					edroomCurrentTrans.localId = ReqRes_Nack;
					edroomNextState = Wait;
				 } 
				break;
			case(TryAgain):
				FResRequest();
				if( GIsAck() ){
					edroomCurrentTrans.localId = TryAgain_Ack;
					edroomNextState = Working;
				 } 
				else{
					edroomCurrentTrans.localId = TryAgain_Nack;
					edroomNextState = Wait;
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
				edroomCurrentTrans=EDROOMWorkingllegada();
				break;

			case(Wait):
				FProgWait();
				edroomCurrentTrans=EDROOMWaitllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CAClient::EDROOMTopState::EDROOMInit(){

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

	// Leaf SubState  Working

	// ***********************************************************************



TEDROOMTransId CAClient::EDROOMTopState::EDROOMWorkingllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId= FreeRes;
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

	// Leaf SubState  Wait

	// ***********************************************************************



TEDROOMTransId CAClient::EDROOMTopState::EDROOMWaitllegada(){

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



