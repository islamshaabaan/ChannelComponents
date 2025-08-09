#include "Parameter.h"

Parameter::Parameter(QObject* parent) : QObject(parent) 
{
}

void Parameter::setName(const QString &n) 
{ 
    mName = n; 
}

QString Parameter::getName() const 
{ 
    return mName; 
}

void Parameter::setKind(const QString &k) 
{ 
    mKind = k; 
}
QString Parameter::getKind() const 
{ 
    return mKind; 
}

void Parameter::setValue(const QVariant &v) 
{
    QVariant old = mValue;
    if (old != v) 
    {
        mValue = v;
        emit valueChanged(old, mValue);
    }
}
QVariant Parameter::getValue() const 
{ 
    return mValue; 
}

void Parameter::setIsFixed(bool f) 
{ 
    mIsFixed = f; 
}
bool Parameter::isFixed() const 
{ 
    return mIsFixed; 
}

void Parameter::setMin(double v) 
{ 
    mMin = v; 
}
double Parameter::getMin() const 
{ 
    return mMin; 
}

void Parameter::setMax(double v) 
{ 
    mMax = v; 
}
double Parameter::getMax() const 
{ 
    return mMax; 
}

void Parameter::setIsDecimal(bool d) 
{ 
    mIsDecimal = d; 
}
bool Parameter::isDecimal() const 
{ 
    return mIsDecimal; 
}

void Parameter::setOptions(const QStringList &opts) 
{ 
    mOptions = opts; 
}
QStringList Parameter::getOptions() const 
{ 
    return mOptions; 
}
