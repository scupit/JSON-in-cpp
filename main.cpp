#include <iostream>
#include "JsonValue.hpp"

using namespace std;

int main(void) {

  JsonValue val(JsonType::JFLOAT);
  val.setValue(10.5f);
  
  cout << *static_cast<float*>(val.getValue()) << endl;

  return 0;
}