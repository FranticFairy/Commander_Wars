CO_JESS.init = function(co)
{
    co.setPowerStars(0);
    co.setSuperpowerStars(3);
};
CO_JESS.activateSuperpower = function(co, powerMode)
{
    CO_JESS.activatePower(co, powerMode);
};
CO_JESS.getSuperPowerDescription = function()
{
    return CO_JESS.getPowerDescription();
};
CO_JESS.getSuperPowerName = function()
{
    return CO_JESS.getPowerName();
};
CO_JESS.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                     defender, defPosX, defPosY, isDefender, action)
{
    if (co.getIsCO0() === true)
    {
        switch (co.getPowerMode())
        {
        case GameEnums.PowerMode_Tagpower:
        case GameEnums.PowerMode_Superpower:
        case GameEnums.PowerMode_Power:
            if ((attacker.getUnitType() !== GameEnums.UnitType_Air) &&
                (attacker.getUnitType() !== GameEnums.UnitType_Naval) &&
                (attacker.getUnitType() !== GameEnums.UnitType_Infantry))
            {
                return 30;
            }
            else if ((attacker.getUnitType() === GameEnums.UnitType_Air) ||
                     (attacker.getUnitType() === GameEnums.UnitType_Naval))
            {
                return -10;
            }
            return 0;
        default:
            if ((attacker.getUnitType() !== GameEnums.UnitType_Air) &&
                (attacker.getUnitType() !== GameEnums.UnitType_Naval) &&
                (attacker.getUnitType() !== GameEnums.UnitType_Infantry))
            {
                return 30;
            }
            break;
        }
        if ((attacker.getUnitType() === GameEnums.UnitType_Air) ||
            (attacker.getUnitType() === GameEnums.UnitType_Naval))
        {
            return -10;
        }
    }
    return 0;
};

CO_JESS.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                       defender, defPosX, defPosY, isAttacker, action)
{
    if (co.getIsCO0() === true)
    {
        if (co.getPowerMode() > GameEnums.PowerMode_Off)
        {
            return 10;
        }
    }
    return 0;
};

CO_JESS.getMovementpointModifier = function(co, unit, posX, posY)
{
    if (co.getIsCO0() === true)
    {
        if (co.getPowerMode() > GameEnums.PowerMode_Off)
        {
            if ((unit.getUnitType() !== GameEnums.UnitType_Air) &&
                (unit.getUnitType() !== GameEnums.UnitType_Naval) &&
                (unit.getUnitType() !== GameEnums.UnitType_Infantry))
            {
                return 1;
            }
        }
    }
    return 0;
};
