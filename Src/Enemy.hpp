//����� ���������� ������� 21317�� 
// ����� �����
#pragma once

#include "Entity.hpp"

class CEnemy : public CEntity {
public:
	int direction;//����������� �������� �����

	CEnemy();             // ������������ � ��� ��������� � � ����������� 
	CEnemy(sf::Texture&, float, float, int, int, std::string);
//	~CEnemy();

	void checkCollisionWithMap(float m_fDx, float m_fDy);//�-��� �������� ������������ � ������
	void Frame(float& fTime);

	std::string* m_pszMapCode;
	void setMap(std::string* dsd) {m_pszMapCode = dsd;}

	sf::Sprite getSprite() {return m_Sprite;}

};

/*
	bool  m_bLife;
	int   m_nW, m_nH, m_nHealth;
	float m_fX, m_fY, m_fDx, m_fDy;
	float m_fSpeed, m_fCurrFrame;
	sf::Sprite  m_Sprite;
*/