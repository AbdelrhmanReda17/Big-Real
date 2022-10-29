#include "BigReal.h"

BigReal :: BigReal(double realNumber) { //Initialize from double
    string realNumberString = to_string(realNumber);
    string rawNumber,fractionNumber;
    for(int i=0; i<realNumberString.size(); i++){
        if(realNumberString[i]=='.'){
            rawNumber = realNumberString.substr(0,i);
            BigDecimalInt rawNumberFormatted(rawNumber);
            number = rawNumberFormatted;
            fractionNumber = realNumberString.substr(i+1,realNumberString.size()-rawNumber.size()-1);
            BigDecimalInt fractionNumberFormatted(fractionNumber);
            fraction = fractionNumberFormatted;
            break;
        }
    }

}

BigReal :: BigReal(string realNumber) { // Initialize from string
    string rawNumber,fractionNumber;
    for(int i=0; i<realNumber.size(); i++){
        if(realNumber[i]=='.'){
            rawNumber = realNumber.substr(0,i);
            BigDecimalInt rawNumberFormatted(rawNumber);
            number = rawNumberFormatted;
            fractionNumber = realNumber.substr(i+1,realNumber.size()-rawNumber.size()-1);
            BigDecimalInt fractionNumberFormatted(fractionNumber);
            fraction = fractionNumberFormatted;
            break;
        }
    }
}

BigReal :: BigReal(BigDecimalInt bigInteger) { // Initialize from BigDecimalInt
    number = bigInteger;
    BigDecimalInt emptyFraction("0");
    fraction = emptyFraction;
}

BigReal :: BigReal(const BigReal& other) : number(other.number),fraction(other.fraction) {
} // Copy constructor - Deep Copy


BigReal ::BigReal(BigReal &&other){ // Move constructor
    number   = other.number;
    fraction = other.fraction;
}


BigReal& BigReal ::operator=(BigReal& other){ // Assignment operator
    number = other.number;
    fraction = other.fraction;
    return *this;
}

BigReal& BigReal ::operator=(BigReal&& other) { // Move assignment
    if(&other != this){
        number = other.number;
        fraction = other.fraction;
    }
    return *this;
}
int BigReal::Sign(){
    return number.Sign();
}
int BigReal::size(){
    return number.size()+fraction.size()+1;
}

ostream& operator << (ostream& out, BigReal num){
    if(num.number.Sign()=='-'){
        out << num.number.Sign();
        out<<num.number;
        out<<".";
        out<<num.fraction << endl;
    }
    else{
        out<<num.number;
        out<<"." ;
        out<< num.fraction << endl;
    }
    return out;
}

istream& operator >> (istream& out, BigReal& num){
    string realNumber;
    out >> realNumber;
    string rawNumber,fractionNumber;
    for(int i=0; i<realNumber.size(); i++){
        if(realNumber[i]=='.'){
            rawNumber = realNumber.substr(0,i);
            BigDecimalInt rawNumberFormatted(rawNumber);
            num.number = rawNumberFormatted ;
            fractionNumber = realNumber.substr(i+1,realNumber.size()-rawNumber.size()-1);
            BigDecimalInt fractionNumberFormatted(fractionNumber);
            num.fraction = fractionNumberFormatted;
            break;
        }
    }
    return out;
}

