#include <iostream>
#include "doublelist.hpp"
#include "functions.hpp"

int main()
{
  kovshikov::DoubleList< std::pair< std::string, kovshikov::DoubleList< size_t > > > allPairs;
  bool isBigNumber = false;
  kovshikov::inputPairs(allPairs, isBigNumber);
  kovshikov::outputListName(allPairs);
 /* DoubleList< size_t > summaList;
  DoubleList< DoubleList< size_t > > resultList;
  DoubleList< std::pair< std::string, DoubleList< size_t > > >::Iterator iteratorAllPairs = allPairs.begin();
  */
  kovshikov::outputResult(allPairs, isBigNumber);
  if(isBigNumber == true)
  {
    std::cerr << "too many numbers were entered\n";
    return 1;
  }
  return 0;
}