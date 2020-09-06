#ifndef RULESELECTION_H
#define RULESELECTION_H

#include <QObject>
#include "oxygine-framework.h"

#include "objects/multislider.h"

class RuleSelection;
typedef oxygine::intrusive_ptr<RuleSelection> spRuleSelection;

class RuleSelection : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit RuleSelection(qint32 width);
    virtual ~RuleSelection();
    void showRuleSelection();
    void confirmRuleSelectionSetup();
signals:
    void sigShowCOBannlist();
    void sigShowActionBannlist();
    void sigShowPerkBannlist();
public slots:
    // slots for changing the rules
    void startWeatherChanged(qint32 value);
    void weatherChancesChanged();
    void showCOBannlist();
    void showPerkBannlist();
    void showActionBannlist();
private:
    void addCustomGamerules(qint32 & y);
private:
    spMultislider m_pWeatherSlider;
};

#endif // RULESELECTION_H
