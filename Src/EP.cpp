/*++

VegeTable group, FTI grp. 21317

Filename:
	EP.cpp
	
Abstract:
	Define entry point
	
Author:
	KIRAY

--*/

#include <sstream>
#include <SFML\Graphics.hpp>

#include "Actor.hpp"
#include "Enemy.hpp"
#include "Teacher.h"

#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")

using namespace sf;

int main(int argc, char* argv[]) {
	bool bGame = true; // ����, ���� ���� �������� (����� ��������) - ����

	VideoMode desk = VideoMode::getDesktopMode();
	RenderWindow wnd(VideoMode(800, 600, desk.bitsPerPixel), "VegaGame", Style::None);
	
	// ������ ������ ��� ����������� ���� � ��������� � ����� ����
	Font fnt;
	fnt.loadFromFile("../Data/main.ttf");
	Text txt("", fnt, 20);
	txt.setColor(Color::Green);
	// ��������� � ����� ����
	Text endGame ("You lost :-(", fnt, 60);
	endGame.setColor(Color::Red);
	
	float fTime = 0.f;
	// ������ ������ ��� �����
	Texture mapTexture;
	mapTexture.loadFromFile("../Data/Level0.png");
	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);
	
	// ������ ������ ������ ������
	Texture actorTexture;
	actorTexture.loadFromFile("../Data/Actor.png");
	CActor actor(actorTexture, 50.f, 50.f, 96, 96, "Actor");

	// ������ ������ ������ ����
	Image enemyImg;
	enemyImg.loadFromFile("../Data/Voenkom.png");
	enemyImg.createMaskFromColor(Color(255, 255, 255));
	Texture textEnemy;
	textEnemy.loadFromImage(enemyImg);
	
	CEnemy Army1(textEnemy, 100.f, 200.f, 96, 96, "Army");

	// ������ ������ ������ �������
	sf:: Image image_Teacher;
	image_Teacher.loadFromFile("../Data/Teacher.png");
	image_Teacher.createMaskFromColor(image_Teacher.getPixel(0,0));
	Texture textTeacher;
	textTeacher.loadFromImage(image_Teacher);

	CTeacher Teacher(textTeacher, 100.f, 200.f, 96, 96, "Teacher");

	Clock clock;
	Event event;
	while(wnd.isOpen()) {
		if(bGame) {
			fTime = clock.getElapsedTime().asMicroseconds();
			fTime /= 600; // �������� ����
			clock.restart();
		} else fTime = 0.f;
	
		while(wnd.pollEvent(event)) {
			if(event.type == Event::Closed || 
			  (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) 
				wnd.close();
		}		
		
		// ������� ���� ��� ���������� (������������ ����������, ������������ ������������ � ���������� ������, ���� ����������)
		// ������� � �������� ��������� �������� ����
		if(bGame) {
			actor.Frame(fTime);
			Army1.Frame(fTime);
			Teacher.Frame(fTime);
		}

		// ���� ����� ���� �����, ��� ��������� ���, �� ��������� ������������ 
		// � ���. ���������
		if(actor.m_bLife == true) {
			if(actor.getRect().intersects(Army1.getRect())) {
				actor.nHealth = 0;
				bGame = false;
			}
				
			if(actor.getRect().intersects(Teacher.getRect()) && actor.uLabCnt >= 3)
				actor.uLabCnt -= 3;
		}
		
		wnd.clear(); // ������� ����
		
		// ������������ �����
		for(unsigned i=0; i<MAP_HEIGHT; i++)
			for(unsigned j=0; j<MAP_WIDTH; j++) {
				if(g_szMap[i][j] == '0') mapSprite.setTextureRect(IntRect(32, 0, 32, 32)); // �����
				if(g_szMap[i][j] == '1') mapSprite.setTextureRect(IntRect(0, 0, 32, 32)); // ���
				if(g_szMap[i][j] == '2') mapSprite.setTextureRect(IntRect(64, 0, 32, 32)); // ����
				if(g_szMap[i][j] == '3') mapSprite.setTextureRect(IntRect(96, 0, 32, 32)); // Ƹ���� ���
				
				mapSprite.setPosition(j*32, i*32);
				wnd.draw(mapSprite);
			}
		
		// ������������ ��� (��������, ��������� ����)
		std::ostringstream strLab, strHealth;
		strLab << actor.uLabCnt; strHealth << actor.nHealth;
		txt.setString("Lab's: " + strLab.str() + "\nHealth: " + strHealth.str());
		txt.setPosition(650, 500);
		wnd.draw(txt);
		// �������, ���� ����������, ��������� � ���������
		if(!bGame) {
			endGame.setPosition(250.f, 250.f); // for 800x600 res
			wnd.draw(endGame);
		}
		
		// ������ �������
		wnd.draw(actor.getSprite());
		wnd.draw(Army1.getSprite());
		wnd.draw(Teacher.getSprite());
		
		wnd.display(); // ���������� ������������ ����
	}
	
	return 0;
}