#pragma once
#include <SFML/Graphics.hpp>

sf::View view;//объявили sfml объект "вид", который и является камерой

void getplayercoordinateforview(float x, float y) { //функция для считывания координат игрока
	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 360) tempX = 360;//убираем из вида левую сторону
	if (x > 920) tempX = 920;//убираем из вида левую сторону
	if (y < 280) tempY = 280;//верхнюю сторону
	if (y > 520) tempY = 520;//нижнюю сторону	

	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 

}


void viewmap(float time) { //функция для перемещения камеры по карте. принимает время sfml


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		view.move(0.1 * time, 0);//скроллим карту вправо 
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		view.move(0, 0.1 * time);//скроллим карту вниз 
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		view.move(-0.1 * time, 0);//скроллим карту влево 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		view.move(0, -0.1 * time);//скроллим карту вправо 
	}

}

void changeview() {


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		view.zoom(1.0006f); //масштабируем, уменьшение
		//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view.rotate(0.05);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view.rotate(-0.05);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		view.setSize(720, 560);//устанавливает размер камеры (наш исходный)
	}


}
