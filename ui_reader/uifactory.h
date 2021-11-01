#ifndef UIFACTORY_H
#define UIFACTORY_H

#include <QObject>
#include <QDomDocument>
#include "3rd_party/oxygine-framework/oxygine-framework.h"

#include "coreengine/interpreter.h"
#include "coreengine/console.h"

#include "ui_reader/createdgui.h"

class UiFactory : public QObject
{
    Q_OBJECT
public:
    using CreatorFunction = std::function<bool(oxygine::spActor, QDomElement, oxygine::spActor & item, CreatedGui* pMenu)>;
    struct FactoryItem
    {
        QString m_id;
        CreatorFunction m_creator;
    };
    static UiFactory & getInstance()
    {
        if (m_pUiFactory == nullptr)
        {
            m_pUiFactory = new UiFactory();
        }
        return *m_pUiFactory;
    }
    /**
     * @brief createUi
     * @param uiXmlFile
     */
    void createUi(QString uiXml, CreatedGui* pMenu);
    /**
     * @brief getFactoryItems
     * @return
     */
    QVector<UiFactory::FactoryItem> & getFactoryItems();
private:
    // this section contains the information about the elements and the attributes supported by the xml
    /**
     * Nodename: Label
     * supported attributes are:
     * mandatory: x, y, width, heigth, text, font,
     * optional: tooltip, onUpdate, id
     */
    bool createLabel(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui* pMenu);
    /**
      * Nodename: Checkbox
      * supported attributes are:
      * mandatory: x, y, onEvent, startValue
      * optional: tooltip, id
      */
    bool createCheckbox(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui* pMenu);
    /**
      * Nodename: Spinbox
      * supported attributes are:
      * mandatory: x, y, width, min, max, infinite, onEvent, startValue
      * optional: tooltip, id
      */
    bool createSpinbox(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui* pMenu);
    /**
      * Nodename: Slider
      * supported attributes are:
      * mandatory: x, y, width, min, max, onEvent, startValue
      * optional: tooltip, id
      */
    bool createSlider(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui*);
    /**
      * Nodename: Textbox
      * supported attributes are:
      * mandatory: x, y, width, onEvent, startValue
      * optional: tooltip, id
      */
    bool createTextbox(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui*);
    /**
      * Nodename: TimeSpinbox
      * supported attributes are:
      * mandatory: x, y, width, onEvent, startValue
      * optional: tooltip, id
      */
    bool createTimeSpinbox(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui*);
    /**
      * Nodename: Panel
      * supported attributes are:
      * mandatory: x, y, width, height, childs
      * optional: tooltip, id
      */
    bool createPanel(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui*);
    /**
      * Nodename: Box
      * supported attributes are:
      * mandatory: x, y, width, height, sprite, childs
     */
    bool createBox(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui* pMenu);
    /**
      * Nodename: Icon
      * supported attributes are:
      * mandatory: x, y, size, startValue
      */
    bool createIcon(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui*);
    /**
     * Nodename: Button
     * supported attributes are:
     * mandatory: x, y, text, onEvent
     * optional: tooltip, width
     */
    bool createButton(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui* pMenu);
    /**
     * Nodename: Button
     * supported attributes are:
     * mandatory: x, y, sprite, onEvent
     */
    bool createIconButton(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui*);
signals:
    void sigDoEvent(QString command);
private slots:
    void doEvent(QString command);

private:
    explicit UiFactory();
    /**
     * @brief checkArray
     * @param attributes
     * @return
     */
    bool checkElements(QDomNodeList element, const QVector<QString> & attributes);
    QString getAttribute(QDomNodeList childs, QString attribute);
    QDomNode getNode(QDomNodeList childs, QString attribute);
    bool createItem(oxygine::spActor parent, QDomElement element, oxygine::spActor & item, CreatedGui* pMenu);
    qint32 getIntValue(QString line);
    bool getBoolValue(QString line);
    QString getStringValue(QString line);
    oxygine::TextStyle getStyle(QString styleName);
    QString getId(QString attribute);
    template<typename TType>
    void onEvent(QString line, TType value)
    {
        QString args;
        if constexpr(std::is_same<QString, TType>::value)
        {
            args = "var input = \"" + value + "\";";
        }
        else
        {
            args = "var input = " + QString::number(value) + ";";
        }
        QJSValue erg = Interpreter::getInstance()->evaluate(args + line);
        if (erg.isError())
        {
            CONSOLE_PRINT("Error while parsing " + args + line + " Error: " + erg.toString() + ".", Console::eERROR);
        }
    }
    template<typename TType>
    TType onUpdate(QString line)
    {
        TType ret;
        QJSValue erg = Interpreter::getInstance()->evaluate(line);

        if constexpr(std::is_same<QString, TType>::value)
        {
            ret = erg.toString();
        }
        else if constexpr(std::is_arithmetic<TType>::value)
        {
            ret = erg.toNumber();
        }
        else
        {
            CONSOLE_PRINT("Unable to determine a return value while interpreting. Line: " + line, Console::eERROR);
        }
        if (erg.isError())
        {
            CONSOLE_PRINT("Error while parsing " + line + " Error: " + erg.toString() + ".", Console::eERROR);
        }
        return ret;
    }
    static QString translate(QString line);
private:

    static UiFactory* m_pUiFactory;
    QVector<FactoryItem> m_factoryItems;
    QRect m_lastCoordinates;
    quint32 m_creationCount{0};
};

#endif // UIFACTORY_H
