#include "commands.hpp"
#include <limits>
#include <string>

void sobolevsky::inputFromFile(std::istream &file, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
    }
    std::string name;
    file >> name;
    AVLtree< int, std::string, int > tempTree;
    int key;
    while (file >> key)
    {
      std::string value;
      file >> value;
      tempTree.insert(std::make_pair(key, value));
    }
    data.insert(std::make_pair(name, tempTree));
  }
}

void sobolevsky::getError(std::ostream &out, std::string text)
{
  out << text << "\n";
}

void sobolevsky::getPrint(std::istream &in, std::ostream &out, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  std::string name;
  in >> name;
  AVLtree< int, std::string, int > currTree(data.at(name));
  if (currTree.size() == 0)
  {
    throw std::invalid_argument("<EMPTY>");
  }
  out << name << " ";
  for (AVLtree< int, std::string, int >::ConstIterator iter(currTree.cbegin()); iter != currTree.cend();)
  {
    out << iter->first << " " << iter->second;
    iter++;
    out << (iter != currTree.cend() ? " " : "\n");
  }
}

void sobolevsky::checkName(AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data, AVLtree< int, std::string, int > &newTree,
std::string newName)
{
  if (data.find(newName) != data.end())
  {
    data.at(newName).swap(newTree);
    newTree.clear();
  }
  else
  {
    data.insert(std::make_pair(newName, newTree));
  }
}

void sobolevsky::getComplement(std::istream &in, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  AVLtree< int, std::string, int > newTree;
  if (data.at(name1).size() == 0 || data.at(name2).size() == 0)
  {}
  else
  {
    for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
    {
      if (data.at(name2).find(iter->first) == data.at(name2).end())
      {
        newTree.insert(std::make_pair(iter->first, iter->second));
      }
    }
  }

  checkName(data, newTree, newName);
}

void sobolevsky::getIntersect(std::istream &in, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  AVLtree< int, std::string, int > newTree;
  if (data.at(name1).size() == 0 || data.at(name2).size() == 0)
  {}
  else
  {
    for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
    {
      if (data.at(name2).find(iter->first) != data.at(name2).end())
      {
        newTree.insert(std::make_pair(iter->first, iter->second));
      }
    }
  }

  checkName(data, newTree, newName);
}

void sobolevsky::getUnion(std::istream &in, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  AVLtree< int, std::string, int > newTree;
  if (data.at(name1).size() == 0 && data.at(name2).size() == 0)
  {}
  else if (data.at(name1).size() != 0 && data.at(name2).size() == 0)
  {
    for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
    {
      newTree.insert(std::make_pair(iter->first, iter->second));
    }
  }
  else if (data.at(name1).size() == 0 && data.at(name2).size() != 0)
  {
    for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name2).cbegin()); iter != data.at(name2).cend(); iter++)
    {
      newTree.insert(std::make_pair(iter->first, iter->second));
    }
  }
  else
  {
    for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
    {
      newTree.insert(std::make_pair(iter->first, iter->second));
    }

    for (AVLtree< int, std::string, int >::ConstIterator iter(data.at(name2).cbegin()); iter != data.at(name2).cend(); iter++)
    {
      if (data.at(name1).find(iter->first) == data.at(name1).end())
      {
        newTree.insert(std::make_pair(iter->first, iter->second));
      }
    }
  }

  checkName(data, newTree, newName);
}
