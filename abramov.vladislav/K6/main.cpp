#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>

template< class T >
struct BiTree
{
  T data;
  BiTree< T > *left;
  BiTree< T > *right;
  BiTree< T > *parent;
};

template< class T >
BiTree< T > *rotate_right(BiTree< T > *root)
{
  BiTree< T > *new_root = nullptr;
  BiTree< T > *new_son = nullptr;
  if (!root->left)
  {
    throw std::logic_error("Can not rotate\n");
  }
  else
  {
    new_root = root->left;
    if (new_root->right)
    {
      new_son = new_root->right;
    }
  }
  if (root->parent->left == root)
  {
    root->parent->left = new_root;
  }
  else
  {
    root->parent->right = new_root;
  }
  root->parent = new_root;
  new_root->right = root;
  root->left = new_son;
  new_son->parent = root;
  return new_root;
}

template< class T >
BiTree< T > *rotate_left(BiTree< T > *root)
{
  BiTree< T > *new_root = nullptr;
  BiTree< T > *new_son = nullptr;
  if (!root->right)
  {
    throw std::logic_error("Can not rotate\n");
  }
  else
  {
    new_root = root->right;
    if (new_root->left)
    {
      new_son = new_root->left;
    }
  }
  if (root->parent->left == root)
  {
    root->parent->left = new_root;
  }
  else
  {
    root->parent->right = new_root;
  }
  root->parent = new_root;
  new_root->left = root;
  root->right = new_son;
  new_son->parent = root;
  return new_root;
}

template< class T, class Cmp >
BiTree< T > *find(BiTree< T > *root, const T &value, Cmp cmp)
{
  if (root->data == value)
  {
    return root;
  }
  while (root)
  {
    if (root->data == value)
    {
      return root;
    }
    if (cmp(value, root->data))
    {
      root = root->left;
    }
    else
    {
      root = root->right;
    }
  }
  return nullptr;
}

template< class T, class Cmp >
void add(BiTree< T > *root, Cmp cmp, const T &value)
{
  while (root)
  {
    if (cmp(root->data, value))
    {
      if (root->left)
      {
        root = root->left;
      }
      else
      {
        root->left = new BiTree< T >{ value, nullptr, nullptr, root };
        return;
      }
    }
    else
    {
      if (root->right)
      {
        root = root->right;
      }
      else
      {
        root->right = new BiTree< T >{ value, nullptr, nullptr, root };
        return;
      }
    }
  }
}

template< class T >
void deleteTree(BiTree< T > *root)
{
  if (root)
  {
    BiTree< T > *left = root->left;
    BiTree< T > *right = root->right;
    deleteTree(left);
    deleteTree(right);
  }
  delete root;
}

int main()
{
  size_t k = 0;
  int x = 0;
  BiTree< int > *root = nullptr;
  std::cin >> k;
  if (k != 0)
  {
    std::cin >> x;
    root = new BiTree< int >{ x, nullptr, nullptr, nullptr };
    for (size_t i = 0; i < k - 1; ++i)
    {
      std::cin >> x;
      if (!std::cin)
      {
        std::cout << "<INVALID ARGUMENT>\n";
        deleteTree(root);
        return 1;
      }
      add(root, std::less< int >(), x);
    }
  }
  try
  {
    if (root)
    {
      while(std::cin)
      {
        std::string s;
        int num = 0;
        std::cin >> s >> num;
        if (!std::cin)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        BiTree< int > *new_root = find(root, num, std::less< int >());
        if (!new_root)
        {
          std::cout << "<INVALID COMMAND>\n";
          deleteTree(root);
          return 1;
        }
        if (s == "left")
        {
          rotate_left(root);
        }
        else if (s == "right")
        {
          rotate_right(root);
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
          deleteTree(root);
          return 1;
        }
      }
    }
  }
  catch (const std::exception &e)
  {
    std::cout << e.what();
    deleteTree(root);
    return 1;
  }
  deleteTree(root);
}
