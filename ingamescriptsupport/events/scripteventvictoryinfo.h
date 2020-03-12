#ifndef SCRIPTEVENTVICTORYINFO_H
#define SCRIPTEVENTVICTORYINFO_H


#include "scriptevent.h"

class ScriptEventVictoryInfo : public ScriptEvent
{
    Q_OBJECT
public:
    ScriptEventVictoryInfo();
    /**
     * @brief readEvent
     * @param rStream
     */
    virtual void readEvent(QTextStream& rStream) override;
    /**
     * @brief writeEvent
     * @param rStream
     */
    virtual void writeEvent(QTextStream& rStream) override;
    /**
     * @brief getPlayer
     * @return
     */
    QString getInfo() const;
    /**
     * @brief setPlayer
     * @param value
     */
    void setInfo(const QString &value);
    /**
     * @brief getDescription
     * @return
     */
    virtual QString getDescription() override
    {
        return tr("Victory Info");
    }
    /**
     * @brief showEditEvent
     */
    virtual void showEditEvent(spScriptEditor pScriptEditor) override;
    /**
     * @brief getVersion
     * @return
     */
    virtual qint32 getVersion() override
    {
        return 0;
    }
private:
    QString info;
};

#endif // SCRIPTEVENTVICTORYINFO_H