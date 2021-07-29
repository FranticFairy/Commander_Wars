CO_CASSIDY.coZoneBonus = 0;
CO_CASSIDY.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                        defender, defPosX, defPosY, isDefender, action)
{
    if (co.getIsCO0() === true)
    {
        if (defender !== null)
        {
            switch (co.getPowerMode())
            {
            case GameEnums.PowerMode_Tagpower:
            case GameEnums.PowerMode_Superpower:
                if (attacker.getHp() >= defender.getHp())
                {
                    return 70;
                }
                return 20;
            case GameEnums.PowerMode_Power:
                if (attacker.getHp() >= defender.getHp())
                {
                    return 50;
                }
                return 20;
            default:
                if (attacker.getHp() >= defender.getHp())
                {
                    return 20;
                }
            }
        }
    }
    return 0;
};

CO_CASSIDY.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
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
