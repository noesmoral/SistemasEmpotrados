#ifndef VEHICLE_H_
#define VEHICLE_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdlocation_iface_v1.h>


//******************************************************************************
// Required software interfaces

#include <public/sensors_iface_v1.h>
#include <public/bprint_iface_v1.h>


/**
 * \class   Vehicle
 *
 */
class Vehicle: public CEDROOMComponent {

public:

	/**
	 * \enum EDROOMVehicleSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum EDROOMVehicleSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SConfigPathPlanner, 
							SMarkObstacle, 
							SNewTargetLocation, 
							SStartPlanning, 
							SConfigError, 
							SConfigOK, 
							SConfigPathTracker, 
							SStopTracking, 
							SStartTracking, 
							SConfigAO, 
							SStart, 
							SObstacleDetected };

	/**
	 * \class Vehicle::CEDROOMMemory
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

			//! CDLocation Data Pool Memory
			CDLocation	poolCDLocation[10+1];
			//! CDLocation Data Pool Marks Memory
			TEDROOMBool	poolMarkCDLocation[10];


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

	//! PathPlannerCtrl Component Port
	CEDROOMInterface	PathPlannerCtrl;
	//! PathTrackerCtrl Component Port
	CEDROOMInterface	PathTrackerCtrl;
	//! AvoidObstaclesSysCtrl Component Port
	CEDROOMInterface	AvoidObstaclesSysCtrl;


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
	Vehicle(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




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

	enum EDROOMVehicleSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, SConfigPathPlanner, SMarkObstacle, SNewTargetLocation, SStartPlanning, SConfigError, SConfigOK, SConfigPathTracker, SStopTracking, SStartTracking, SConfigAO, SStart, SObstacleDetected };


		friend class Vehicle;

		Vehicle &EDROOMcomponent;

		CEDROOMMessage * &Msg;

		CEDROOMMessage * &MsgBack;

		//Ports

		CEDROOMInterface & PathPlannerCtrl;
		CEDROOMInterface & PathTrackerCtrl;
		CEDROOMInterface & AvoidObstaclesSysCtrl;
		CEDROOMTimingInterface & Timer;

			enum edroomStateId{I, StartUp, VehicleReady, SysRecovery, AvObstaclesConfigured, PathTrackerConfigured};

			enum IdTrans{Init, ConfigAvObstacles, ConfigAvObstacles_Error, ConfigAvObstacles_OK, ReStart, ConfigPathTracker, ConfigPathTracker_Error, ConfigPathTracker_OK, ConfigPathPlanner, ConfigPathPlanner_Error, ConfigPathPlanner_OK, ObstacleDetected,  EDROOMMEMORIA };

		//Constants



		//Variables

		CDLocation &VTargetLocation;


		// Pools

		class CEDROOMPOOLCDLocation:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLCDLocation(TEDROOMUInt32 elemCount,CDLocation *pMem, TEDROOMBool *pMarks);
			CDLocation	* AllocData();
		};
		CEDROOMPOOLCDLocation	& EDROOMPoolCDLocation;


		// CONSTRUCTORS

		EDROOMTopContext (Vehicle &act, CDLocation & EDROOMpVarVTargetLocation, CEDROOMPOOLCDLocation & EDROOMpPoolCDLocation );

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

		void	FAvObstaclesError();

		/**
		 * \brief  
		 */
		void	FInvokeConfigAvObstacles();

		/**
		 * \brief  
		 */
		void	FInvokeConfigPathPlanner();

		/**
		 * \brief  
		 */
		void	FInvokeConfigPathTracker();

		/**
		 * \brief  
		 */
		void	FMarkObstacle();

		void	FPathPlannerError();

		void	FPathTrackerError();

		/**
		 * \brief  
		 */
		void	FProgRecovery();

		/**
		 * \brief  
		 */
		void	FProgTimerConfig();

		/**
		 * \brief  
		 */
		void	FStartAvoidObs();

		/**
		 * \brief  
		 */
		void	FStartPlanning();

		/**
		 * \brief  
		 */
		void	FStartTracking();

		void	FStartUp();

		/**
		 * \brief  
		 */
		void	FStopTracking();

		/**
		 * \brief  
		 */
		TEDROOMBool	GConfigError();

	};

	// ***********************************************************************

	// class EDROOMTopState

	// ***********************************************************************



	class EDROOMTopState : public EDROOMTopContext {

	protected:



		EDROOMTopContext::edroomStateId edroomCurrentState;

		EDROOMTopContext::edroomStateId edroomNextState;

		//Variables

		CDLocation VTargetLocation;


		// Pools

		CEDROOMPOOLCDLocation	EDROOMPoolCDLocation;


	public:

		// CONSTRUCTOR

		EDROOMTopState (Vehicle &act, CEDROOMMemory *pEDROOMMemory  );


		//***************************** EDROOMBehaviour ********************************

		void EDROOMBehaviour();

		// Inicio**********************************************

		void EDROOMInit();

		// ***********************************************************************

		// SubEstado Inicial 

		// ***********************************************************************



		TEDROOMTransId EDROOMIllegada();

		// ***********************************************************************

		// Leaf SubState StartUp

		// ***********************************************************************



		TEDROOMTransId EDROOMStartUpllegada();

		// ***********************************************************************

		// Leaf SubState VehicleReady

		// ***********************************************************************



		TEDROOMTransId EDROOMVehicleReadyllegada();

		// ***********************************************************************

		// Leaf SubState SysRecovery

		// ***********************************************************************



		TEDROOMTransId EDROOMSysRecoveryllegada();

		// ***********************************************************************

		// Leaf SubState AvObstaclesConfigured

		// ***********************************************************************



		TEDROOMTransId EDROOMAvObstaclesConfiguredllegada();

		// ***********************************************************************

		// Leaf SubState PathTrackerConfigured

		// ***********************************************************************



		TEDROOMTransId EDROOMPathTrackerConfiguredllegada();

	};

protected:

	// ********************************  Top State  ****************************

	EDROOMTopState edroomTopState;



};
#endif
