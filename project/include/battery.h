/**
 * @file vector.h
 *
 * @copyright Lin Huynh, All rights reserved.
 */

#ifndef INC_BATTERY_H_
#define INC_BATTERY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <cmath>
#include "utils.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/*******************************************************************************
 * @brief The main class for the battery.
 *
 * Calls to \ref Battery() to generate a new instance of the class
*******************************************************************************/
namespace csci3081 {
class Battery {
    private:
        int BatteryID;              //!< Unique ID (interger presentation for each Battery istances)
        float maxCharge = 10000;      //!< The maximum capacity of the battery in secs
        float remainingLifeinSec;     //!< The remaining life of the battery in secs
        bool isDead;                //!< Boolean attribute to see if the battery is below 20%
                                    //!< False if below 20%, true otherwise
        int displayBar;             //!< Bar represents the leftover capacity of the battery
                                    //!< Maximum of displayBar is 5
    
    public:
        /**
        * @brief Default Constructor.
        * This sets up an instance of Battery with empty remaining life
        */
        Battery();
    
        /**
        * @brief Constructor to set up an instance of Battery with passing remaining life
        * @param[in] remainingLifeinSec_ current remaining life in the battery
        */
        Battery(float remainingLifeinSec_);
    
        /**
        * This functions return the remaining life of the battery
        */
        float GetRemainingLife();
    
        /**
        * This functions return the current displayBar of the Battery
        */
        int GetDisplayBar();
    
        /**
        * This functions return the ID of the battery
        */
        int GetId();

        /**
        * @brief Depleting The Battery. Should be used everytime the object using battery is in action
        * @param[in] sec seconds battery is used
        */
        void Depleting(float sec);
        
        /**
        * @brief Charging The Battery
        * @param[in] sec seconds battery is charged
        * @param[out] True if the battery is charged, False otherwise
        */
        bool Charging(float sec);
        
        /**
        * @brief This function returns the time battery needed charged to be full
        */
        float TimeToFull();
        
        /**
        * @brief This returns a boolean value for the battery's life
        *       False if battery is dead (below 20%)
        *       True otherwise
        */
        bool IsDead();
};

}

#endif /* INC_BATTERY_H_ */