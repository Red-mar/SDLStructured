#include "equipment.h"

Equipment::Equipment()
{
    for (int i = 0; i < MAX_EQUIPMENTTYPE; i++)
    {
        equipment[(EquipmentType)i] = nullptr;
    }
}

Equipment::~Equipment()
{
    for (std::unordered_map<EquipmentType, Item *>::iterator it = equipment.begin(); it != equipment.end(); it++)
    {
        delete (it->second);
    }
    equipment.clear();
}

void Equipment::equip(EquipmentType type, Item *item)
{
    equipment[type] = item;
}

void Equipment::unequip(EquipmentType type)
{
    equipment[type] = nullptr;
}

void Equipment::update(float dt, FacingDirection fd)
{
    for(auto item : equipment)
    {
        if(item.second != NULL)
        {
            item.second->setFacingDirection(fd);
            item.second->update(dt);
        }
    }
}

void Equipment::render(float cameraX, float cameraY, float posX, float posY)
{
    for (auto item : equipment)
    {
        if (item.second != NULL)
        {
            switch (item.first)
            {
            case HEAD:
                item.second->render(cameraX, cameraY, posX, posY);
                break;
            case WEAPON:
                //
                break;
            default:
                break;
            }
        }
    }
}
