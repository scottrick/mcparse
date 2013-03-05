#include "MCScene.h"


MCScene::MCScene(void) {
	create();
}

MCScene::~MCScene(void) {
	destroy();
}

void MCScene::create() {

}

void MCScene::destroy() {

}

void MCScene::prepareRender() {

}

void MCScene::render() {

}

const char *MCScene::GetClassName() const { 
    return "MCScene";
}