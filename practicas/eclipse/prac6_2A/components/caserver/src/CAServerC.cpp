#include <public/caserver_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAServer::EDROOMTopContext::EDROOMTopContext (CAServer &act
	, TEDROOMUInt8 & EDROOMpVarVresFreeNumber ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pService4(EDROOMcomponent.pService4)
	,pService3(EDROOMcomponent.pService3)
	,pService2(EDROOMcomponent.pService2)
	,pService1(EDROOMcomponent.pService1)
	, VresFreeNumber ( EDROOMpVarVresFreeNumber )
 {

}

CAServer::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,pService4(contex.pService4)
	,pService3(contex.pService3)
	,pService2(contex.pService2)
	,pService1(contex.pService1)
	, VresFreeNumber ( contex.VresFreeNumber )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CAServer::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

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

void	CAServer::EDROOMTopContext::FAck()

{

VresFreeNumber--;
   Msg->reply(SResAck); 
}



void	CAServer::EDROOMTopContext::FFreeResouce()

{

VresFreeNumber++;

}



void	CAServer::EDROOMTopContext::FNack()

{

   Msg->reply(SResAck); 
}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAServer::EDROOMTopState::EDROOMTopState (CAServer &act ):
	  EDROOMTopContext( act 
		, VresFreeNumber )
	, VresFreeNumber ( 2 )
{

}

	//***************************** EDROOMBehaviour ********************************

void CAServer::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans = EDROOMIllegada();

	do{

		switch(edroomCurrentTrans.localId){

			case(Init):
				edroomNextState = Ready;
				break;
			case(ResRequest):
				if( VresFreeNumber ){
					FAck();
					edroomCurrentTrans.localId = ResRequest_Ack;
					edroomNextState = Ready;
				 } 
				else{
					FNack();
					edroomCurrentTrans.localId = ResRequest_Nack;
					edroomNextState = Ready;
				 } 
				break;
			case(FreeResouce):
				FFreeResouce();
				edroomNextState = Ready;
				break;
		}

		switch(edroomNextState){

			case(I):
				edroomCurrentTrans=EDROOMIllegada();
				break;

			case(Ready):
				edroomCurrentTrans=EDROOMReadyllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CAServer::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CAServer::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CAServer::EDROOMTopState::EDROOMReadyllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (SResReq): 

				 {
					edroomCurrentTrans.localId = ResRequest;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

			case (SFreeRes): 

				 {
					edroomCurrentTrans.localId= FreeResouce;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



