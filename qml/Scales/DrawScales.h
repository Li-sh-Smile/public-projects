#ifndef DRAWSCALES_H
#define DRAWSCALES_H

#include <QQuickPaintedItem>
#include <QPainter>


#define GETFUN(Type,Property,VariableName)   \
    public: Type get##Property() const {return VariableName;}

#define SETFUN(Type,Property,VariableName)   \
    public: void set##Property(const Type value) { \
        if(value == VariableName) return; \
        VariableName = value; emit sig##Property ##Changed(); \
    }
#define SETSIGNAL(Property) \
    Q_SIGNALS: void sig##Property ##Changed();

#define MY_PROPERTY(Type,PropertyName,Property,VariableName)     \
    private: Q_PROPERTY(Type PropertyName READ get##Property WRITE set##Property NOTIFY sig##Property ##Changed) \
    GETFUN(Type,Property,VariableName) \
    SETFUN(Type,Property,VariableName) \
    SETSIGNAL(Property)


class DrawScales : public QQuickPaintedItem
{
    Q_OBJECT
    MY_PROPERTY(QColor, lineColor,      LineColor,      stuDrawProperty.lineColor)
    MY_PROPERTY(QColor, textColor,      TextColor,      stuDrawProperty.textColor)
    MY_PROPERTY(int,    textPixelSize,  TextPixelSize,  stuDrawProperty.textPixelSize)
    MY_PROPERTY(int,    _margins,        Margins,        stuDrawProperty.margins)
    MY_PROPERTY(int,    _leftMargin,     LeftMargin,     stuDrawProperty.leftMargin)
    MY_PROPERTY(int,    _rightMargin,    RightMargin,    stuDrawProperty.rightMargin)
    MY_PROPERTY(int,    _topMargin,      TopMargin,      stuDrawProperty.topMargin)
    MY_PROPERTY(int,    _bottomMargin,   BottomMargin,   stuDrawProperty.bottomMargin)

    MY_PROPERTY(int,    startValue,     StartValue,     stuDrawProperty.startValue)
    MY_PROPERTY(int,    stopValue,      StopValue,      stuDrawProperty.stopValue)
    MY_PROPERTY(int,    spacingValue,   SpacingValue,   stuDrawProperty.spacingValue)
    MY_PROPERTY(int,    drawType,       DrawType,       stuDrawProperty.drawType)
private:
    struct StructDrawProperty
    {
        QColor lineColor;
        QColor textColor;
        int textPixelSize;

        int margins;
        int leftMargin;
        int rightMargin;
        int topMargin;
        int bottomMargin;

        int startValue;
        int stopValue;
        int spacingValue;

        int drawType;   //0:上  1:下  2:左  3:右
    }stuDrawProperty;
public:
    DrawScales(QQuickItem *parent = nullptr);

protected:
    void paint(QPainter *painter);
    void paintLines(QPainter *painter);

private:

};
namespace initQMLRegisterType {
    static void initQMLType(){
        qmlRegisterType<DrawScales>("DrawScales", 1, 0, "DrawScales");
    }
}

#endif // DRAWSCALES_H
