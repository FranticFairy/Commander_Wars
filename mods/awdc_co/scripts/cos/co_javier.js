CO_JAVIER.init = function(co)
{
    co.setPowerStars(3);
    co.setSuperpowerStars(3);
};
CO_JAVIER.activateSuperpower = function(co, powerMode)
{
	CO_JAVIER.activatePower(co, powerMode);
};
CO_JAVIER.getSuperPowerDescription = function()
{
    return CO_JAVIER.getPowerDescription();
};
CO_JAVIER.getSuperPowerName = function()
{
    return CO_JAVIER.getPowerName();
};
CO_JAVIER.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                             defender, defPosX, defPosY, isDefender, action)
{
    var towers = co.getOwner().getBuildingCount("TOWER");
    switch (co.getPowerMode())
    {
        case GameEnums.PowerMode_Tagpower:
        case GameEnums.PowerMode_Superpower:
        case GameEnums.PowerMode_Power:
            return towers * 15 + 10;
        default:
            if (co.inCORange(Qt.point(atkPosX, atkPosY), attacker))
            {
                return towers * 5 + 10;
            }
    }
};
CO_JAVIER.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                             defender, defPosX, defPosY, isAttacker, action)
{
    var rangedAttacked = (Math.abs(atkPosX - defPosX) + Math.abs(atkPosY - defPosY) > 1);
    var towers = co.getOwner().getBuildingCount("TOWER");
    var ret = 0;
    switch (co.getPowerMode())
    {
        case GameEnums.PowerMode_Tagpower:
        case GameEnums.PowerMode_Superpower:
        case GameEnums.PowerMode_Power:
            if (rangedAttacked)
            {
                ret += 40;
            }
            ret += towers * 5  + 10;
            break;
        default:
            if (co.inCORange(Qt.point(defPosX, defPosY), defender))
            {
                ret += towers * 5 + 10;
                if (rangedAttacked)
                {
                    ret += 20;
                }
            }
            break;
    }
    return ret;
};
