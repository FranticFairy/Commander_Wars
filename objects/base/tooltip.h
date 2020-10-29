#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QObject>
#include <QTimer>

#include "oxygine-framework.h"

class Tooltip;
typedef oxygine::intrusive_ptr<Tooltip> spTooltip;

class Tooltip : public QObject, public oxygine::Sprite
{
    Q_OBJECT
public:
    explicit Tooltip();
    virtual ~Tooltip();
signals:
    void sigHideTooltip();
    void sigStartTooltip();
    void sigStopTooltip();
public slots:
    QString getTooltipText() const;
    void setTooltipText(const QString &tooltipText);

    void restartTooltiptimer();
    void stopTooltiptimer();

    void showTooltip();
    void hideTooltip();
    void disableTooltip();
    void enableTooltip();
protected:
    oxygine::spActor m_Tooltip;
private:
    QString m_tooltipText;
    QTimer m_TooltipTimer;
    bool m_disabled{false};
};

#endif // TOOLTIP_H
