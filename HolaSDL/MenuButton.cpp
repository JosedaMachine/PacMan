#include "MenuButton.h"

MenuButton::MenuButton(Point2D pos, int w, int h, Texture* te) : GameObject(pos, w, h) {
	t = te;
}

void MenuButton::render() {
	GameObject:render();
}