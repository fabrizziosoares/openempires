// General purpose test zones.

#include "Units.h"

#include "Util.h"

Units Units_GenerateTestZone(Units units, const Map map, const Grid grid, const Registrar graphics, const int32_t users)
{
    if(users > 0)
    {
        const Point zero = { 0,0 };
        const int32_t starting_villagers = 5;
        const Point middle = {
            map.cols / 2,
            map.rows / 2,
        };
        const int32_t padding = 10;
        const int32_t dx = middle.x - padding;
        const int32_t dy = middle.y - padding;
        const Point slots[] = {
            { middle.x + dx, middle.y      }, // E.
            { middle.x + dx, middle.y + dy }, // SE.
            { middle.x,      middle.y + dy }, // S.
            { middle.x - dx, middle.y + dy }, // SW.
            { middle.x - dx, middle.y      }, // W.
            { middle.x - dx, middle.y - dy }, // NW
            { middle.x,      middle.y - dy }, // N.
            { middle.x + dx, middle.y - dy }, // NE.
        };
        const Button a = { ICONTYPE_BUILD, { ICONBUILD_TOWN_CENTER  }, TRIGGER_NONE };
        const Button b = { ICONTYPE_UNIT,  { ICONUNIT_MALE_VILLAGER }, TRIGGER_NONE };
        const Parts towncenter = Parts_FromButton(a, units.share.status.age, units.share.status.civ);
        const Parts villager   = Parts_FromButton(b, units.share.status.age, units.share.status.civ);
        const int32_t len = UTIL_LEN(slots);
        for(int32_t i = 0; i < users; i++)
        {
            const int32_t index = (i * len) / users;
            const Point slot = slots[index];
            const Color color = (Color) i;
            units = Units_SpawnParts(units, slot, zero, grid, color, graphics, map, false, towncenter, false, TRIGGER_NONE);
            for(int32_t j = 0; j < starting_villagers; j++)
            {
                const Point shift = { -3, 3 };
                const Point cart = Point_Add(slot, shift);
                units = Units_SpawnParts(units, cart, zero, grid, color, graphics, map, false, villager, false, TRIGGER_NONE);
            }
        }
        Parts_Free(towncenter);
        Parts_Free(villager);
    }
    return units;
}
