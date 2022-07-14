#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include <algorithm>

using namespace std;

#define MAXSIZE 3010

class BigInt {
    string num;
    bool sign;
public:
    BigInt();
    BigInt(string x);
    BigInt(string x, bool sig);
    BigInt operator + (BigInt y);
    BigInt operator - (BigInt y);
    BigInt operator * (BigInt y);
    bool operator > (BigInt b);
    bool operator < (BigInt b);
    bool operator == (BigInt b);
    bool operator == (string b);
    const string& getNum();
    const bool& getSign();
    void setNum(string x);
    void setSign(bool x);
    operator string();
    BigInt abso();
    string addition(string a, string b);
    string subtraction(string a, string b);
    string multiply(string a, string b);
    bool lesser(BigInt a, BigInt b);
    bool greater(BigInt a, BigInt b);
    bool equals(BigInt a, BigInt b);
    bool equals(BigInt a, string b);
    string to_String(long long x);
    string factorial(string n);
    unsigned long long GCD(unsigned long long a, unsigned long long b);
    string GCD(string a, string b);
    string modulus(string a, string b);
    string exponentiate(string n, unsigned long long int x);
    friend std::ostream& operator<<(std::ostream& out, BigInt a);
};

BigInt::BigInt() {
    num = "0";
    sign = false;
}

BigInt::BigInt(string x) {
    if (isdigit(x[0])) {
        setNum(x);
        sign = false;
    }
    else {
        setNum(x.substr(1));
        if (x[0] == '+') {
            sign = false;
        }
        else {
            sign = true;
        }
    }
}

BigInt::BigInt(string x, bool sig) {
    setNum(x);
    setSign(sig);
}

bool BigInt::operator == (BigInt b) {
    return equals((*this), b);
}

//bool BigInt::operator == (string b) {
//    return equals((*this.getNum()), b);
//}

const string& BigInt::getNum() {
    return num;
}

const bool& BigInt::getSign() {
    return sign;
}

void BigInt::setSign(bool x) {
    sign = x;
}

void BigInt::setNum(string x) {
    num = x;
}

BigInt BigInt::abso() {
    return BigInt(getNum());
}

bool BigInt::operator > (BigInt b) {
    return greater((*this), b);
}

bool BigInt::operator < (BigInt b) {
    return lesser((*this), b);
}


BigInt BigInt::operator + (BigInt b) {
    BigInt sum;
    if (getSign() == b.getSign()) {
        sum.setNum(addition(getNum(), b.getNum()));
        sum.setSign(getSign());
    }
    else {
        if (abso() > b.abso()) {
            sum.setNum(subtraction(getNum(), b.getNum()));
            sum.setSign(getSign());
        }
        else {
            sum.setNum(subtraction(b.getNum(), getNum()));
            sum.setSign(b.getSign());
        }
    }

    return sum;

}

BigInt BigInt::operator * (BigInt b) {
    BigInt product;

    product.setNum(multiply(getNum(), b.getNum()));
    if (getSign() == b.getSign()) {
        product.setSign(false);
    }
    else {
        product.setSign(true);
    }

    return product;
}

BigInt BigInt::operator - (BigInt b) {
    bool newSign = !b.getSign();
    b.setSign(newSign);
    return (*this) + b;
}

bool BigInt::equals(BigInt a, BigInt b) {
    bool firstCheck = a.getNum() == b.getNum();
    bool secondCheck = a.getSign() == b.getSign();
    return firstCheck and secondCheck;
}

bool BigInt::equals(BigInt a, string b) {
    bool firstCheck = a.getNum() == b;
    return firstCheck;
}

bool BigInt::greater(BigInt a, BigInt b) {
    bool sign1 = a.getSign();
    bool sign2 = b.getSign();

    int num1length = a.getNum().length();
    int num2length = b.getNum().length();

    if (sign1 && !sign2)
        return false;

    else if (!sign1 && sign2)
        return true;

    else if (!sign1) {
        if (num1length < num2length)
            return false;
        if (num1length > num2length)
            return true;
        return a.getNum() > b.getNum();
    }
    else {
        if (num1length > num2length)
            return false;
        if (num1length < num2length)
            return true;
        return a.getNum().compare(b.getNum()) < 0;
    }
}

