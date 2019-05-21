#include <iostream>
#include "CourierCompany.h"
#include "Furniture.h"
#include "Shoes.h"

Element* createElement(const char* name, size_t weight, bool isBreakable) {
    return new Element(name, weight, isBreakable);
}

Item* createFurniture(const char* address, double cost, size_t capacity, const Box& box, const char* brand) {
    return new Furniture(address, cost, capacity, box, brand);
}

Item* createShoes(const char* address, double cost, size_t capacity, const Box& box, bool canMeasure) {
    return new Shoes(address, cost, capacity, box, canMeasure);
}

Item* createItem(const char* address, double cost, size_t capacity, const Box& box) {
    return new Item(address, cost, capacity, box);
}

void addElements(Item* item, Element* e1, Element* e2, Element* e3, Element* e4) {
    item->add_element(e1);
    item->add_element(e2);
    item->add_element(e3);
    item->add_element(e4);
}

void testCompany() {
    CourierCompany company(16);
    Box box1(10, 20, 30);
    Box box2(20, 15, 60);
    Box box3(10, 10, 10);

    Element *element1 = createElement("iron", 10, false);
    Element *element2 = createElement("wood", 5, false);
    Element *element3 = createElement("marble", 7, true);
    Element *element4 = createElement("steel", 11, false);

    Item *item1 = createFurniture("some address1", 2.37, 8, box1, "Some brand1");
    addElements(item1, element1, element2, element3, element4);

    Item *item2 = createShoes("some address2", 3.37, 16, box2, false);
    addElements(item2, element1, element2, element3, element4);

    Item *item3 = createFurniture("some address3", 0.37, 8, box3, "Some brand2");
    addElements(item3, element1, element2, element3, element4);

    Item *item4 = createShoes("some address4", 9.57, 12, box2, true);
    addElements(item4, element1, element2, element3, element4);

    Item *item5 = createFurniture("some address5", 2.37, 18, box1, "Some brand4");
    addElements(item5, element1, element2, element3, element4);

    Item *item6 = createItem("some address6", 6.37, 12, box3);
    addElements(item6, element1, element2, element3, element4);

    company.addItem(item1);
    company.addItem(item2);
    company.addItem(item3);
    company.addItem(item4);
    company.addItem(item5);
    company.addItem(item6);
    std::cout << "All cost for transport: " << company.getAllCostForTransport() << std::endl;
    std::cout << "All volume: " << company.getAllVolume() << std::endl;
    company.print();

    delete element1;
    delete element2;
    delete element3;
    delete element4;
}

void serializeItem() {
    Box box(50, 10, 20);

    Element* element1 = createElement("iron", 10, false);
    Element* element2 = createElement("wood", 5, false);
    Element* element3 = createElement("marble", 7, true);
    Element* element4 = createElement("steel", 11, false);

    Item* item = createFurniture("some address", 6.37, 9, box, "Some brand1");
    addElements(item, element1, element2, element3, element4);

    delete element1;
    delete element2;
    delete element3;
    delete element4;
    delete item;

}

int main() {
    testCompany();
    serializeItem();
    return 0;
}