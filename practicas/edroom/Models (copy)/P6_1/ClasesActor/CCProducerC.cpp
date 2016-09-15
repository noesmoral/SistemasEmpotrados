#include <public/ccproducer_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCProducer::EDROOMTopContext::EDROOMTopContext (CCProducer &act
	, TEDROOMByte & EDROOMpVarVaux
	, CEDROOMPOOLTEDROOMByte & EDROOMpPoolTEDROOMByte ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pOut(EDROOMcomponent.pOut)
	, VauxLimit ( 'z' )
	, Vaux ( EDROOMpVarVaux )
	, EDROOMPoolTEDROOMByte ( EDROOMpPoolTEDROOMByte )
 {

}

CCProducer::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,pOut(contex.pOut)
	, VauxLimit ( 'z' )
	, Vaux ( contex.Vaux )
	, EDROOMPoolTEDROOMByte ( contex.EDROOMPoolTEDROOMByte )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CCProducer::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

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

void	CCProducer::EDROOMTopContext::FResetData()

{

	Vaux='a';

}



void	CCProducer::EDROOMTopContext::FSendData()

{
  TEDROOMByte * pSData_Data = EDROOMPoolTEDROOMByte.AllocData();
	
		// Complete Data 
	
	*pSData_Data=Vaux;
	
	Vaux++;
   pOut.send(SData, pSData_Data, &EDROOMPoolTEDROOMByte); 
}



TEDROOMBool	CCProducer::EDROOMTopContext::GNeedReset()

{

	return(Vaux>VauxLimit);

}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMByte

CCProducer::EDROOMTopContext::CEDROOMPOOLTEDROOMByte::CEDROOMPOOLTEDROOMByte(TEDROOMUInt32 elemCount, TEDROOMByte* pMem, TEDROOMBool * pMemMarks):CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks, sizeof (TEDROOMByte)){;}

TEDROOMByte *	CCProducer::EDROOMTopContext::CEDROOMPOOLTEDROOMByte::AllocData(){
	return(TEDROOMByte*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCProducer::EDROOMTopState::EDROOMTopState (CCProducer &act, CEDROOMMemory *pEDROOMMemory  ):
	  EDROOMTopContext( act 
		, Vaux
		, EDROOMPoolTEDROOMByte )
	, Vaux ( 'a' )
	, EDROOMPoolTEDROOMByte ( 10, pEDROOMMemory->poolTEDROOMByte, pEDROOMMemory->poolMarkTEDROOMByte)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCProducer::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans = EDROOMIllegada();

	do{

		switch(edroomCurrentTrans.localId){

			case(Init):
				edroomNextState = Ready;
				break;
			case(SendData):
				FSendData();
				if( GNeedReset() ){
					FResetData();
					edroomCurrentTrans.localId = SendData_ResetData;
					edroomNextState = Ready;
				 } 
				else{
					edroomCurrentTrans.localId = SendData_DataOk;
					edroomNextState = Ready;
				 } 
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

void CCProducer::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCProducer::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCProducer::EDROOMTopState::EDROOMReadyllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (SConReady): 

				 if ( *Msg->GetPInterface() == pOut) {

					edroomCurrentTrans.localId = SendData;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



