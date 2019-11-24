#include <iostream>
#include "JsonParser.hpp"
#include "JsonValue.hpp"

using namespace std;

int main(void) {

  JsonValue jVal({
    {"hello", "Noice thing"},
    {"Very nice plan", "other place"},
    {"An Array", JsonValue(
      {
        12,
        -32.736f,
        "someone",
        nullptr,
        false,
        true,
        false,
        JsonValue({
          {"This object is in the array", nullptr},
          {"Noice", -10}
        })
      }
    )},
    {"Another Object", JsonValue(
      {
        {"Key in that object", "very nice"},
        {"You", 12.3f},
        {"boolean", true}
      }
    )},
    {"Should be null", nullptr}
  });

  cout << jVal << endl;

  return 0;
}