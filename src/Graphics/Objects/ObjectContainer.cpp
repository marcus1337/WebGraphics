#include "Graphics/Objects/ObjectContainer.h"
#include <iostream>

ObjectContainer::ObjectContainer() {
    for (const auto& name : IOContainer::getInstance().ioOBJ.getModelNames()) {
        auto modelObject = std::shared_ptr<ModelObject>(new ModelObject(name));
        modelObjects[name] = modelObject;
    }
}

ObjectContainer& ObjectContainer::getInstance() {
    static ObjectContainer objectContainer;
    return objectContainer;
}

ModelObject* ObjectContainer::getModelObject(std::string model) {
    if (!modelObjects.contains(model)) {
        std::cerr << "ERROR modelObjects does not contain " << model << "!\n";
        return nullptr;
    }
    return modelObjects[model].get();
}