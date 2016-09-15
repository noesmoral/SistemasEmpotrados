#ifndef CASERVER_H_
#define CASERVER_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

/**
 * \class   CAServer
 *
 */
class CAServer: public CEDROOMComponent {

public:

	/**
	 * \enum EDROOMCAServerSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum EDROOMCAServerSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SResAck, 
							SResNack, 
							SFreeRes, 
							SResReq };

	/**
	 * \class CAServer::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

	// ********************************************************************
	// ******************* Component Message Data Pools *******************
	// ********************************************************************

		public:

			//! TEDROOMUInt8 Data Pool Memory
			TEDROOMUInt8	poolTEDROOMUInt8[10+1];
			//! TEDROOMUInt8 Data Pool Marks Memory
			TEDROOMBool	poolMarkTEDROOMUInt8[10];


			/** \brief This function is used for setting the Component Memory
			 * 
			 * \param numberOfMsgs number of messages that the component can store
			 * \param msgsMemory memory for the messages that the component can store
			 * \param msgsMemoryMarks memory marks for the messages that the component can store
			 * \param numberOfNodes number of nodes that the component needs
			 * \param queueNodesMemory memory for the component message queues 
			 * \param queueNodesMemoryMarks memory marks for the component message queues 
			 */
			void SetMemory(TEDROOMUInt32 numberOfMsgs
						, CEDROOMMessage * msgsMemory
						, TEDROOMBool * msgsMemoryMarks
						, TEDROOMUInt32 numberOfNodes
						, CEDROOMQueue::CQueueNode * queueNodesMemory
						, TEDROOMBool * queueNodesMemoryMarks);

	};


	// ********************************************************************
	//******************  Component Communication Ports *******************
	// ********************************************************************

	//! pService4 Component Port
	CEDROOMInterface	pService4;
	//! pService3 Component Port
	CEDROOMInterface	pService3;
	//! pService2 Component Port
	CEDROOMInterface	pService2;
	//! pService1 Component Port
	CEDROOMInterface	pService1;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CAServer(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




	//! Component Configuration 
	 int EDROOMConfig();


	//! Component Start 
	 int EDROOMStart();




	#ifdef _EDROOM_SYSTEM_CLOSE

	//! Method that returns true if component is finished 
	TEDROOMBool EDROOMIsComponentFinished();


	#endif

protected:



	//! Component behaviour 
	virtual void EDROOMBehaviour();




public:

	// *****************************	Behaviour  *************************

	// ***********************************************************************

	// class EDROOMTopContext

	// ***********************************************************************



	class EDROOMTopContext {

	protected:

	enum EDROOMCAServerSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, SResAck, SResNack, SFreeRes, SResReq };


		friend class CAServer;

		CAServer &EDROOMcomponent;

		CEDROOMMessage * &Msg;

		CEDROOMMessage * &MsgBack;

		//Ports

		CEDROOMInterface & pService4;
		CEDROOMInterface & pService3;
		CEDROOMInterface & pService2;
		CEDROOMInterface & pService1;

			enum edroomStateId{I, Ready};

			enum IdTrans{Init, ResRequest, ResRequest_Ack, ResRequest_Nack, FreeResouce,  EDROOMMEMORIA };

		//Constants

		const TEDROOMInt8 VresNumber;


		//Variables

		TEDROOMBool *VresFree;
		TEDROOMUInt8 &VresFreeNumber;


		// Pools

		class CEDROOMPOOLTEDROOMUInt8:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLTEDROOMUInt8(TEDROOMUInt32 elemCount,TEDROOMUInt8 *pMem, TEDROOMBool *pMarks);
			TEDROOMUInt8	* AllocData();
		};
		CEDROOMPOOLTEDROOMUInt8	& EDROOMPoolTEDROOMUInt8;


		// CONSTRUCTORS

		EDROOMTopContext (CAServer &act, TEDROOMBool * EDROOMpVarVresFree, TEDROOMUInt8 & EDROOMpVarVresFreeNumber, CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 );

		EDROOMTopContext ( EDROOMTopContext &contex );

	public:

		/**
		 * \brief Search Context transition 
		 * \param edroomCurrentTrans returns the context transition 

		 * \return true if context transition is found 

		 */
		TEDROOMBool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

		//! \brief Get new message from the Queue

		void EDROOMNewMessage () { EDROOMcomponent.EDROOMNewMsg(); }

		/**
		 * \brief Get and Clear the Error Flags 
		 * \return the error flags  

		 */
		 TEDROOMUInt32 GetAndClearErrorFlags(){ return EDROOMcomponent.GetAndClearErrorFlags();}

		// User Defined Functions

		/**
		 * \brief  
		 */
		void	FAck();

		/**
		 * \brief  
		 */
		void	FFreeResouce();

		/**
		 * \brief  
		 */
		void	FInit();

		/**
		 * \brief  
		 */
		void	FMarkResouce();

		/**
		 * \brief  
		 */
		void	FNack();

	};

	// ***********************************************************************

	// class EDROOMTopState

	// ***********************************************************************



	class EDROOMTopState : public EDROOMTopContext {

	protected:



		EDROOMTopContext::edroomStateId edroomCurrentState;

		EDROOMTopContext::edroomStateId edroomNextState;

		//Variables

		TEDROOMBool VresFree[2];
		TEDROOMUInt8 VresFreeNumber;


		// Pools

		CEDROOMPOOLTEDROOMUInt8	EDROOMPoolTEDROOMUInt8;


	public:

		// CONSTRUCTOR

		EDROOMTopState (CAServer &act, CEDROOMMemory *pEDROOMMemory  );


		//***************************** EDROOMBehaviour ********************************

		void EDROOMBehaviour();

		// Inicio**********************************************

		void EDROOMInit();

		// ***********************************************************************

		// SubEstado Inicial 

		// ***********************************************************************



		TEDROOMTransId EDROOMIllegada();

		// ***********************************************************************

		// Leaf SubState Ready

		// ***********************************************************************



		TEDROOMTransId EDROOMReadyllegada();

	};

protected:

	// ********************************  Top State  ****************************

	EDROOMTopState edroomTopState;



};
#endif
