#include "tree.h"
#include "iostream"
#include <sstream>

int tree::getHeight(tree_node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int leftHeight = getHeight(node->left.get());
    int rightHeight = getHeight(node->right.get());
    return std::max(leftHeight, rightHeight) + 1;
}

int tree::getWidth(tree_node *node, int level)
{
    if (node == nullptr)
    {
        return 0;
    }
    if (level == 1)
    {
        return 1;
    }
    int leftWidth = getWidth(node->left.get(), level - 1);
    int rightWidth = getWidth(node->right.get(), level - 1);
    return leftWidth + rightWidth;
}
  
int tree::getMaxWidth(tree_node *node)
{
    int height = getHeight(node);
    int maxWidth = 0;
    for (int level = 1; level <= height; level++)
    {
        int width = getWidth(node, level);
        if (width > maxWidth)
        {
            maxWidth = width;
        }
    }
    return maxWidth;
}

std::string tree::printLevel(tree_node *node, int level, int maxWidth, int height)
{
    static int maxheight = height;
    std::stringstream out;
    if (node == nullptr)
    {
        int spaces = maxWidth / (level * 2);
        for (int i = 0; i < spaces; i++)
        {
            out << "  ";
        }
        out << "  ";
        return out.str();
    }
    if (level == 1)
    {
        for (int i = maxheight; i > 0; i--)
        {
            if (node->left || node->right)
            {
                out << "  ";
            }
            if (node->left) {
                if (node->left->left || node->left->right)
                {
                    out << "  ";
                }
            }
            if (node->right)
            {
                if (node->right->left || node->right->right)
                {
                    out << "  ";
                }
            }
        }

        out << node->value;
        return out.str();
    }
    if (level > 1) {
        out << printLevel(node->left.get(), level - 1, maxWidth, height);
        if (level == 2 && node->right && node->right->left) {
            out << "  ";
        }
        out << "  ";
        out << printLevel(node->right.get(), level - 1, maxWidth, height);
            
        return out.str();
    }
    else {
        return "";
    }
}

void tree::printTree(tree_node *root)
{
    int height = getHeight(root);
    int maxWidth = getMaxWidth(root);
    for (int level = 1; level <= height; level++)
    {
        std::string line = printLevel(root, level, maxWidth, height);
        std::cout << line << std::endl;
    }
}

tree_node * tree::create_node(tree_node *parent, std::unique_ptr<tree_node> &child, int val)
{
    child = std::make_unique<tree_node>();
    child->value = val;
    child->up = parent;
    return child.get();
}

tree_node * tree::insert(int val)
{
    if (!root)
    {
        return create_node(nullptr, root, val);
    }
    tree_node *current = root.get();
    while (true)
    {
        if (val < current->value)
        {
            if (!current->left)
            {
                return create_node(current, current->left, val);
            }
            current = current->left.get();
        }

        else if (val > current->value)
        {
            if (!current->right)
            {
                return create_node(current, current->right, val);
            }
            current = current->right.get();
        }

        else
        {
            return nullptr;
        }
    }
}

bool tree::remove(int val)
{
    tree_node *current = root.get();
    
    while (current)
    {
        if (val < current->value)
        {
            current = current->left.get();
        }

        else if (val > current->value)
        {
            current = current->right.get();
        }

        else
        {
            if (current->left && current->right)
            {
                tree_node *descendant = current->right.get();

                while (descendant->left)
                {
                    descendant = descendant->left.get();
                }

                current->value = descendant->value;
                current = descendant;
            }

            if (current->left)
            {
                current->left->up = current->up;

                if (current == root.get())
                {
                    root = std::move(current->left);
                }

                else if (current->up->left.get() == current)
                {
                    current->up->left = std::move(current->left);
                }

                else
                {
                    current->up->right = std::move(current->left);
                }

                return true;
            }

            else if (current->right)
            {
                current->right->up = current->up;
                
                if (current == root.get())
                {
                    root = std::move(current->right);
                }

                else if (current->up->left.get() == current)
                {
                    current->up->left = std::move(current->right);
                }

                else
                {
                    current->up->right = std::move(current->right);
                }

                return true;
            }
            else
            {
                if (current == root.get())
                {
                    root.reset();
                }

                else if (current->up->left.get() == current)
                {
                    current->up->left.reset();
                }

                else
                {
                    current->up->right.reset();
                }

                return true;
            }
        }
    }
    return false;
}

//int main()
//{
//    tree tree;
//    while (true)
//    {
//        tree.printTree(tree.root.get());
//        std::cout << "Выберите действие:\n";
//        std::cout << "1 - Вставить узел\n";
//        std::cout << "2 - Удалить узел\n";
//        std::cout << "0 - Остановить выполнение программы\n";
//        int choice;
//        std::cin >> choice;
//        try
//        {
//            switch (choice)
//            {
//                case 1:
//                    std::cout << "Введите значение для вставки:\n";
//                    int value;
//                    if (!(std::cin >> value))
//                    {
//                        throw std::runtime_error("Неверный ввод. Пожалуйста, введите число типа int.");
//                    }
//                    if (!tree.insert(value))
//                    {
//                        throw std::runtime_error("Значение уже существует в дереве.");
//                    }
//                    std::cout << "Дерево:\n";
//                    tree.insert(value);
//                    break;
//                case 2:
//                    std::cout << "Введите значение для удаления:\n";
//                    int value2;
//                    if (!(std::cin >> value2))
//                    {
//                        throw std::runtime_error("Неверный ввод. Пожалуйста, введите число типа int.");
//                    }
//                    if (!tree.remove(value2))
//                    {
//                        throw std::runtime_error("Значение не найдено в дереве.");
//                    }
//                    std::cout << "Дерево:\n";
//                    tree.remove(value2);
//                    break;
//                case 0:
//                    return 0;
//                default:
//                    std::cout << "Неверный выбор, попробуйте снова.\n";
//            }
//        }
//        catch (const std::exception& e)
//        {
//            std::cerr << e.what() << '\n';
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        }
//    }
//}
// 

