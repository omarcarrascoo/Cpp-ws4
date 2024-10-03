#ifndef SENECA_CANISTER_H
#define SENECA_CANISTER_H

#include <iostream>

namespace seneca {
   class Canister {
      char* m_contentName;
      double m_diameter;     // in centimeters 
      double m_height;       // in centimeters
      double m_contentVolume; // in CCs

      /// <summary>
      /// Renders the canister unusable by freeing the content name memory and setting diameter and height to -1
      /// </summary>
      void setToUnusable();
      
      /// <summary>
      /// Returns true if canister volume is below 0.00001
      /// </summary>
      /// <returns>true if the canister is empty</returns>
      bool isEmpty() const;

      /// <summary>
      /// Returns true if height and diameter are within acceptable values
      /// </summary>
      /// <returns>true if canister is usable</returns>
      bool usable() const;

      /// <summary>
      /// Returns true if the content name of the two canisters are the same
      /// </summary>
      /// <param name="C">const Canister& to compare to</param>
      /// <returns>True if the name is the same</returns>
      bool hasSameContent(const Canister& C) const;

      /// <summary>
      /// Returns the capacity of the canister
      /// </summary>
      /// <returns>Capacity of Canister</returns>
      double capacity() const;

      /// <summary>
      /// Returns the content volume. Always less than capacity
      /// </summary>
      /// <returns>Content Volume</returns>
      double volume() const;

   public:
     Canister(); // Default constructor
   Canister(double height, double diameter, const char* contentName = nullptr); // Constructor with diameter and height
    Canister(const char* contentName); // Constructor with content name
    Canister(const Canister& other); // Copy constructor

      // Destructor
      ~Canister(); 

      // Member functions
      Canister& clear(); // Clear method
      Canister& setContent(const char* contentName); // Set content method
      Canister& pour(double quantity); // Pour method with double quantity
      Canister& pour(Canister& can); // Pour method with another Canister
      
      // Display function
      std::ostream& display() const;
   };
}

#endif // !SENECA_CANISTER_H
