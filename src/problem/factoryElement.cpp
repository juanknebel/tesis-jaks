//
// Created by zero on 26/09/16.
//

#include "factoryElement.h"

std::unique_ptr<Element> FactoryElement::getTheElement(std::string element)
{
    Element* theElement = nullptr;

    if (element.compare("FILE") == 0) {
        theElement = new ElementFile();
    }
    if (element.compare("AUTHOR") == 0) {
        theElement = new ElementAuthor();
    }

    if (element.compare("ARTICLE") == 0) {
        theElement = new ElementArticle();
    }

    if (element.compare("AFFILIATION") == 0) {
        theElement = new ElementAffiliation();
    }

    return std::move(std::unique_ptr<Element>(theElement));
}
