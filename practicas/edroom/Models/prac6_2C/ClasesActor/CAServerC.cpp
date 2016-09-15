#include <public/caserver_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAServer::EDROOMTopContext::EDROOMTopContext (CAServer &act
	, TEDROOMUInt8 & EDROOMpVarVresFreeNumber
	, TEDROOMBool * EDROOMpVarVresFree
	, CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pService4(EDROOMcomponent.pService4)
	,pService3(EDROOMcomponent.pService3)
	,pService2(EDROOMcomponent.pService2)
	,pService1(EDROOMcomponent.pService1)
	, VresNumber ( 2 )
	, VresFreeNumber ( EDROOMpVarVresFreeNumber )
	, VresFree ( EDROOMpVarVresFree )
	, EDROOMPoolTEDROOMUInt8 ( EDROOMpPoolTEDROOMUInt8 )
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
	, VresNumber ( 2 )
	, VresFreeNumber ( contex.VresFreeNumber )
	, VresFree ( contex.VresFree )
	, EDROOMPoolTEDROOMUInt8 ( contex.EDROOMPoolTEDROOMUInt8 )
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
  TEDROOMUInt8 * pSResAck_Data = EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 

	TEDROOMUInt8 resId=0;
	VresFreeNumber--;
	while((!VresFree[resId])&&(resId<(VresNumber-1))){
		resId++;
	}
	VresFree[resId]=false;
	*pSResAck_Data=resId;

   Msg->reply(SResAck, pSResAck_Data, &EDROOMPoolTEDROOMUInt8); 
}



void	CAServer::EDROOMTopContext::FFreeResouce()

{

VresFreeNumber++;

}



void	CAServer::EDROOMTopContext::FNack()

{

   Msg->reply(SResAck); 
}



void	CAServer::EDROOMTopContext::FInit()

{

for(TEDROOMUInt8 i=0; i<VresNumber; i++){
	VresFree[i]=true;
}

}



void	CAServer::EDROOMTopContext::FMarkResouce()

{
  TEDROOMUInt8 & varSFreeRes = *(TEDROOMUInt8 *)Msg->data;
	
		// Data acces
	
	// ... =varSFreeRes;
	if(varSFreeRes<VresNumber){
		VresFree[varSFreeRes]=true;
		printf("%s Free ResId %i\n", EDROOMcomponent.EDROOMName
			,(int)varSFreeRes);
	}

}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMUInt8

CAServer::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(TEDROOMUInt32 elemCount, TEDROOMUInt8* pMem, TEDROOMBool * pMemMarks):CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks, sizeof (TEDROOMUInt8)){;}

TEDROOMUInt8 *	CAServer::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::AllocData(){
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAServer::EDROOMTopState::EDROOMTopState (CAServer &act, CEDROOMMemory *pEDROOMMemory  ):
	  EDROOMTopContext( act 
		, VresFreeNumber
		, VresFree
		, EDROOMPoolTEDROOMUInt8 )
	, VresFreeNumber ( 2 )
	, EDROOMPoolTEDROOMUInt8 ( 10, pEDROOMMemory->poolTEDROOMUInt8, pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CAServer::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans = EDROOMIllegada();

	do{

		switch(edroomCurrentTrans.localId){

			case(Init):
				FInit();
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
				FMarkResouce();
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



