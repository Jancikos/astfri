#include <string>

namespace libastrfi
{
    enum class AstNodeType
    {
        Expression,
            UnaryExpression, // !
            BinaryExpression, // +, -, *, /, %
            CastingExpression, // static, dynamic, const... 
        LiteralValue, // char, string, int, bool ... 
        
        FileDefinition, // dependencies, namespace, classes, methods
            ClassDefinition, // definition (accessibility, modificators (readonly, sealed...), atributes, name, parents, ?interfaces, properties, methods), generika
                PeopertyDefinition, // accessibility, type, name, def. value, nullable
            EnumDefinition, // special type of class
            FunctionDefinition, // definition (accessibility,  atributes, name, paramters, return type, code block), generika
                ParameterDefinition, // type, name, def. value, nullable
                CodeBlock, // jednotlive riadky tela funkcie
                    LoopBlock, // condition (before/after), break, continue
                    ConditionBlock, // condition, true block, false block
                        IfBlock,
                        SwitchBlock,
                    TryCatchBlock, // try, catch, finally


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
