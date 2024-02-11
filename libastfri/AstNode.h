#include <string>

namespace libastrfi
{
    enum class AstNodeType
    {
        Expression,
        Constant
    };

    class AstNode
    {
    private:
        AstNodeType type;
        std::string value;
        AstNode *left;
        AstNode *right;

    public:
        AstNode(AstNodeType type, std::string value, AstNode *left = nullptr, AstNode *right = nullptr)
        {
            this->type = type;
            this->value = value;
            this->left = left;
            this->right = right;
        }
        AstNodeType getType()
        {
            return this->type;
        }
        std::string getValue()
        {
            return this->value;
        }
        AstNode *getLeft()
        {
            return this->left;
        }
        AstNode *getRight()
        {
            return this->right;
        }
    };

} // namespace libastrfi
