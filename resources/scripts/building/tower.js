var Constructor = function()
{
    // called for loading the main sprite
    this.loadSprites = function(building, neutral)
    {
        if (building.getOwnerID() >= 0 && !neutral)
        {
            // none neutral player
            building.loadSprite("tower", false);
            building.loadSpriteV2("tower+mask", GameEnums.Recoloring_Matrix);
        }
        else
        {
            // neutral player
            building.loadSprite("tower+neutral", false);
        }
    };
    this.getBaseIncome = function()
    {
        return 0;
    };

    this.getOffensiveBonus = function(building)
    {
        return 5;
    };

    this.getDefensiveBonus = function(building)
    {
        return 5;
    };

    this.getName = function()
    {
        return qsTr("Tower");
    };

    this.getDescription = function()
    {
        return qsTr("<r>Once captured the Tower boosts your </r><div c='#00ff00'>attack and defence powers</div><r>.</r>");
    };

    this.getVisionHide = function(building)
    {
        return true;
    };

    this.getTerrainAnimationBackground = function(unit, terrain)
    {
        return "back_tower";
    };
}

Constructor.prototype = BUILDING;
var TOWER = new Constructor();
