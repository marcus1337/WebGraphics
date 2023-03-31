#include "Graphics/Objects/ObjectContainer.h"

ObjectContainer::ObjectContainer() {

}

ObjectContainer& ObjectContainer::getInstance() {
    static ObjectContainer objectContainer;
    return objectContainer;
}

