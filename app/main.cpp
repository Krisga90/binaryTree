#include <iostream>
#include <thread>

#include <chrono>
#include <map>
#include <mutex>
#include <string>

#include "binary_tree.h"



void print_tree(const BinaryTree& bt);
void tree_helper(const Node* bt, int lvl, std::vector<std::pair<int, std::vector<VAL>>>& tree);

int main() {
  BinaryTree bt = {5,8,7, 1, 2, 3, 4, 5, 10, 9, 11, 6, 14, 10};

  print_tree(bt);
  bt.removeElement(7);
  print_tree(bt);

  return 0;
}

void print_tree(const BinaryTree& bt)
{
  std::vector<std::pair<int, std::vector<VAL>>> tree;
  
  tree_helper(bt.m_trunk, 0, tree);
  
  std::cout <<tree.size() << " aa\n";

  for(auto pair : tree)
  {
    std:: cout << pair.first << ": ";
    for (auto value: pair.second)
    {
      std::cout << value <<", ";
    }
    std::cout << std::endl;
  }
}

void tree_helper(const Node* node, int lvl, std::vector<std::pair<int, std::vector<VAL>>>& tree)
{
  auto value = node->m_data;
  if (tree.size() < lvl + 1)
  {
    std::pair<int, std::vector<VAL>> temp = {lvl, {}};
    tree.push_back(temp);
  }
  tree[lvl].second.push_back(value);
  if(node->m_lower)
  {
    tree_helper(node->m_lower, lvl + 1, tree);
  }
  else{
    if (tree.size() < lvl + 2)
  {
    std::pair<int, std::vector<VAL>> temp = {lvl+1, {}};
    tree.push_back(temp);
  }
    tree[lvl+1].second.push_back(0);
  }
  if(node->m_higher)
  {
    tree_helper(node->m_higher, lvl + 1, tree);
  }
  else{
    if (tree.size() < lvl + 2)
  {
    std::pair<int, std::vector<VAL>> temp = {lvl+1, {}};
    tree.push_back(temp);
  }
    tree[lvl+1].second.push_back(0);
  }
}
