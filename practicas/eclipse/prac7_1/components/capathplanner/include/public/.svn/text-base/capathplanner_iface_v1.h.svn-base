#ifndef CAPATHPLANNER_H_
#define CAPATHPLANNER_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdlocation_iface_v1.h>
#include <public/cdpath_iface_v1.h>


//******************************************************************************
// Required software interfaces

#include <public/sensors_iface_v1.h>
#include <public/actuators_iface_v1.h>
#include <public/planner_iface_v1.h>
#include <public/bprint_iface_v1.h>


/**
 * \class   CAPathPlanner
 *
 */
class CAPathPlanner: public CEDROOMComponent {

public:

	/**
	 * \enum EDROOMCAPathPlannerSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum EDROOMCAPathPlannerSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							STrackPath, 
							SPathRequest, 
							SConfigPathPlanner, 
							SMarkObstacle, 
							SNewTargetLocation, 
							SStartPlanning, 
							SConfigError, 
							SConfigOK };

	/**
	 * \class CAPathPlanner::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

			//************ Component Timing Service Memory************

			//!Component Timing Service Timer Info Memory
			CEDROOMTimerInfo TimerInf[3];
			//!Component Timing Service Timer Info Marks Memory
			TEDROOMBool TimerInfMarks[3];
			//!Component Timing Service TimeOut Messages Memory
			CEDROOMTimeOutMessage TimeOutMsgs[3];
			//!Component Timing Service TimeOut Messages Marks Memory
			TEDROOMBool TimeOutMsgsMarks[3];

		public: 

			//!Component Timing Service Memory Object
			CEDROOMTimingMemory TimingMemory;

	// ********************************************************************
	// ******************* Component Message Data Pools *******************
	// ********************************************************************

			//! CDPath Data Pool Memory
			CDPath	poolCDPath[3+1];
			//! CDPath Data Pool Marks Memory
			TEDROOMBool	poolMarkCDPath[3];


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

	//! TrackPath Component Port
	CEDROOMInterface	TrackPath;
	//! PathPlannerCtrl Component Port
	CEDROOMInterface	PathPlannerCtrl;


	// ********************************************************************
	// ********************  Timing Service Interface *********************
	// ********************************************************************

	//! Timing Service Access Point. It is common to all timing ports.
	CEDROOMTimingSAP	 EDROOMtimingSAP;


	//! Timer Timing Port
	CEDROOMTimingInterface	Timer;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CAPathPlanner(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




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

	enum EDROOMCAPathPlannerSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, STrackPath, SPathRequest, SConfigPathPlanner, SMarkObstacle, SNewTargetLocation, SStartPlanning, SConfigError, SConfigOK };


		friend class CAPathPlanner;

		CAPathPlanner &EDROOMcomponent;

		CEDROOMMessage * &Msg;

		CEDROOMMessage * &MsgBack;

		//Ports

		CEDROOMInterface & TrackPath;
		CEDROOMInterface & PathPlannerCtrl;
		CEDROOMTimingInterface & Timer;

			enum edroomStateId{I, Idle, CalculatePath, CalNextPath};

			enum IdTrans{Init, Config, Config_Error, Config_OK, CalStep, CalStep_SendMinPath, CalStep_MaxStep, CalStep_NextStep, Start, NewTar, PatRequest, ObsTDetected,  EDROOMMEMORIA };

		//Constants

		const TEDROOMUInt8 VMaxPathSteps;
		const TEDROOMUInt8 VMinPathSteps;


		//Variables

		CDPath &VNextPath;
		CDLocation &VNextStepStartPoing;
		TEDROOMUInt8 &VSimError;
		CDLocation &VTargetLocation;
		TEDROOMBool &VVehicleHalted;


		// Pools

		class CEDROOMPOOLCDPath:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLCDPath(TEDROOMUInt32 elemCount,CDPath *pMem, TEDROOMBool *pMarks);
			CDPath	* AllocData();
		};
		CEDROOMPOOLCDPath	& EDROOMPoolCDPath;


		// CONSTRUCTORS

		EDROOMTopContext (CAPathPlanner &act, CDPath & EDROOMpVarVNextPath, CDLocation & EDROOMpVarVNextStepStartPoing, TEDROOMUInt8 & EDROOMpVarVSimError, CDLocation & EDROOMpVarVTargetLocation, TEDROOMBool & EDROOMpVarVVehicleHalted, CEDROOMPOOLCDPath & EDROOMpPoolCDPath );

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

		void	FCalPathStep();

		void	FConfigPlanner();

		/**
		 * \brief  
		 */
		void	FMarkObstacle();

		void	FMaxSteps();

		/**
		 * \brief  
		 */
		void	FNewTarget();

		/**
		 * \brief  
		 */
		void	FProgNextStep();

		void	FReplanning();

		/**
		 * \brief  
		 */
		void	FReplyConfigOK();

		/**
		 * \brief  
		 */
		void	FReplySimError();

		/**
		 * \brief  
		 */
		void	FSendNextPath();

		TEDROOMBool	GMaxSteps();

		TEDROOMBool	GSendMinPath();

	};

	// ***********************************************************************

	// class EDROOMTopState

	// ***********************************************************************



	class EDROOMTopState : public EDROOMTopContext {

	protected:



		EDROOMTopContext::edroomStateId edroomCurrentState;

		EDROOMTopContext::edroomStateId edroomNextState;

		//Variables

		CDPath VNextPath;
		CDLocation VNextStepStartPoing;
		TEDROOMUInt8 VSimError;
		CDLocation VTargetLocation;
		TEDROOMBool VVehicleHalted;


		// Pools

		CEDROOMPOOLCDPath	EDROOMPoolCDPath;


	public:

		// CONSTRUCTOR

		EDROOMTopState (CAPathPlanner &act, CEDROOMMemory *pEDROOMMemory  );


		//***************************** EDROOMBehaviour ********************************

		void EDROOMBehaviour();

		// Inicio**********************************************

		void EDROOMInit();

		// ***********************************************************************

		// SubEstado Inicial 

		// ***********************************************************************



		TEDROOMTransId EDROOMIllegada();

		// ***********************************************************************

		// Leaf SubState Idle

		// ***********************************************************************



		TEDROOMTransId EDROOMIdlellegada();

		// ***********************************************************************

		// Leaf SubState CalculatePath

		// ***********************************************************************



		TEDROOMTransId EDROOMCalculatePathllegada();

		// ***********************************************************************

		// Leaf SubState CalNextPath

		// ***********************************************************************



		TEDROOMTransId EDROOMCalNextPathllegada();

	};

protected:

	// ********************************  Top State  ****************************

	EDROOMTopState edroomTopState;



};
#endif