bool BigInt::lesser(BigInt a, BigInt b) {
    bool sign1 = a.getSign();
    bool sign2 = b.getSign();

    int num1length = a.getNum().length();
    int num2length = b.getNum().length();

    if (sign1 && !sign2)
        return true;

    else if (!sign1 && sign2)
        return false;

    else if (!sign1) {
        if (num1length < num2length)
            return true;
        if (num1length > num2length)
            return false;
        return a.getNum() > b.getNum();
    }
    else {
        if (num1length > num2length)
            return true;
        if (num1length < num2length)
            return false;
        return a.getNum().compare(b.getNum()) > 0;
    }
}


string BigInt::addition(string a, string b) {

    string sum;
    if (a.length() > b.length()) {
        sum = a;
    }
    else {
        sum = b;
    }

    char carry = '0';
    int lengthDiff = abs((int)(a.length() - b.length()));

    if (a.length() < b.length()) {
        a.insert(0, lengthDiff, '0');
    }
    else {
        b.insert(0, lengthDiff, '0');
    }

    for (int i = a.length() - 1; i >= 0; i--) {
        char currSum = ((a[i] - '0') + (b[i] - '0') + (carry - '0')) + '0';
        if (i > 0) {
            if (currSum > '9') {
                currSum -= 10;
                carry = '1';
            }
            else {
                carry = '0';
            }
        }

        sum[i] = currSum;
    }

    char currSum = sum[0];
    if (currSum > '9') {
        currSum -= 10;
        sum[0] = currSum;
        sum.insert(0, 1, '1');
    }

    return sum;

}


string BigInt::subtraction(string a, string b) {
    string diff;

    if (a.length() > b.length()) {
        diff = a;
    }
    else {
        diff = b;
    }

    int lengthDiff = abs((int)(a.length() - b.length()));

    if (a.length() < b.length()) {
        a.insert(0, lengthDiff, '0');
    }
    else {
        b.insert(0, lengthDiff, '0');
    }

    for (int i = a.length() - 1; i >= 0; i--) {
        if (b[i] > a[i]) {
            a[i] += 10;
            a[i - 1] = a[i - 1] - 1;
        }
        auto difference = ((a[i] - '0') - (b[i] - '0')) + '0';
        diff[i] = difference;
    }

    while (diff[0] == '0' && diff.length() > 1) // erase leading zeros
        diff.erase(0, 1);

    return diff;
}


string BigInt::multiply(string s1, string s2) {

    if (s1.length() > s2.length()) {
        s1.swap(s2);
    }

    if (s1.length() == 0 || s2.length() == 0) {
        return "0";
    }

    string result = "0";

    int index1 = 0;
    for (int i = s1.length() - 1; i >= 0; i--) {

        int carry = 0;
        int num1 = s1[i] - '0';
        string tempString = s2;

        //int index2 = 0;
        for (int j = tempString.length() - 1; j >= 0; j--) {
            int num2 = tempString[j] - '0';
            tempString[j] = (num1 * num2) + carry;

            if (tempString[j] > 9) {
                carry = (tempString[j] / 10);
                tempString[j] = tempString[j] - (carry * 10);
            }
            else {
                carry = 0;
            }

            tempString[j] = tempString[j] + '0';
        }

        if (carry > 0)
            tempString.insert(0, 1, (carry + '0'));

        tempString.append((s1.length() - i - 1), '0');

        result = addition(result, tempString);
    }

    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    while (result[0] == '0' && result.length() != 1)
        result.erase(0, 1);

    return result;
}

string BigInt::factorial(string n) {
    if (equals(n, "0")) {
        return "1";
    }
    //cout << n << endl;
    return multiply(n, factorial(subtraction(n, "1")));
    //cout << n << endl;
}


