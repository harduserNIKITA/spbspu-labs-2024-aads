#include <iostream>
#include "ExpressionCalc.hpp"
#include <fstream>

int main(int argc, char** argv)
{
  hohlova::ExpressionCalc calculator;
  hohlova::Stack< long long > results;
  try
  {
    if (argc == 1)
    {
      calculator.readExpression(std::cin);
    }
    else if (argc == 2)
    {
      std::ifstream stream(argv[1]);
      if (stream.eof() == 0)
        throw std::runtime_error("File is empty!\n");

      calculator.readExpression(stream);
    }
    else
    {
      std::cerr << "Invalid number of command line arguments\n";
    }
    calculator.CalculateExpressions(results);
  }
  catch (const std::runtime_error& err)
  {
    std::cout << err.what();
    return 1;
  }
  while (!results.empty())
  {
    std::cout << results.top();
    if (results.size() != 1)
    {
      std::cout << ' ';
    }
    results.pop();
  }
  std::cout << "\n";
  return 0;
}
