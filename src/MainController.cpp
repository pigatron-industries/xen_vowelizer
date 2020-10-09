#include "MainController.h"

MainController::MainController(Controller** controllers, int size) {
    this->controllers = controllers;
    this->controllerSize = size;
}

void MainController::init(float sampleRate) {
    Hardware::hw.init();
    for(int i = 0; i < controllerSize; i++) {
        controllers[i]->init(sampleRate);
    }
    Hardware::hw.display.setDisplayedPage(controllers[activeController]->getDisplayPage());
}

void MainController::update() {
    Hardware::hw.encoder.tick();
    Hardware::hw.encoderButton.update();

    if(!controllerSelectMode) {
        if(Hardware::hw.encoderButton.held() && Hardware::hw.encoderButton.duration() > 1000) {
            controllerSelectMode = true;
            controllers[activeController]->getDisplayPage()->setSelection(0);
        }
        controllers[activeController]->update();
    } else {
        RotaryEncoder::Direction dir = Hardware::hw.encoder.getDirection();
        if(dir == RotaryEncoder::Direction::CLOCKWISE) {
            activeController = ((activeController + 1) % (controllerSize));
            controllers[activeController]->getDisplayPage()->setSelection(0);
            Hardware::hw.display.setDisplayedPage(controllers[activeController]->getDisplayPage());
        } else if(dir == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
            activeController = activeController > 0 ? activeController - 1 : controllerSize - 1;
            controllers[activeController]->getDisplayPage()->setSelection(0);
            Hardware::hw.display.setDisplayedPage(controllers[activeController]->getDisplayPage());
        }
        if(Hardware::hw.encoderButton.pressed()) {
            controllerSelectMode = false;
            controllers[activeController]->getDisplayPage()->setSelection(-1);
        }
    }

    Hardware::hw.display.render();
}

void MainController::process(float **in, float **out, size_t size) {
    controllers[activeController]->process(in, out, size);
}

void MainController::render() {
    


    // #if defined(XEN_TFT)
    //     hw.tft.setCursor(2, 0, 2);
    //     if(controllerSelectMode) {
    //         hw.tft.fillRect(0, 0, hw.tft.width()-1, 16, TFT_NAVY);
    //         hw.tft.setTextColor(TFT_YELLOW, TFT_NAVY);
    //     } else {
    //         hw.tft.setTextColor(TFT_OLIVE, TFT_BLACK);
    //     }
    //     hw.tft.print(controllers[activeController]->getName());
    //     hw.tft.print("          ");
    //     hw.tft.drawLine(0, 16, hw.tft.width()-1, 16, TFT_OLIVE);

    //     if(!controllerSelectMode) {
    //         controllers[activeController]->render();
    //     }
    // #endif
}