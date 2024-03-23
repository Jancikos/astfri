#pragma once

#include <string>
#include <vector>

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>

namespace libastfri::structures {
/**
 * @brief pre reprazentaciu celeho vstupneho bloku kodu
 *
 */
struct TranslationUnit {
    std::vector<FunctionDefinition *> functions;
};

// "riadok" v kode
struct Statement {
    int rnd; // TODO vymazat - teraz IBA PRE TRAPNY DEBUGGING

    Statement() {
        static int rnd = 0;
        this->rnd = rnd++;
    }

    std::string toString() const {
        return "Statement " + std::to_string(rnd) + "\n";
    }
};

struct CompoundStatement : Statement {
    std::vector<Statement *> statements;

    std::string toString() const {
        std::string result;
        for (const auto &statement : statements) {
            result += statement->toString();
        }
        return result;
    }
};

struct DeclarationStatement : Statement {
    Declaration *declaration;

    std::string toString() const {
        // Implement the toString() function for DeclarationStatement
        std::string result = "DeclarationStatement: ";
        // result += variable->toString();
        return result;
    }
};

struct DeclarationAndAssigmentStatement : DeclarationStatement {
    Expression *exp;

    std::string toString() const {
        // Implement the toString() function for
        // DeclarationAndAssigmentStatement
        std::string result = "DeclarationAndAssigmentStatement: ";
        // result += variable->toString();
        result += " = ";
        // result += exp->toString();
        return result;
    }
};

struct ReturnStatement : Statement {
    Expression *value;

    std::string toString() const {
        // Implement the toString() function for ReturnStatement
        std::string result = "ReturnStatement: ";
        // result += value->toString();
        return result;
    }
};

struct ExpressionStatement : Statement {
    Expression *expression;

    std::string toString() const {
        // Implement the toString() function for ExpressionStatement
        std::string result = "ExpressionStatement: ";
        // result += expression->toString();
        return result;
    }
};

// Conditional statement
struct ConditionalStatement : Statement {
    Expression *condition;

    std::string toString() const {
        // Implement the toString() function for ConditionalStatement
        std::string result = "ConditionalStatement: ";
        // result += condition->toString();
        return result;
    }
};

struct IfStatement : ConditionalStatement {
    CompoundStatement *thenBody;
    CompoundStatement *elseBody;

    std::string toString() const {
        // Implement the toString() function for IfStatement
        std::string result = "IfStatement: ";
        result += "Condition: ";
        // result += condition->toString();
        result += "\nThen Body: ";
        result += thenBody->toString();
        result += "\nElse Body: ";
        result += elseBody->toString();
        return result;
    }
};

// Loop statement
struct LoopStatement : Statement {
    Expression *condition;
    CompoundStatement *body;

    std::string toString() const {
        // Implement the toString() function for LoopStatement
        std::string result = "LoopStatement: ";
        result += "Condition: ";
        // result += condition->toString();
        result += "\nBody: ";
        result += body->toString();
        return result;
    }
};

struct WhileLoopStatement : LoopStatement {
    std::string toString() const {
        // Implement the toString() function for WhileLoopStatement
        std::string result = "WhileLoopStatement: ";
        result += "Condition: ";
        // result += condition->toString();
        result += "\nBody: ";
        result += body->toString();
        return result;
    }
};

struct DoWhileLoopStatement : LoopStatement {
    std::string toString() const {
        // Implement the toString() function for DoWhileLoopStatement
        std::string result = "DoWhileLoopStatement: ";
        result += "Condition: ";
        // result += condition->toString();
        result += "\nBody: ";
        result += body->toString();
        return result;
    }
};

struct ForLoopStatement : LoopStatement {
    ExpressionStatement *init;
    ExpressionStatement *step;

    std::string toString() const {
        // Implement the toString() function for ForLoopStatement
        std::string result = "ForLoopStatement: ";
        result += "Init: ";
        result += init->toString();
        result += "\nCondition: ";
        // result += condition->toString();
        result += "\nStep: ";
        result += step->toString();
        result += "\nBody: ";
        result += body->toString();
        return result;
    }
};

struct UnknownStatement : Statement {
    std::string message;

    UnknownStatement(std::string message) : message(message) {}
};
} // namespace libastfri::structures