bool stringCompare(string a, string b) {

    if (a.length() > b.length()) {
        return true;
    }

    if (b.length() > a.length()) {
        return false;
    }

    for (int i = 0; i < a.length(); ++i) {
        if ((a[i] - '0') < (b[i] - '0'))
        {
            return false;
        }
        else if ((a[i] - '0') > (b[i] - '0')) {
            return true;
        }

    }

    return "";

}

string  BigInt::modulus(string a, string b) {
    // cout << a << endl;
    // cout << b << endl;
    if(a == "0"){
        return b;
    }
    if(b == "0"){
        return a;
    }

    string result = "";
    string dividend = "";
    string divisor = "";

    if (stringCompare(dividend, divisor)) {
        dividend = a;
        divisor = b;
    }
    else {
        dividend = b;
        divisor = a;
    }

    while (stringCompare(dividend, divisor) || dividend == divisor) {
        //cout << dividend << endl;
        int divLength = divisor.length();
        //cout << divLength << " " << dividend.length() << endl;

        if (divLength == dividend.length()) {

            if (!stringCompare(dividend, divisor)) {
                result = dividend;
                return result;
            }

            while (stringCompare(dividend, divisor)) {
                dividend = subtraction(dividend, divisor);
                //cout << subDividend << endl;
            }

            result = dividend;
            return result;
        }

        string subDividend = dividend.substr(0, divLength + 1);
        //cout << subDividend << endl;

        while (stringCompare(subDividend, divisor)) {
            //cout << "asfajksjfka" << endl;
            subDividend = subtraction(subDividend, divisor);
            //cout << subDividend << endl;

            int i;
            for (i = 0; i < subDividend.length(); i++) {
                if (subDividend[i] == '0') {
                    continue;
                }
                else {
                    break;
                }
            }
            if (i == subDividend.length()) {
                subDividend = "0";
            }
            else {
                subDividend = subDividend.substr(i);
            }

            //cout << subDividend << endl;
        }

        string remainderDivident = dividend.substr(divLength + 1);
        //cout << remainderDivident << endl;
        subDividend = subDividend + remainderDivident;
        //cout << subDividend << endl;
        dividend = subDividend;
        //cout << dividend << endl;

        // int i;
        // for (i = 0; i < dividend.length(); i++) {
        //     if (dividend[i] == '0') {
        //         continue;
        //     }
        // }
        // if (i == dividend.length()) {
        //     dividend = "0";
        // }
        // else {
        //     dividend = dividend.substr(i);
        // }

    }

    return dividend;

}

string  BigInt::GCD(string a, string b) {

    if (b == "0") {
        return a;
    }

    return GCD(b, modulus(a, b));
}


unsigned long long gcd(unsigned long long x, unsigned long long y)
{
    if (!x)
        return y;
    return gcd(y % x, x);
}


unsigned long long gcdNo(unsigned long long x, string y)
{
    // unsigned long long num = reduceB(a, b);
    //cout << x << endl;
    unsigned long long num = 0;
    for (int i = 0; i < y.size(); i++)
        num = (num * 10 + y[i] - '0') % x;

    return gcd(x, num);
}

