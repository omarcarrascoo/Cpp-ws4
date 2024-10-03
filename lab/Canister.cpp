#include <istream>
#include "cstr.h"  
#include "Canister.h"
using namespace std;
namespace seneca {

   const double PI = 3.14159265;
   

   bool Canister::isEmpty() const {
      return m_contentVolume < 0.00001;
   }

   bool Canister::usable() const
   {
      return m_height >= 10 && m_height <= 40 && m_diameter >= 10 && m_diameter <= 30;
   }

   void Canister::setToUnusable(){
      freeMem(m_contentName);
      m_diameter = m_height = -1.0;
   }

   double Canister::capacity() const {
      return PI * (m_height-0.267) * (m_diameter/2) * (m_diameter / 2);
   }

      bool Canister::hasSameContent(const Canister& C)const {
      return m_contentName && C.m_contentName && strcmp(m_contentName, C.m_contentName) == 0;
   }

   double Canister::volume() const {
      return m_contentVolume;
   }

   std::ostream& Canister::display() const {
      cout.setf(ios::fixed);
      cout.precision(1);
      cout.width(7);
      cout << capacity() << "cc (";
      cout.width(4);
      cout << m_height << "x";
      cout.width(4);
      cout << m_diameter << ") Canister";
      if (!usable()) {
         cout << " is  Unusable   recycle!";
      }
      else {
         cout << " of ";
         cout.width(7);
         cout << volume() << "cc   " << (m_contentName?m_contentName:"Sanetized and Empty");
      }
      return cout;
   }


   Canister::Canister() {
    m_height = 13.0;
    m_diameter = 10.0;
    m_contentVolume = 0.0;
    m_contentName = nullptr;
   }

   Canister::Canister(const char* contentName) {
    m_height = 13.0;        
    m_diameter = 10.0;     
    m_contentVolume = 0.0;  
    m_contentName = nullptr;

    if (contentName != nullptr) {
        alocpy(m_contentName, contentName); 
    }    
   }

// Three-argument constructor
   Canister::Canister(double diameter, double height, const char* contentName) {
    m_diameter = diameter;
    m_height = height;
    m_contentVolume = 0.0;
    m_contentName = nullptr;

    if (contentName) {
        alocpy(m_contentName, contentName); // Use alocpy to set content name
    }
}


    // Destructor
   Canister::~Canister() {
      freeMem(m_contentName); 
   }

   // Clear method
   Canister& Canister::clear() {
      freeMem(m_contentName); 
      m_contentName = nullptr;       
      m_contentVolume = 0.0;   
      return *this;   
   }

   // SetContent method
   Canister& Canister::setContent(const char* contentName) {
      if (contentName != nullptr && usable()) {
         if (m_contentName == nullptr || isEmpty()) {
            alocpy(m_contentName, contentName); 
         } else if (!hasSameContent(*this)) {
            setToUnusable();
         }
      }
      return *this; 
   }

   // Pour method with double quantity
   Canister& Canister::pour(double quantity) {
      if (usable() && quantity > 0) {
         if (m_contentVolume + quantity <= capacity()) {
            m_contentVolume += quantity; 
         } else {
            setToUnusable(); 
         }
      }
      return *this;
   }

   // Pour method with another Canister
   Canister& Canister::pour(Canister& can) {
      if (usable() && can.usable()) {
         double availableSpace = capacity() - volume();
         if (can.volume() > availableSpace) {
            can.m_contentVolume -= availableSpace; 
            m_contentVolume = capacity();          
         } else {
            m_contentVolume += can.volume();       
            can.m_contentVolume = 0.0;             
         }
         setContent(can.m_contentName);           
      }
      return *this; 
   }


Canister::Canister(const Canister& other) {
    // Use alocpy to allocate and copy content name
    alocpy(m_contentName, other.m_contentName);
    
    // Copy other attributes
    m_diameter = other.m_diameter;
    m_height = other.m_height;
    m_contentVolume = other.m_contentVolume;
}






}
