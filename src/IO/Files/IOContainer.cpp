#include "IO/Files/IOContainer.h"


IOContainer::IOContainer() {

}

IOContainer& IOContainer::getInstance() {
    static IOContainer ioContainer;
    return ioContainer;
}