template <class T>
inline std::string to_string(const T & t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

string BigInt::exponentiate(string n, unsigned long long x) {
    unsigned long long y;
    string result = "1";
    // for (y = 1; y < x; y++) {
    //     //auto z = to_string(y);
    //     //cout << result << endl;
    //     result = multiply(result, n);
    // }
    y = x;
    while (y > 0)
    {
        if (y & 1)
            result = multiply(result, n);

        y = y >> 1;
        n = multiply(n, n);
    }

    return result;
}


std::ostream& operator <<(std::ostream & out, BigInt a)
{
    for (unsigned int i = 0; i < a.getNum().length(); i++) {
        out << a.getNum()[i] << "";
    }
    return out;
}


int operand_priority(char c)
{
    if (c == 'x')
        return 1;
    else
        return 0;
}

string expressionCalculator(string expression) {

    string tokenArray[expression.size()];
    for (int i = 0; i < expression.size(); i++)
        tokenArray[i] = "";


    char tokens[expression.length()];
    int j = 0;
    int k = -1;

    for (int i = 0; i < expression.size(); i++) {
        char c = expression[i];
        //cout << c << endl;
        if (isdigit(c)) {
            tokenArray[j] += c;
        }

        else {
            j++;
            //cout << j << endl;
            if (k == -1) {
                k++;
                tokens[k] = c;
            }
            else if (operand_priority(tokens[k]) < operand_priority(c)) {
                k++;
                tokens[k] = c;
            }
            else {
                while (k > -1 and operand_priority(tokens[k]) >= operand_priority(c)) {
                    tokenArray[j] += tokens[k];
                    j++; k--;
                }
                k++;
                tokens[k] = c;
            }
        }
    }

    if (k != -1)
    {
        j += 1;
        while (k != -1) {
            tokenArray[j] += tokens[k];
            j += 1; k -= 1;
        }
    }

    // for (int i = 0; i <= j; i++)
    // {
    //     cout << "***" << endl;
    //     cout << tokenArray[i] << endl;
    // }

    string tokens2[j + 1];
    k = -1;
    BigInt x;
    for (int i = 0; i <= j; i++)
    {
        //cout << "***" << endl;
        if (tokenArray[i] == "x")
        {
            string num1 = tokens2[k - 1];
            string num2 = tokens2[k];
            string result = x.multiply(num1, num2);
            k--;
            tokens2[k] = result;

        }
        else if (tokenArray[i] == "+")
        {
            string num1 = tokens2[k - 1];
            string num2 = tokens2[k];
            string result = x.addition(num1, num2);
            k--;
            tokens2[k] = result;

        }
        else if (tokenArray[i] == "-")
        {
            string num1 = tokens2[k - 1];
            string num2 = tokens2[k];
            string result = x.subtraction(num1, num2);
            k--;
            tokens2[k] = result;
        }
        else
        {
            tokens2[++k] = tokenArray[i];
        }
    }
    auto answer = tokens2[0];
    return answer;
}


int main() {

    int n;
    // cout << "Choose an operation: " << endl;
    // cout << "1) Exponentation " << endl;
    // cout << "2) GCD " << endl;
    // cout << "3) Factorial " << endl;
    // cout << "4) Calculator " << endl;
    cin >> n;

    if (n == 1) {
        string a;
        unsigned long long b;

        cin >> a >> b;

        BigInt x;

        auto result = x.exponentiate(a, b);
        cout << result << endl;

    }

    else if (n == 2) {
        string a;
        string b;
        cin >> a >> b;

        BigInt x;


            //cout << endl;
            //cout << "GRAB SOME SNACKS!!" << endl;
        auto result = x.GCD(a, b);
        cout << result << endl;

    }

    else if (n == 3) {
        string a;
        cin >> a;

        BigInt x;
        auto result = x.factorial(a);
        cout << result << endl;
    }

    else if (n == 4) {
        string a;
        cin >> a;

        auto result = expressionCalculator(a);
        cout << result << endl;
    }

    else {
        cout << "INVALID" << endl;
    }



    // BigInt a("500");
    // BigInt b("501");
    // BigInt c("15467985611234679845178946510379845612546541238708");
    // BigInt d("67467985611412679845878946783212365212043542388978");
    // BigInt x;
    // //auto result = x.factorial("219");
    // // auto result = x.exponentiate(a.getNum(), 10);
    // //cout << b - a  << endl;
    // auto result = x.GCD("127481279471294712929847892", "12");
    // cout << result << endl;
    // auto result = x.subtraction("20", "3");
    // cout << result << endl;

    // char f[] = "48";
    // auto result = gcdLarge(6, f);
    // cout << result << endl;
    // //cout << result << endl;
    // //cout << c * d << endl;
    // //cout << a - b << endl;

    // //string y = "444";
    // //string z = "56";
    // //cout << stringCompare(y, z) << endl;

    return 0;
}