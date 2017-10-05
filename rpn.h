#ifndef RPN_H
#define RPN_H

#include <QString>
#include <QVector>


class RPN {
public:
    static double  calculate         (const QString&);
    static QString removeBrackets    (const QString&);
public: // сделать private
    static QString infixToPostfix    (const QString&);
    static double  calculatePostfix  (const QString&);
    static QString postfixToInfix    (const QString&);
    static QString postfixToInfix2   (const QString&);
private:
    static bool    isOperation       (const QString&);
    static bool    isPlus            (const QString&);
    static bool    isMinus           (const QString&);
    static bool    isMultiply        (const QString&);
    static bool    isDivision        (const QString&);
    static bool    isPower           (const QString&);
    static bool    isVariable        (const QString&);
    static bool    isConstant        (const QString&);
    static int     getPriority       (const QString&);
    static double  inputVariableValue(const QString&);
};

#endif
