#pragma once
namespace core {
  class dataWriter {
    public:
      virtual void open()  = 0;
      virtual void close() = 0;
      virtual void write() = 0;
  };

};

