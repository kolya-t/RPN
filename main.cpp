#include <QCoreApplication>
#include <iostream>
#include <string>
#include "Queue.h"
#include "rpn.h"
#include <QDebug>

using namespace std;

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QVector<QString> expressions;
//    expressions.append("3 + ( 4 * 2 ) / ( 1 - 5 ) ** 2");
//    expressions.append("( ( a + b ) * ( c + d ) ) - e");
//    expressions.append("( 12 * a ) * ( var2 - 24 ) - var2");
    expressions.append("( ( a * b ) + ( b * b ) )");
//    expressions.append("( ( c * ( a + ( e - b ) * d ) ) )");
//    expressions.append("( a + b ) * c");
//    expressions.append("( a * b ) * ( a + b ) * ( a + b ) / ( a * b )");
    expressions.append("( a + b ) * ( c + d )");

    foreach (QString infix, expressions) {
        QString postfix = RPN::infixToPostfix(infix);
        QString infix2  = RPN::postfixToInfix(postfix);
//        double  result  = RPN::calculatePostfix(postfix);
        double result = 0;

        cout << "Infix:            " << infix.toStdString()   << endl
             << "Postfix:          " << postfix.toStdString() << endl
             << "Without brackets: " << infix2.toStdString()  << endl
             << "Result:           " << result                << endl;
        cout << endl;
    }

    return app.exec();
}
