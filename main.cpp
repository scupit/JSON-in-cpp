#include <iostream>
#include "JsonValue.hpp"

using namespace std;

int main(void) {

  JsonValue val(JsonType::JFLOAT);
  val.setValue(10.5f);
  
  cout << val.getAsFloat() << endl;

  return 0;
}