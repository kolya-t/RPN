#include "rpn.h"
#include <iostream>
#include <math.h>
#include <QStringList>
#include <QMap>
#include <QMultiMap>
#include <QStack>
#include <QQueue>
#include <QRegExp>

using namespace std;


// преобразование инфиксной записи в обратную польскую (постфиксную)
QString RPN::infixToPostfix(const QString& expr) {
    QStringList symbList = expr.split(" ");
    QStack<QString> stack;
    QStringList out;

    foreach (QString symbol, symbList) {
        // если текущий символ - ")"
        if (symbol == ")") {
            // то выталкиваем из стека все операции до "("
            while (stack.top() != "(") {
                out.append(stack.pop());
            }
            stack.pop(); // удаляем из стека "("
        }

        // если текущий символ - операнд
        if (isVariable(symbol) || isConstant(symbol)) {
            // то переписываем в выходную строку
            out.append(symbol);
        }

        // если текущий символ - "("
        if (symbol == "(") {
            // то заталкиваем ее в стек
            stack.push(symbol);
        }

        // если текущий символ - операция
        if (isOperation(symbol)) {
            // и если стек пуст
            if (stack.empty()) {
                // то записываем операцию в стек
                stack.push(symbol);
            }
            // и если приоритет текущей операции выше
            // приоритета операции на вершине стека
            else if (getPriority(symbol) > getPriority(stack.top())) {
                // тогда заталкиваем поступившую операцию в стек
                stack.push(symbol);
            }
            // если приоритет операции меньше
            else {
                // тогда переписываем в выходную строку все операции
                // из стека с большим или равным приоритетом
                while (!stack.empty() && getPriority(stack.top()) >= getPriority(symbol)) {
                    out.append(stack.pop());
                }
                // записываем в стек поступившую операцию
                stack.push(symbol);
            }
        }
    }

    // после рассмотрения всего выражения переписываем
    // операции из стека в выходную строку
    while (!stack.empty()) {
        out.append(stack.pop());
    }

    return out.join(" ");
}

// вычисление выражения в обратной польской записи (постфиксной)
double RPN::calculatePostfix(const QString& expr) {
    QStringList symbList = expr.split(" ");
    QStack<double> stack;
    // операнды и результат промежуточной операции
    double op1, op2, res;
    // словарь, хранящий названия и значения переменных
    QMap<QString, double> variables;

    foreach (QString symbol, symbList) {
        // если символ - переменная
        if (isVariable(symbol)) {
            double value;
            // искать значение переменной в словаре
            if (variables.find(symbol) != variables.end()) {
                value = variables.value(symbol);
            }
            // если не найдено - ввести
            else {
                value = inputVariableValue(symbol);
                variables.insert(symbol, value);
            }
            // запушим значение переменной в стек
            stack.push(value);
        }

        // если символ - число
        else if (isConstant(symbol)) {
            // запушить в стек
            stack.push(symbol.toDouble());
        }

        // если символ - операция
        else if (isOperation(symbol)) {
            op2 = stack.pop();
            op1 = stack.pop();
            if      (isPlus(symbol))     {res = op1 + op2;}
            else if (isMinus(symbol))    {res = op1 - op2;}
            else if (isMultiply(symbol)) {res = op1 * op2;}
            else if (isDivision(symbol)) {res = op1 / op2;}
            else if (isPower(symbol))    {res = pow(op1, op2);}
            stack.push(res);
        }
    }

    return stack.top();
}

// восстановление выражения из обратной польской записи в инфиксную
QString RPN::postfixToInfix(const QString& expr) {
    QStringList symbList = expr.split(" ");
    QStack<QString> stack;
    QMultiMap<QString, QString> operands; // все операнды
    QString op1, op2; // текущие два операнда
    QString temp;

    foreach (QString symbol, symbList) {
        // если текущий символ - переменная или число
        if (isVariable(symbol) || isConstant(symbol)) {
            stack.push(symbol);
        }
        // если это операция
        else {
            op2 = stack.pop();
            op1 = stack.pop();

            //
            int op1Priority = getPriority(operands.key(op1));
            if (op1Priority < getPriority(symbol)) {
                op1 = "( " + op1 + " )";
            }

            int op2Priority = getPriority(operands.key(op2));
            if (op2Priority < getPriority(symbol)) {
                op2 = "( " + op2 + " )";
            }

            temp = op1 + " " + symbol + " " + op2;
            operands.insert(symbol, temp);

            stack.push(temp);
        }
    }

    return stack.top();
}

QString RPN::postfixToInfix2(const QString& expr) {
//    QStringList symbList = expr.split(" ");
    QQueue<QString> queue;
    queue.fromStdList(expr.split(" ").toStdList());
    QStack<QString> stack;
    QMultiMap<QString, QString> operands; // все операнды
    QString op1, op2; // текущие два операнда
    QString temp;

    foreach (QString symbol, queue) {
        // если текущий символ - переменная или число
        if (isVariable(symbol) || isConstant(symbol)) {
            stack.push(symbol);
        }
        // если это операция
        else {
            op2 = stack.pop();
            op1 = stack.pop();

            //
            int op1Priority = getPriority(operands.key(op1));
            if (op1Priority < getPriority(symbol)) {
                op1 = "( " + op1 + " )";
            }

            int op2Priority = getPriority(operands.key(op2));
            if (op2Priority < getPriority(symbol)) {
                op2 = "( " + op2 + " )";
            }

            temp = op1 + " " + symbol + " " + op2;
            operands.insert(symbol, temp);

            stack.push(temp);
        }
    }

    return stack.top();
}

// удаление лишних скобок из выражения
QString RPN::removeBrackets(const QString& expr) {
    return postfixToInfix2(infixToPostfix(expr));
}

// ввод значения переменной
double RPN::inputVariableValue(const QString& varName) {
    double varValue;
    cout << varName.toStdString() << " = ";
    cin  >> varValue;
    return varValue;
}

// вычисление выражения в инфиксной записи
double RPN::calculate(const QString& expr) {
    return calculatePostfix(infixToPostfix(expr));
}

// является ли символ операцией
bool RPN::isOperation(const QString& s) {
    return isPlus(s)     ||
           isMinus(s)    ||
           isMultiply(s) ||
           isDivision(s) ||
           isPower(s);
}

// является ли символ операцией сложения
bool RPN::isPlus(const QString& op) {
    return op == "+";
}

// является ли символ операцией вычитания
bool RPN::isMinus(const QString& op) {
    return op == "-";
}

// является ли символ операцией умножения
bool RPN::isMultiply(const QString& op) {
    return op == "*";
}

// является ли символ операцией деления
bool RPN::isDivision(const QString& op) {
    return op == "/";
}

// является ли символ операцией возведения в степень
bool RPN::isPower(const QString& op) {
    return op == "**";
}

// является ли символ переменной
bool RPN::isVariable(const QString& s) {
    return s[0].isLetter();
}

// является ли символ числом
bool RPN::isConstant(const QString& s) {
    return s[0].isDigit();
}

// получить приоритет операции
int RPN::getPriority(const QString& operation) {
    int priority = 5;

    if (operation == "(") {
        priority = 0;
    } else if (operation == ")") {
        priority = 1;
    } else if (operation == "+" || operation == "-") {
        priority = 2;
    } else if (operation == "*" || operation == "/") {
        priority = 3;
    } else if (operation == "**") {
        priority = 4;
    }

    return priority;
}


