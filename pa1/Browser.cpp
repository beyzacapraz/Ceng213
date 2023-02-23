#include "Browser.h"

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    Window a;
    windows.prepend(a);
}

void Browser::closeWindow() {
    if(windows.getSize() == 0);
    else{
        windows.removeNode(windows.getFirstNode());
    }
}

void Browser::switchToWindow(int index) {
    if(windows.getSize()==0);
    else{
        windows.moveToIndex(index,0);
    }
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    if(from.isEmpty());
    else{
        Tab active = from.getActiveTab();
        from.closeTab();
        to.newTab(active);
        
    }

}

void Browser::mergeWindows(Window &window1, Window &window2) {
        window2.changeActiveTabTo(0);
        while(!window2.isEmpty()){
            window1.newTab(window2.getActiveTab());
            window2.closeTab();
        
    }
}

void Browser::mergeAllWindows() {
    if(windows.getSize()==0 || windows.getSize()==1);
    else{
        Node<Window>* current = windows.getFirstNode();
        current = current -> next;
        while(current != windows.getFirstNode()){
            mergeWindows(windows.getFirstNode()-> data, current -> data);
            current = current -> next;
            
        }
    }
}

void Browser::closeAllWindows() {
    int i,n;
    n = windows.getSize();
    for(i=0;i<n;i++){
        closeWindow();
    }
}

void Browser::closeEmptyWindows() {
         int i,index = 0, n = windows.getSize();
         Node<Window>* current = windows.getFirstNode(); 
         for(i=0;i<n;i++){
             if((current -> data).isEmpty()){
                 current = current -> next;
                 windows.removeNodeAtIndex(index);
             }
             else{
                 current = current -> next;
                 index++;
             }
             
         }

        
    
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}

