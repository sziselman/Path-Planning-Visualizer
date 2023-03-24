#include <iostream>
#include "visualizer.h"


int main() {

    Visualizer vis(1000, 1000);
    while (!vis.quit()) {
        vis.render();
        vis.update();
    }
}
