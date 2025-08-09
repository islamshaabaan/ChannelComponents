#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include <QStringList>
#include <QVariant>

class Parameter : public QObject {
    Q_OBJECT

public:
    explicit Parameter(QObject* parent = nullptr);

    // setters/getters
    void setName(const QString& n);    
    QString getName() const;
    void setKind(const QString& k);    
    QString getKind() const;
    void setValue(const QVariant& v);  
    QVariant getValue() const;
    void setIsFixed(bool f);           
    bool isFixed() const;

    // numeric
    void setMin(double v);    
    double getMin() const;
    void setMax(double v);    
    double getMax() const;
    void setIsDecimal(bool d); 
    bool isDecimal() const;

    // category
    void setOptions(const QStringList& opts); 
    QStringList getOptions() const;

signals:
    // emitted when value is changed programatically
    void valueChanged(const QVariant &oldValue, const QVariant &newValue);
    
private:
    QString mName;
    QString mKind;
    QVariant mValue;
    bool mIsFixed{false};

    double mMin{0.0};
    double mMax{0.0};
    bool mIsDecimal{false};

    QStringList mOptions;
};

#endif // PARAMETER_H
