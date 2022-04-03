#include "stack.h"
#include <vector>

void stackTest() {
    // Stack<int> stack;
    LinkedStack<int> stack;
    for (int i = 0; i < 20; i++) {
        stack.push(i);
        cout << "size: " << stack.size() << endl;
        cout << "top: " << stack.top() << endl;
    }
    for (int i = 0; i < 20; i++) {
        cout << "size: " << stack.size() << endl;
        cout << "top: " << stack.top() << endl;
        stack.pop();
    }
}

vector<string> inffix2suffix(string expr) {
    /**
     * 中序表达式转化为逆波兰式
     * 采用两个栈: 运算符号栈, 操作数栈
     * 1. 对于数字, 直接压入操作数栈
     * 2. 操作符号: 
     *    (: 直接压入符号栈
     *    ): 输出符号栈到操作数栈, 直到遇见(
     *    运算符: 
     *      1. 符号栈顶为括号: 直接压入符号栈
     *      2. 比符号栈顶运算符优先级高: 直接压入符号栈
     *      3. 比符号栈顶运算符优先级低/相等: 符号栈输出到操作数栈
     *      4. 读取完毕, 将符号栈剩余的运算符压入操作数栈
     */
    vector<string> suffix;
    Stack<char> opts;

    int n = expr.length();
    int i = 0;
    while (i < n) {
        if (isdigit(expr[i])) {
            // 纯数字
            string number(1, expr[i++]);
            while (isdigit(expr[i]))
                number += expr[i++];
            suffix.push_back(number);
        } else if (expr[i] == '(') {
            // '('
            opts.push(expr[i++]);
        } else if (expr[i] == ')') {
            // ')'
            while (opts.top() != '(') {
                suffix.push_back(string(1, opts.top()));
                opts.pop();
            }
            opts.pop();
            i++;
        } else if (expr[i] == '+' || expr[i] == '-') {
            // '+' '-'
            while (!opts.empty() && opts.top() != '(') {
                suffix.push_back(string(1, opts.top()));
                opts.pop();
            }
            opts.push(expr[i++]);
        } else {
            // '*' '/'
            while (!opts.empty() && opts.top() != '+' && opts.top() != '-' && opts.top() != '(') {
                suffix.push_back(string(1, opts.top()));
                opts.pop();
            }
            opts.push(expr[i++]);
        }
    }
    while (!opts.empty()) {
        suffix.push_back(string(1, opts.top()));
        opts.pop();
    }

    return suffix;
}

int suffixCompute(vector<string> expr) {
    /**
     * 遇到符号, 取出数字栈的两个数字进行计算
     */ 
    Stack<string> stack;
    for (string s : expr) {
        if (s == "+") {
            int n2 = atoi(stack.top().c_str());
            stack.pop();
            int n1 = atoi(stack.top().c_str());
            stack.pop();
            stack.push(to_string(n1 + n2));
        } else if (s == "-") {
            int n2 = atoi(stack.top().c_str());
            stack.pop();
            int n1 = atoi(stack.top().c_str());
            stack.pop();
            stack.push(to_string(n1 - n2));
        } else if (s == "*") {
            int n2 = atoi(stack.top().c_str());
            stack.pop();
            int n1 = atoi(stack.top().c_str());
            stack.pop();
            stack.push(to_string(n1 * n2));
        } else if (s == "/") {
            int n2 = atoi(stack.top().c_str());
            stack.pop();
            int n1 = atoi(stack.top().c_str());
            stack.pop();
            stack.push(to_string(n1 / n2));
        } else {
            stack.push(s);
        }
    }
    return atoi(stack.top().c_str());
}

void infixTest() {
    string inputString;
    cout << "input inffix string for computing: ";
    cin >> inputString;
    cout << "inffix: " << inputString << endl;
    vector<string> exprs = inffix2suffix(inputString);
    cout << "suffix: ";
    for (string expr : exprs)
        cout << expr << ' ';
    cout << "\nresult: " << suffixCompute(exprs) << endl;
}

int main() {
    infixTest();
    return 0;
}