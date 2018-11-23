
#include "Core/algorithm.h"
#include "bank.h"
#include "reader.h"
#include <map>
#include <string>

namespace clas12 {

  class recEvBank : public hipo::bank {
    public:
      void init( const char *, hipo::reader &);
     
      int getInt( std::string b, int i ) { return bank::getInt( order[b], i); }
      int getLong( std::string b, int i ) { return bank::getLong( order[b], i); }
      float getFloat( std::string b, int i) { return bank::getFloat( order[b], i); };
      double getDouble( std::string b, int i) { return bank::getDouble( order[b], i); };

      void addBranch( std::string );
    private:
      std::map<std::string, int> order;
  };

  class recEventReader : public core::algorithm {
    public:
      recEventReader() {};

      virtual void init();
      virtual void processEvent();
      virtual void terminate() {};

    private:
      recEvBank _bank;
      std::map<std::string,int> _index;
  };

}