bool BigReal::operator< (BigReal anotherReal){
    if(number<anotherReal.number){
        return true;
    }
    else if(number==anotherReal.number){
        if (fraction.size()!=anotherReal.fraction.size()){
            int diff= abs(fraction.size()-anotherReal.fraction.size());
            string modified;
            if (fraction.size()>anotherReal.fraction.size()) {
                string modified = anotherReal.fraction.getNumber();
                for(int i=0;i<diff;i++){
                    modified=modified+'0';
                }
                BigDecimalInt container(modified);
                if (fraction<container){
                    return true;
                }else{
                    return false;
                }
            }else{
                string modified=fraction.getNumber();
                for(int i=0;i<diff;i++){
                    modified=modified+'0';
                }
                BigDecimalInt container(modified);
                if (anotherReal.fraction>container){
                    return true;
                }else{
                    return false;
                }
            }

        }else{
            if (fraction<anotherReal.fraction){
                return true;
            }
                return false;
        }
    }
    return false;
}
bool BigReal::operator> (BigReal anotherReal){
    if(number>anotherReal.number){
        return true;
    }
    else if(number==anotherReal.number){
        if (fraction.size()!=anotherReal.fraction.size()){
            int diff= abs(fraction.size()-anotherReal.fraction.size());
            string modified;
            if (fraction.size()>anotherReal.fraction.size()) {
                string modified = anotherReal.fraction.getNumber();
                for(int i=0;i<diff;i++){
                    modified=modified+'0';
                }
                BigDecimalInt container(modified);
                if (fraction>container) {
                    return true;
                }
                return false;
            }else{
                string modified=fraction.getNumber();
                for(int i=0;i<diff;i++){
                    modified=modified+'0';
                }
                BigDecimalInt container(modified);
                if (anotherReal.fraction<container){
                    return true;
                }
                return false;
            }

        }else{
            if (fraction>anotherReal.fraction){
                return true;
            }
            return false;
        }
    }
    return false;

}
bool BigReal::operator== (BigReal anotherReal){
    if (number==anotherReal.number){
        if(fraction.size()!=anotherReal.fraction.size()){
            return false;
        }else{
            if(fraction==anotherReal.fraction){
                return true;
            }
            return false;
        }
    }
    return false;
}


BigReal BigReal::operator+ (BigReal& other)
{
    if (number.getSign() == other.number.getSign()) {
        BigReal result;
        BigDecimalInt frac1 , frac2 , first , second;

        string firstfrac = fraction.getNumber();
        string secondfrac = other.fraction.getNumber();

        string firstnum = number.getNumber();
        string secondnum = other.number.getNumber();

        first.setNumberValue(firstnum);
        first.setSign(number.getSign());

        second.setNumberValue(secondnum);
        second.setSign(other.number.getSign());

        frac1.setSign('+');
        frac2.setSign('+');
        while (secondfrac.size() > firstfrac.size()) firstfrac += '0';
        while (secondfrac.size() < firstfrac.size()) secondfrac += '0';

        int size = firstfrac.size();

        frac1.setNumberValue(firstfrac);
        frac2.setNumberValue(secondfrac);

        BigDecimalInt sumf(frac1 + frac2);
        if (size != sumf.getNumber().size()) {
            string x = sumf.getNumber();
            x = x.erase(0, 1);
            sumf.setNumberValue(x);
            BigDecimalInt carry("1");
            BigDecimalInt xeq = first + carry;
            first.setNumberValue(xeq.getNumber());
        }
        result.fraction = sumf;
        BigDecimalInt ss = first + second;
        result.number = ss;
        result.number.setSign(ss.getSign());
        return result;
    }
    else
    {
        BigReal temp;
        if (number.getSign() == '-')
        {
            temp = *this;
            temp.number.setSign('+');
            return other - temp;
        }
        else
        {
            temp = other;
            temp.number.setSign('+');
            return *this - temp;
        }
    }
}


BigReal BigReal::operator- (BigReal& other)
{
    if (number.getSign() == other.number.getSign()) {
        BigDecimalInt first, second;
        string firstfrac = fraction.getNumber();
        string secondfrac = other.fraction.getNumber();

        while (secondfrac.size() > firstfrac.size()) firstfrac+= '0';
        while (secondfrac.size() < firstfrac.size()) secondfrac+='0';
        int size = firstfrac.size();

        string firstnum = number.getNumber() + firstfrac;
        string secondnum = other.number.getNumber() + secondfrac;

        first.setNumberValue(firstnum);
        first.setSign(number.getSign());
        second.setNumberValue(secondnum);
        second.setSign(other.number.getSign());
        BigDecimalInt sum = first - second;

        string str = sum.getNumber();
        while (str.size()<=size) str = '0' + str;
        str.insert(str.size()-size, ".");
        BigReal result = str;
        result.number.setSign(sum.getSign());
        return result;
    }else
    {
        BigReal temp;
        if (number.getSign() == '-')
        {
            temp = other;
            temp.number.setSign('-');
            return *this + temp;
        }
        else
        {
            temp = other;
            temp.number.setSign('+');
            return temp + *this;
        }
    }
}

