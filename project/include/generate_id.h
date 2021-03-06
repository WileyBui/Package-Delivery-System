#ifndef GENERATE_ID_H
#define GENERATE_ID_H

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief GenerateId class generates a static unique identifier to the customer, 
 * drone, robot, package, and battery objects. Each time GenerateNewId() is 
 * called, the `id` variable gets incremented.
 */
class GenerateId {
 public:

  /**
   * This function statically increments the ID counter to create a unique identifier.
   */
  static int GenerateNewId();

  /**
   * Warning: this function SHOULD ONLY BE CALLED during Google Test cases.
   * This function resets the ID counter back to 0. 
   * @return Current reset ID.
   */
  int ResetId();

 private:
  static int id;
};

}  // namespace csci3081

#endif /* GENERATE_ID_H */