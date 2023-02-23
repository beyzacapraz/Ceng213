#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    if((tabs.getSize()) == 0){
        Tab empty_tab;
        return empty_tab;
    }
    else{
        Tab active = (tabs.getNodeAtIndex(activeTab)) -> data;
        return active;
    }
    
}

bool Window::isEmpty() const {
    if(tabs.getSize() == 0) return true;
    else return false;
}

void Window::newTab(const Tab &tab) {
    if(tabs.getSize() == 0){
        tabs.prepend(tab); 
        activeTab = 0;
    }
    else{
        tabs.insertAfterNode(tab,tabs.getNodeAtIndex(activeTab));
        activeTab++;
    }
    
}


void Window::closeTab() {
    
    if(tabs.getSize() == 0) activeTab = -1;
    else if(activeTab == 0) tabs.removeNode(tabs.getNodeAtIndex(activeTab));
    else if (activeTab == tabs.getSize()-1){
        tabs.removeNode(tabs.getNodeAtIndex(activeTab));
        activeTab--;
    }
    else{
        tabs.removeNode(tabs.getNodeAtIndex(activeTab));
        activeTab++;
    }

    
}

void Window::moveActiveTabTo(int index) {
    tabs.moveToIndex(activeTab, index);
    if(index > tabs.getSize() -1) activeTab = tabs.getSize()-1;
    else{
        activeTab = index;
    }
    
}

void Window::changeActiveTabTo(int index) {
    if( tabs.getSize() == 0 || index < 0 || index > (tabs.getSize()-1)) return;
    else{
        activeTab = index;
    }
}

void Window::addTab(Node<Tab> &tab) {
    if(tabs.getSize() == 0){
        tabs.append(tab.data);
        activeTab = 0;
    }
    else{
        tabs.append(tab.data);
        
    }
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}

