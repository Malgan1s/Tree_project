#include <memory>

/**
 * @brief Структура tree_node представляет узел дерева.
 */
struct tree_node
{
    /**
    * Значение узла
    */
    int value;
    
    /**
    * Указатель на родительский узел.
    */
    tree_node *up;
    
    /**
    * Умные указатели на левый и правый потомки
    */
    std::unique_ptr<tree_node> left, right;
};

/**
 * @brief Структура tree представляет дерево
 */
struct tree
{
    /**
    * Умный указатель на корень дерева.
    */
    std::unique_ptr<tree_node> root;
    
    /**
     * @brief Функция insert вставляет новый узел.
     * @param val значение узла
     * @return Указатель на вставленный узел или nullptr, если значение уже существует в дереве.
     */
    tree_node * insert(int val);
    
    /**
     * @brief Функция remove удаляет узел со значением val из дерева.
     * @param val значение узла
     * @return Возвращает true, если удаление прошло успешно, в противном случае возвращает false.
     */
    bool remove(int val);
    
    /**
     * @brief Функция getHeight находит высоту поддерева
     * @param node - указатель на узел (корень)
     * @return Возвращает высоту поддерева.
     */
    int getHeight(tree_node *node);
    
    /**
     * @brief Функция getHeight находит высоту поддерева
     * @param node указатель на узел (корень)
     * @param level уровень ширина дерева
     * @return Возвращает ширину поддерева на уровне level
     */
    int getWidth(tree_node *node, int level);
    
    /**
     * @brief Функция getMaxWidth находит максимальную высоту поддерева
     * @param node указатель на узел (корень)
     * @return Возвращает максимальную ширину поддерева
     */
    int getMaxWidth(tree_node *node);
    
    /**
     * @brief Функция printLevel возвращает строку, содержащую значение узлов на указанном уровне level
     * @param node указатель на узел (корень)
     * @param level уровень ширина дерева
     * @param maxWidth максимальная ширина дерева
     * @param height высота дерева
     * @return Возвращает строку, содержащую значение узлов на указанном уровне
     */
    std::string printLevel(tree_node *node, int level, int maxWidth, int height);
    
    /**
     * @brief Функция printTree печатает дерево в консоль
     * @param root указатель на корень дерева
     */
    void printTree(tree_node *root);

private:
    tree_node * create_node(tree_node *parent, std::unique_ptr<tree_node> &child, int val);
};
