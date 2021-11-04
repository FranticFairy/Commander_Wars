var Constructor = function()
{
    this.getTerrainGroup = function()
    {
        return 2;
    };
    // loader for stuff which needs C++ Support
    this.init = function (terrain)
    {
        terrain.setVisionHigh(2);
        terrain.setTerrainName(DESERT_ROCK.getName());
    };
    this.getName = function()
    {
        return qsTr("Rock");
    };
    this.getDefense = function()
    {
        return 4;
    };
    this.loadBaseTerrain = function(terrain, currentTerrainID)
    {
        if (currentTerrainID === "SNOW")
        {
            terrain.loadBaseTerrain("SNOW");
        }
        else if (currentTerrainID === "PLAINS")
        {
            terrain.loadBaseTerrain("PLAINS");
        }
        else if (currentTerrainID === "WASTE")
        {
            terrain.loadBaseTerrain("WASTE");
        }
        else
        {
            terrain.loadBaseTerrain("DESERT");
        }
    };
    this.loadBaseSprite = function(terrain)
    {
        var surroundings = terrain.getSurroundings("DESERT_ROCK", false, false, GameEnums.Directions_East, false);
        surroundings += terrain.getSurroundings("DESERT_ROCK", false, false, GameEnums.Directions_West, false);
        terrain.loadBaseSprite("desert_rock" + surroundings);
    };
    this.getFirerangeModifier = function(terrain, unit)
    {
        return -1;
    };
    this.getMiniMapIcon = function()
    {
        return "minimap_desert_rock";
    };
    this.getBonusVision = function(unit)
    {
        if (unit.getUnitType() === GameEnums.UnitType_Infantry)
        {
            return 3;
        }
        else
        {
            return 0;
        }
    };
    this.getTerrainAnimationForeground = function(unit, terrain)
    {
        return "fore_mountain";
    };
    this.getTerrainAnimationBackground = function(unit, terrain)
    {
        return "back_mountain";
    };

    this.getDescription = function()
    {
        return "<r>" + qsTr("Clear view. In Fog of War, Infantry unit's gain ") + "</r>" +
                "<div c='#00ff00'>" + qsTr("vision +3.") + "</div>" +
                "<r>" + qsTr(" It reduces the firerange of indirect units by 1.") + "</r>";
    };

    this.getTerrainSprites = function()
    {
        // array of sprites that can be selected as fix sprites for this terrain
        return ["desert_rock.png",
                "desert_rock+E",
                "desert_rock+E+W",
                "desert_rock+W"];
    };
    this.getTerrainAnimationForeground = function(unit, terrain, defender)
    {
        return "";
    };

    this.getTerrainAnimationBackground = function(unit, terrain)
    {
        return "back_desertmountain";
    };
};
Constructor.prototype = TERRAIN;
var DESERT_ROCK = new Constructor();
