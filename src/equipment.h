#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <unordered_map>
#include "item.h"
#include "facingdirection.h"

enum EquipmentType
    {
        WEAPON,
        HEAD,
        MAX_EQUIPMENTTYPE
    };

class Equipment
{
    public:
        Equipment();
        ~Equipment();

        void equip(EquipmentType type, Item* item);
        void unequip(EquipmentType type);

        void render(float cameraX, float cameraY);
        void update(float dt, FacingDirection fd, float posX, float posY);

    private:
        std::unordered_map<EquipmentType, Item*> equipment;
        FacingDirection facingDirection = LEFT;
};

#endif // !EQUIPMENT_H
