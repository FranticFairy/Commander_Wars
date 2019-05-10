var Constructor = function()
{
    this.getName = function()
    {
        return qsTr("Bomb");
    };
    this.getEnviromentDamage = function(enviromentId)
    {
        return 95;
    };
    this.getBaseDamage = function(unit)
    {
        switch(unit.getUnitID())
        {
			// infantry
			case "INFANTRY":
                return 110;
			case "MECH":
				return 110;
			case "MOTORBIKE":
				return 110;
			case "SNIPER":
				return 110;

			// supporter
			case "APC":
				return 105;
			case "FLARE":
				return 105;
			case "RECON":
				return 105;

			// tanks
			case "FLAK":
                return 95;
			case "HOVERFLAK":
                return 95;
			case "LIGHT_TANK":
                return 105;
            case "HOVERCRAFT":
                return 105;
				
			// heavy tanks
            case "HEAVY_HOVERCRAFT":
                return 95;
			case "HEAVY_TANK":
                return 95;
			case "NEOTANK":
                return 90;
				
			// very heavy tanks
			case "MEGATANK":
                return 35;

            case "HOELLIUM":
                return 35;
				
			// ranged land units
			case "ARTILLERY":
                return 105;
            case "ANTITANKCANNON":
                return 80;
			case "MISSILE":
                return 105;
            case "ROCKETTHROWER":
                return 105;
			
			// ships
			case "BATTLESHIP":
                return 75;
			case "CANNONBOAT":
                return 95;
			case "CRUISER":
                return 50;
			case "DESTROYER":
                return 50;
			case "SUBMARINE":
                return 95;
			case "LANDER":
				return 95;
            case "BLACK_BOAT":
                return 75;
			case "AIRCRAFTCARRIER":
                return 105;
			default:
				return -1;
        }
    };
};

Constructor.prototype = WEAPON;
var WEAPON_BOMB = new Constructor();