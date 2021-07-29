CO_ANDY.init = function(co)
{
    co.setPowerStars(0);
    co.setSuperpowerStars(3);
};
CO_ANDY.activateSuperpower = function(co, powerMode)
{
    CO_ANDY.activatePower(co, powerMode);
};
CO_ANDY.getSuperPowerDescription = function()
{
    return CO_ANDY.getPowerDescription();
};
CO_ANDY.getSuperPowerName = function()
{
    return CO_ANDY.getPowerName();
};
CO_ANDY.coZoneBonus = 0;
CO_ANDY.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                     defender, defPosX, defPosY, isDefender, action)
{
    return 0;
};
CO_ANDY.getMovementpointModifier = function(co, unit, posX, posY)
{
    return 0;
};

CO_ANDY.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
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
