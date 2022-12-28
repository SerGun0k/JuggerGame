#pragma once
#include <SFML/Graphics.hpp>

sf::View view;//�������� sfml ������ "���", ������� � �������� �������

void getplayercoordinateforview(float x, float y) { //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 360) tempX = 360;//������� �� ���� ����� �������
	if (x > 920) tempX = 920;//������� �� ���� ����� �������
	if (y < 280) tempY = 280;//������� �������
	if (y > 520) tempY = 520;//������ �������	

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 

}


void viewmap(float time) { //������� ��� ����������� ������ �� �����. ��������� ����� sfml


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		view.move(0.1 * time, 0);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		view.move(0, 0.1 * time);//�������� ����� ���� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		view.move(-0.1 * time, 0);//�������� ����� ����� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		view.move(0, -0.1 * time);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

}

void changeview() {


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		view.zoom(1.0006f); //������������, ����������
		//view.zoom(1.0006f); //���� ����� ����������� ��������������
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		//view.setRotation(90);//����� �� ������ ������� ������
		view.rotate(0.05);//���������� ������������ ������ (������������� �������� - � �������� �������)
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		//view.setRotation(90);//����� �� ������ ������� ������
		view.rotate(-0.05);//���������� ������������ ������ (������������� �������� - � �������� �������)
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		view.setSize(720, 560);//������������� ������ ������ (��� ��������)
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		view.setSize(540, 380);//�������� ������ ������
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//����� ������� �������� ���������� ����� ��� ���� �� �����. ����� ������ ������� ��� ���� ������ View � ����������� � ���� ���������� ������ 2.
	}


}