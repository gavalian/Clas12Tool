#pragma once
namespace core {

  class dataReader {
    public:
      virtual void open() = 0;
      virtual void close() = 0;
      virtual void* next() = 0;
  };

};

